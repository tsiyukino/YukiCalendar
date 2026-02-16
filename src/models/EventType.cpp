#include "EventType.h"
#include <QUuid>

EventType::EventType(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_defaultImportance(5)
    , m_defaultRecurrence(nullptr)
{
}

EventType::EventType(const QString& id, const QString& name, const QColor& color, QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_name(name)
    , m_color(color)
    , m_defaultImportance(5)
    , m_defaultRecurrence(nullptr)
{
}

void EventType::setId(const QString& id)
{
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void EventType::setName(const QString& name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void EventType::setColor(const QColor& color)
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged();
    }
}

void EventType::setDefaultImportance(int importance)
{
    if (m_defaultImportance != importance) {
        m_defaultImportance = importance;
        emit defaultImportanceChanged();
    }
}

void EventType::setDefaultRecurrence(RecurrenceRule* recurrence)
{
    if (m_defaultRecurrence != recurrence) {
        if (m_defaultRecurrence && m_defaultRecurrence->parent() == this) {
            m_defaultRecurrence->deleteLater();
        }
        m_defaultRecurrence = recurrence;
        if (m_defaultRecurrence) {
            m_defaultRecurrence->setParent(this);
        }
        emit defaultRecurrenceChanged();
    }
}

void EventType::setDefaultActionTreeId(const QString& actionTreeId)
{
    if (m_defaultActionTreeId != actionTreeId) {
        m_defaultActionTreeId = actionTreeId;
        emit defaultActionTreeIdChanged();
    }
}

QJsonObject EventType::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["name"] = m_name;
    json["color"] = m_color.name();
    json["defaultImportance"] = m_defaultImportance;

    if (m_defaultRecurrence) {
        json["defaultRecurrence"] = m_defaultRecurrence->toJson();
    }

    if (!m_defaultActionTreeId.isEmpty()) {
        json["defaultActionTreeId"] = m_defaultActionTreeId;
    }

    return json;
}

EventType* EventType::fromJson(const QJsonObject& json, QObject *parent)
{
    auto type = new EventType(parent);

    type->setId(json["id"].toString());
    type->setName(json["name"].toString());
    type->setColor(QColor(json["color"].toString()));
    type->setDefaultImportance(json["defaultImportance"].toInt(5));

    if (json.contains("defaultRecurrence")) {
        RecurrenceRule* recurrence = RecurrenceRule::fromJson(json["defaultRecurrence"].toObject(), type);
        type->setDefaultRecurrence(recurrence);
    }

    if (json.contains("defaultActionTreeId")) {
        type->setDefaultActionTreeId(json["defaultActionTreeId"].toString());
    }

    return type;
}

QList<EventType*> EventType::createDefaultTypes(QObject *parent)
{
    QList<EventType*> types;

    // Default
    auto defaultType = new EventType("default", "Default", QColor("#1976d2"), parent);
    defaultType->setDefaultImportance(5);
    types.append(defaultType);

    // Meeting
    auto meetingType = new EventType("meeting", "Meeting", QColor("#388e3c"), parent);
    meetingType->setDefaultImportance(7);
    types.append(meetingType);

    // Task
    auto taskType = new EventType("task", "Task", QColor("#f57c00"), parent);
    taskType->setDefaultImportance(6);
    types.append(taskType);

    // Reminder
    auto reminderType = new EventType("reminder", "Reminder", QColor("#d32f2f"), parent);
    reminderType->setDefaultImportance(8);
    types.append(reminderType);

    // Appointment
    auto appointmentType = new EventType("appointment", "Appointment", QColor("#7b1fa2"), parent);
    appointmentType->setDefaultImportance(9);
    types.append(appointmentType);

    return types;
}
