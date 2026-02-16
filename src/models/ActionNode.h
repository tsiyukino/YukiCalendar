#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QList>
#include <QJsonObject>
#include <QPointF>

class ActionNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QStringList inputPorts READ inputPorts WRITE setInputPorts NOTIFY inputPortsChanged)
    Q_PROPERTY(QStringList outputPorts READ outputPorts WRITE setOutputPorts NOTIFY outputPortsChanged)
    Q_PROPERTY(QVariantMap parameters READ parameters WRITE setParameters NOTIFY parametersChanged)

public:
    explicit ActionNode(QObject *parent = nullptr);
    ActionNode(const QString& id, const QString& type, QObject *parent = nullptr);

    // Getters
    QString id() const { return m_id; }
    QString type() const { return m_type; }
    double x() const { return m_x; }
    double y() const { return m_y; }
    QStringList inputPorts() const { return m_inputPorts; }
    QStringList outputPorts() const { return m_outputPorts; }
    QVariantMap parameters() const { return m_parameters; }

    // Setters
    void setId(const QString& id);
    void setType(const QString& type);
    void setX(double x);
    void setY(double y);
    void setInputPorts(const QStringList& inputPorts);
    void setOutputPorts(const QStringList& outputPorts);
    void setParameters(const QVariantMap& parameters);

    // Parameter helpers
    Q_INVOKABLE void setParameter(const QString& key, const QVariant& value);
    Q_INVOKABLE QVariant getParameter(const QString& key, const QVariant& defaultValue = QVariant()) const;

    // Position helpers
    QPointF position() const { return QPointF(m_x, m_y); }
    void setPosition(const QPointF& pos);

    // Serialization
    QJsonObject toJson() const;
    static ActionNode* fromJson(const QJsonObject& json, QObject *parent = nullptr);

signals:
    void idChanged();
    void typeChanged();
    void xChanged();
    void yChanged();
    void inputPortsChanged();
    void outputPortsChanged();
    void parametersChanged();

private:
    QString m_id;
    QString m_type;
    double m_x;
    double m_y;
    QStringList m_inputPorts;
    QStringList m_outputPorts;
    QVariantMap m_parameters;
};

struct Connection
{
    QString id;
    QString sourceNodeId;
    QString sourcePort;
    QString targetNodeId;
    QString targetPort;

    QJsonObject toJson() const;
    static Connection fromJson(const QJsonObject& json);
};

#endif // ACTIONNODE_H
