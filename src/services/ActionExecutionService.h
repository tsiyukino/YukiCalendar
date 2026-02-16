#ifndef ACTIONEXECUTIONSERVICE_H
#define ACTIONEXECUTIONSERVICE_H

#include <QObject>
#include <QTimer>
#include <QVariantMap>
#include <QDateTime>
#include "models/ActionTreeData.h"
#include "models/CalendarEvent.h"
#include "ModuleService.h"
#include "EventService.h"

class ActionExecutionService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int checkIntervalMs READ checkIntervalMs WRITE setCheckIntervalMs NOTIFY checkIntervalMsChanged)

public:
    explicit ActionExecutionService(ModuleService* moduleService, EventService* eventService, QObject *parent = nullptr);
    ~ActionExecutionService();

    bool isRunning() const { return m_isRunning; }
    int checkIntervalMs() const { return m_checkIntervalMs; }

    void setCheckIntervalMs(int intervalMs);

    // Start/Stop execution service
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    // Execute action tree manually
    Q_INVOKABLE bool executeActionTree(ActionTreeData* tree, CalendarEvent* event);

signals:
    void isRunningChanged();
    void checkIntervalMsChanged();
    void executionCompleted(const QString& eventId, bool success);
    void executionError(const QString& eventId, const QString& error);

private slots:
    void checkAndExecutePendingActions();

private:
    ModuleService* m_moduleService;
    EventService* m_eventService;
    QTimer* m_timer;
    bool m_isRunning;
    int m_checkIntervalMs;

    // Execution helpers
    bool executeNode(ActionNode* node, QVariantMap& context, ActionTreeData* tree);
    QVariantMap gatherInputs(ActionNode* node, const QVariantMap& context, ActionTreeData* tree);
    void followExecuteConnections(ActionNode* node, QVariantMap& context, ActionTreeData* tree);
    ActionNode* findStartNode(ActionTreeData* tree);
};

#endif // ACTIONEXECUTIONSERVICE_H
