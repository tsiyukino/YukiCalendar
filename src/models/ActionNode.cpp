#include "ActionNode.h"
#include <QJsonArray>
#include <QUuid>

ActionNode::ActionNode(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_x(0.0)
    , m_y(0.0)
{
}

ActionNode::ActionNode(const QString& id, const QString& type, QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_type(type)
    , m_x(0.0)
    , m_y(0.0)
{
}

void ActionNode::setId(const QString& id)
{
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void ActionNode::setType(const QString& type)
{
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
    }
}

void ActionNode::setX(double x)
{
    if (qAbs(m_x - x) > 0.001) {
        m_x = x;
        emit xChanged();
    }
}

void ActionNode::setY(double y)
{
    if (qAbs(m_y - y) > 0.001) {
        m_y = y;
        emit yChanged();
    }
}

void ActionNode::setInputPorts(const QStringList& inputPorts)
{
    if (m_inputPorts != inputPorts) {
        m_inputPorts = inputPorts;
        emit inputPortsChanged();
    }
}

void ActionNode::setOutputPorts(const QStringList& outputPorts)
{
    if (m_outputPorts != outputPorts) {
        m_outputPorts = outputPorts;
        emit outputPortsChanged();
    }
}

void ActionNode::setParameters(const QVariantMap& parameters)
{
    if (m_parameters != parameters) {
        m_parameters = parameters;
        emit parametersChanged();
    }
}

void ActionNode::setParameter(const QString& key, const QVariant& value)
{
    m_parameters[key] = value;
    emit parametersChanged();
}

QVariant ActionNode::getParameter(const QString& key, const QVariant& defaultValue) const
{
    return m_parameters.value(key, defaultValue);
}

void ActionNode::setPosition(const QPointF& pos)
{
    setX(pos.x());
    setY(pos.y());
}

QJsonObject ActionNode::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["type"] = m_type;
    json["x"] = m_x;
    json["y"] = m_y;

    QJsonArray inputPortsArray;
    for (const QString& port : m_inputPorts) {
        inputPortsArray.append(port);
    }
    json["inputPorts"] = inputPortsArray;

    QJsonArray outputPortsArray;
    for (const QString& port : m_outputPorts) {
        outputPortsArray.append(port);
    }
    json["outputPorts"] = outputPortsArray;

    json["parameters"] = QJsonObject::fromVariantMap(m_parameters);

    return json;
}

ActionNode* ActionNode::fromJson(const QJsonObject& json, QObject *parent)
{
    auto node = new ActionNode(parent);

    node->setId(json["id"].toString());
    node->setType(json["type"].toString());
    node->setX(json["x"].toDouble());
    node->setY(json["y"].toDouble());

    QStringList inputPorts;
    QJsonArray inputPortsArray = json["inputPorts"].toArray();
    for (const QJsonValue& value : inputPortsArray) {
        inputPorts.append(value.toString());
    }
    node->setInputPorts(inputPorts);

    QStringList outputPorts;
    QJsonArray outputPortsArray = json["outputPorts"].toArray();
    for (const QJsonValue& value : outputPortsArray) {
        outputPorts.append(value.toString());
    }
    node->setOutputPorts(outputPorts);

    node->setParameters(json["parameters"].toObject().toVariantMap());

    return node;
}

// Connection implementation
QJsonObject Connection::toJson() const
{
    QJsonObject json;
    json["id"] = id;
    json["sourceNodeId"] = sourceNodeId;
    json["sourcePort"] = sourcePort;
    json["targetNodeId"] = targetNodeId;
    json["targetPort"] = targetPort;
    return json;
}

Connection Connection::fromJson(const QJsonObject& json)
{
    Connection conn;
    conn.id = json["id"].toString();
    conn.sourceNodeId = json["sourceNodeId"].toString();
    conn.sourcePort = json["sourcePort"].toString();
    conn.targetNodeId = json["targetNodeId"].toString();
    conn.targetPort = json["targetPort"].toString();
    return conn;
}
