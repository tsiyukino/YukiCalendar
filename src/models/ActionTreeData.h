#ifndef ACTIONTREEDATA_H
#define ACTIONTREEDATA_H

#include <QObject>
#include <QList>
#include <QJsonObject>
#include "ActionNode.h"

class ActionTreeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> nodes READ nodesAsObjects NOTIFY nodesChanged)
    Q_PROPERTY(int nodeCount READ nodeCount NOTIFY nodesChanged)
    Q_PROPERTY(int connectionCount READ connectionCount NOTIFY connectionsChanged)

public:
    explicit ActionTreeData(QObject *parent = nullptr);

    // Node management
    Q_INVOKABLE void addNode(ActionNode* node);
    Q_INVOKABLE void removeNode(const QString& nodeId);
    Q_INVOKABLE ActionNode* getNode(const QString& nodeId) const;
    QList<ActionNode*> nodes() const { return m_nodes; }
    QList<QObject*> nodesAsObjects() const;
    int nodeCount() const { return m_nodes.size(); }

    // Connection management
    Q_INVOKABLE void addConnection(const Connection& connection);
    Q_INVOKABLE void removeConnection(const QString& connectionId);
    Q_INVOKABLE Connection* getConnection(const QString& connectionId);
    QList<Connection> connections() const { return m_connections; }
    int connectionCount() const { return m_connections.size(); }

    // Query helpers
    Q_INVOKABLE QList<Connection> getConnectionsFromNode(const QString& nodeId) const;
    Q_INVOKABLE QList<Connection> getConnectionsToNode(const QString& nodeId) const;
    Q_INVOKABLE Connection* getConnectionFromPort(const QString& nodeId, const QString& portName) const;

    // Serialization
    QJsonObject toJson() const;
    static ActionTreeData* fromJson(const QJsonObject& json, QObject *parent = nullptr);

    // Clear all
    Q_INVOKABLE void clear();

signals:
    void nodesChanged();
    void connectionsChanged();
    void nodeAdded(ActionNode* node);
    void nodeRemoved(const QString& nodeId);
    void connectionAdded(const Connection& connection);
    void connectionRemoved(const QString& connectionId);

private:
    QList<ActionNode*> m_nodes;
    QList<Connection> m_connections;
};

#endif // ACTIONTREEDATA_H
