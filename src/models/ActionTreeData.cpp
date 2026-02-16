#include "ActionTreeData.h"
#include <QJsonArray>
#include <algorithm>

ActionTreeData::ActionTreeData(QObject *parent)
    : QObject(parent)
{
}

void ActionTreeData::addNode(ActionNode* node)
{
    if (node && !m_nodes.contains(node)) {
        node->setParent(this);
        m_nodes.append(node);
        emit nodesChanged();
        emit nodeAdded(node);
    }
}

void ActionTreeData::removeNode(const QString& nodeId)
{
    auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
                           [&nodeId](ActionNode* node) { return node->id() == nodeId; });

    if (it != m_nodes.end()) {
        ActionNode* node = *it;
        m_nodes.erase(it);

        // Remove all connections involving this node
        auto connIt = m_connections.begin();
        while (connIt != m_connections.end()) {
            if (connIt->sourceNodeId == nodeId || connIt->targetNodeId == nodeId) {
                QString connId = connIt->id;
                connIt = m_connections.erase(connIt);
                emit connectionRemoved(connId);
            } else {
                ++connIt;
            }
        }

        emit nodesChanged();
        emit nodeRemoved(nodeId);

        node->deleteLater();
    }
}

ActionNode* ActionTreeData::getNode(const QString& nodeId) const
{
    auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
                           [&nodeId](ActionNode* node) { return node->id() == nodeId; });

    return (it != m_nodes.end()) ? *it : nullptr;
}

QList<QObject*> ActionTreeData::nodesAsObjects() const
{
    QList<QObject*> result;
    for (ActionNode* node : m_nodes) {
        result.append(qobject_cast<QObject*>(node));
    }
    return result;
}

void ActionTreeData::addConnection(const Connection& connection)
{
    // Check if connection already exists
    auto it = std::find_if(m_connections.begin(), m_connections.end(),
                           [&connection](const Connection& conn) { return conn.id == connection.id; });

    if (it == m_connections.end()) {
        m_connections.append(connection);
        emit connectionsChanged();
        emit connectionAdded(connection);
    }
}

void ActionTreeData::removeConnection(const QString& connectionId)
{
    auto it = std::find_if(m_connections.begin(), m_connections.end(),
                           [&connectionId](const Connection& conn) { return conn.id == connectionId; });

    if (it != m_connections.end()) {
        m_connections.erase(it);
        emit connectionsChanged();
        emit connectionRemoved(connectionId);
    }
}

Connection* ActionTreeData::getConnection(const QString& connectionId)
{
    auto it = std::find_if(m_connections.begin(), m_connections.end(),
                           [&connectionId](const Connection& conn) { return conn.id == connectionId; });

    return (it != m_connections.end()) ? &(*it) : nullptr;
}

QList<Connection> ActionTreeData::getConnectionsFromNode(const QString& nodeId) const
{
    QList<Connection> result;
    for (const Connection& conn : m_connections) {
        if (conn.sourceNodeId == nodeId) {
            result.append(conn);
        }
    }
    return result;
}

QList<Connection> ActionTreeData::getConnectionsToNode(const QString& nodeId) const
{
    QList<Connection> result;
    for (const Connection& conn : m_connections) {
        if (conn.targetNodeId == nodeId) {
            result.append(conn);
        }
    }
    return result;
}

Connection* ActionTreeData::getConnectionFromPort(const QString& nodeId, const QString& portName) const
{
    auto it = std::find_if(m_connections.begin(), m_connections.end(),
                           [&nodeId, &portName](const Connection& conn) {
                               return conn.sourceNodeId == nodeId && conn.sourcePort == portName;
                           });

    return (it != m_connections.end()) ? const_cast<Connection*>(&(*it)) : nullptr;
}

QJsonObject ActionTreeData::toJson() const
{
    QJsonObject json;

    QJsonArray nodesArray;
    for (const ActionNode* node : m_nodes) {
        nodesArray.append(node->toJson());
    }
    json["nodes"] = nodesArray;

    QJsonArray connectionsArray;
    for (const Connection& conn : m_connections) {
        connectionsArray.append(conn.toJson());
    }
    json["connections"] = connectionsArray;

    return json;
}

ActionTreeData* ActionTreeData::fromJson(const QJsonObject& json, QObject *parent)
{
    auto tree = new ActionTreeData(parent);

    QJsonArray nodesArray = json["nodes"].toArray();
    for (const QJsonValue& value : nodesArray) {
        ActionNode* node = ActionNode::fromJson(value.toObject(), tree);
        tree->addNode(node);
    }

    QJsonArray connectionsArray = json["connections"].toArray();
    for (const QJsonValue& value : connectionsArray) {
        Connection conn = Connection::fromJson(value.toObject());
        tree->addConnection(conn);
    }

    return tree;
}

void ActionTreeData::clear()
{
    m_connections.clear();
    emit connectionsChanged();

    qDeleteAll(m_nodes);
    m_nodes.clear();
    emit nodesChanged();
}
