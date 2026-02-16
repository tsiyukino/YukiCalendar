#ifndef EVENTTYPE_H
#define EVENTTYPE_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QJsonObject>
#include "RecurrenceRule.h"

class EventType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int defaultImportance READ defaultImportance WRITE setDefaultImportance NOTIFY defaultImportanceChanged)
    Q_PROPERTY(RecurrenceRule* defaultRecurrence READ defaultRecurrence WRITE setDefaultRecurrence NOTIFY defaultRecurrenceChanged)
    Q_PROPERTY(QString defaultActionTreeId READ defaultActionTreeId WRITE setDefaultActionTreeId NOTIFY defaultActionTreeIdChanged)

public:
    explicit EventType(QObject *parent = nullptr);
    EventType(const QString& id, const QString& name, const QColor& color, QObject *parent = nullptr);

    // Getters
    QString id() const { return m_id; }
    QString name() const { return m_name; }
    QColor color() const { return m_color; }
    int defaultImportance() const { return m_defaultImportance; }
    RecurrenceRule* defaultRecurrence() const { return m_defaultRecurrence; }
    QString defaultActionTreeId() const { return m_defaultActionTreeId; }

    // Setters
    void setId(const QString& id);
    void setName(const QString& name);
    void setColor(const QColor& color);
    void setDefaultImportance(int importance);
    void setDefaultRecurrence(RecurrenceRule* recurrence);
    void setDefaultActionTreeId(const QString& actionTreeId);

    // Serialization
    QJsonObject toJson() const;
    static EventType* fromJson(const QJsonObject& json, QObject *parent = nullptr);

    // Create default types
    static QList<EventType*> createDefaultTypes(QObject *parent = nullptr);

signals:
    void idChanged();
    void nameChanged();
    void colorChanged();
    void defaultImportanceChanged();
    void defaultRecurrenceChanged();
    void defaultActionTreeIdChanged();

private:
    QString m_id;
    QString m_name;
    QColor m_color;
    int m_defaultImportance;
    RecurrenceRule* m_defaultRecurrence;
    QString m_defaultActionTreeId;
};

#endif // EVENTTYPE_H
