#include "ActionExecutionService.h"
#include <QDebug>

ActionExecutionService::ActionExecutionService(ModuleService* moduleService, EventService* eventService, QObject *parent)
    : QObject(parent)
    , m_moduleService(moduleService)
    , m_eventService(eventService)
    , m_timer(new QTimer(this))
    , m_isRunning(false)
    , m_checkIntervalMs(60000) // 1 minute default
{
    connect(m_timer, &QTimer::timeout, this, &ActionExecutionService::checkAndExecutePendingActions);
}

ActionExecutionService::~ActionExecutionService()
{
    stop();
}

void ActionExecutionService::setCheckIntervalMs(int intervalMs)
{
    if (m_checkIntervalMs != intervalMs) {
        m_checkIntervalMs = intervalMs;
        emit checkIntervalMsChanged();

        if (m_isRunning) {
            m_timer->setInterval(m_checkIntervalMs);
        }
    }
}

void ActionExecutionService::start()
{
    if (!m_isRunning) {
        m_isRunning = true;
        m_timer->start(m_checkIntervalMs);
        emit isRunningChanged();
    }
}

void ActionExecutionService::stop()
{
    if (m_isRunning) {
        m_isRunning = false;
        m_timer->stop();
        emit isRunningChanged();
    }
}

bool ActionExecutionService::executeActionTree(ActionTreeData* tree, CalendarEvent* event)
{
    if (!tree || !event) {
        return false;
    }

    try {
        // Find the start node
        ActionNode* startNode = findStartNode(tree);
        if (!startNode) {
            emit executionError(event->id(), "No start node found in action tree");
            return false;
        }

        // Initialize context with event data
        QVariantMap context;
        context["eventId"] = event->id();
        context["eventName"] = event->name();
        context["startTime"] = event->startTime();
        context["endTime"] = event->endTime();
        context["notes"] = event->notes();
        context["importance"] = event->importance();

        // Execute the tree starting from the start node
        bool success = executeNode(startNode, context, tree);

        if (success) {
            emit executionCompleted(event->id(), true);
        } else {
            emit executionError(event->id(), "Execution failed");
        }

        return success;

    } catch (const std::exception& e) {
        emit executionError(event->id(), QString("Exception: %1").arg(e.what()));
        return false;
    }
}

void ActionExecutionService::checkAndExecutePendingActions()
{
    if (!m_eventService) {
        return;
    }

    QDateTime now = QDateTime::currentDateTime();
    QDateTime rangeStart = now.addSecs(-m_checkIntervalMs / 1000);
    QDateTime rangeEnd = now.addSecs(m_checkIntervalMs / 1000);

    QList<CalendarEvent*> events = m_eventService->getEventsInRange(rangeStart, rangeEnd);

    for (CalendarEvent* event : events) {
        if (event->actionTree() && event->actionTree()->nodeCount() > 0) {
            executeActionTree(event->actionTree(), event);
        }
    }
}

bool ActionExecutionService::executeNode(ActionNode* node, QVariantMap& context, ActionTreeData* tree)
{
    if (!node) {
        return false;
    }

    ICalendarModule* module = m_moduleService->getModule(node->type());
    if (!module) {
        qWarning() << "Module not found:" << node->type();
        return false;
    }

    // Gather inputs from connections
    QVariantMap inputs = gatherInputs(node, context, tree);

    // Merge node parameters
    QVariantMap parameters = node->parameters();
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        if (!inputs.contains(it.key())) {
            inputs[it.key()] = it.value();
        }
    }

    // Execute the module
    QVariantMap outputs = module->executeAsync(inputs);

    // Store outputs in context
    for (auto it = outputs.begin(); it != outputs.end(); ++it) {
        QString outputKey = node->id() + "." + it.key();
        context[outputKey] = it.value();
    }

    // Follow execute connections
    followExecuteConnections(node, context, tree);

    return true;
}

QVariantMap ActionExecutionService::gatherInputs(ActionNode* node, const QVariantMap& context, ActionTreeData* tree)
{
    QVariantMap inputs;

    QList<Connection> connections = tree->getConnectionsToNode(node->id());

    for (const Connection& conn : connections) {
        // Skip execute connections
        if (conn.targetPort == "Execute") {
            continue;
        }

        // Get the source node
        ActionNode* sourceNode = tree->getNode(conn.sourceNodeId);
        if (!sourceNode) {
            continue;
        }

        // Get the output value from context
        QString outputKey = sourceNode->id() + "." + conn.sourcePort;
        if (context.contains(outputKey)) {
            inputs[conn.targetPort] = context[outputKey];
        }
    }

    return inputs;
}

void ActionExecutionService::followExecuteConnections(ActionNode* node, QVariantMap& context, ActionTreeData* tree)
{
    QList<Connection> connections = tree->getConnectionsFromNode(node->id());

    for (const Connection& conn : connections) {
        // Only follow execute connections
        if (conn.sourcePort == "Execute") {
            ActionNode* nextNode = tree->getNode(conn.targetNodeId);
            if (nextNode) {
                executeNode(nextNode, context, tree);
            }
        }
    }
}

ActionNode* ActionExecutionService::findStartNode(ActionTreeData* tree)
{
    if (!tree) {
        return nullptr;
    }

    for (QObject* obj : tree->nodesAsObjects()) {
        ActionNode* node = qobject_cast<ActionNode*>(obj);
        if (node && node->type() == "start-action") {
            return node;
        }
    }

    return nullptr;
}
