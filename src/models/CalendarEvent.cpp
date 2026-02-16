#include "CalendarEvent.h"
#include <QUuid>

CalendarEvent::CalendarEvent(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_type("default")
    , m_importance(5)
    , m_recurrence(nullptr)
    , m_actionTree(nullptr)
    , m_useTypeDefaults(true)
    , m_isNew(false)
    , m_isDragging(false)
    , m_column(0)
    , m_totalColumns(1)
    , m_widthFraction(1.0)
    , m_offsetFraction(0.0)
{
}

CalendarEvent::CalendarEvent(const QString& id, const QString& name, const QDateTime& startTime, const QDateTime& endTime, QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_name(name)
    , m_startTime(startTime)
    , m_endTime(endTime)
    , m_type("default")
    , m_importance(5)
    , m_recurrence(nullptr)
    , m_actionTree(nullptr)
    , m_useTypeDefaults(true)
    , m_isNew(false)
    , m_isDragging(false)
    , m_column(0)
    , m_totalColumns(1)
    , m_widthFraction(1.0)
    , m_offsetFraction(0.0)
{
}

void CalendarEvent::setId(const QString& id)
{
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void CalendarEvent::setName(const QString& name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void CalendarEvent::setStartTime(const QDateTime& startTime)
{
    if (m_startTime != startTime) {
        m_startTime = startTime;
        emit startTimeChanged();
    }
}

void CalendarEvent::setEndTime(const QDateTime& endTime)
{
    if (m_endTime != endTime) {
        m_endTime = endTime;
        emit endTimeChanged();
    }
}

void CalendarEvent::setType(const QString& type)
{
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
    }
}

void CalendarEvent::setImportance(int importance)
{
    if (m_importance != importance) {
        m_importance = importance;
        emit importanceChanged();
    }
}

void CalendarEvent::setNotes(const QString& notes)
{
    if (m_notes != notes) {
        m_notes = notes;
        emit notesChanged();
    }
}

void CalendarEvent::setRecurrence(RecurrenceRule* recurrence)
{
    if (m_recurrence != recurrence) {
        if (m_recurrence && m_recurrence->parent() == this) {
            m_recurrence->deleteLater();
        }
        m_recurrence = recurrence;
        if (m_recurrence) {
            m_recurrence->setParent(this);
        }
        emit recurrenceChanged();
    }
}

void CalendarEvent::setActionTree(ActionTreeData* actionTree)
{
    if (m_actionTree != actionTree) {
        if (m_actionTree && m_actionTree->parent() == this) {
            m_actionTree->deleteLater();
        }
        m_actionTree = actionTree;
        if (m_actionTree) {
            m_actionTree->setParent(this);
        }
        emit actionTreeChanged();
    }
}

void CalendarEvent::setUseTypeDefaults(bool useDefaults)
{
    if (m_useTypeDefaults != useDefaults) {
        m_useTypeDefaults = useDefaults;
        emit useTypeDefaultsChanged();
    }
}

void CalendarEvent::setIsNew(bool isNew)
{
    if (m_isNew != isNew) {
        m_isNew = isNew;
        emit isNewChanged();
    }
}

void CalendarEvent::setIsDragging(bool isDragging)
{
    if (m_isDragging != isDragging) {
        m_isDragging = isDragging;
        emit isDraggingChanged();
    }
}

void CalendarEvent::setColumn(int column)
{
    if (m_column != column) {
        m_column = column;
        emit columnChanged();
    }
}

void CalendarEvent::setTotalColumns(int totalColumns)
{
    if (m_totalColumns != totalColumns) {
        m_totalColumns = totalColumns;
        emit totalColumnsChanged();
    }
}

void CalendarEvent::setWidthFraction(double widthFraction)
{
    if (qAbs(m_widthFraction - widthFraction) > 0.001) {
        m_widthFraction = widthFraction;
        emit widthFractionChanged();
    }
}

void CalendarEvent::setOffsetFraction(double offsetFraction)
{
    if (qAbs(m_offsetFraction - offsetFraction) > 0.001) {
        m_offsetFraction = offsetFraction;
        emit offsetFractionChanged();
    }
}

qint64 CalendarEvent::durationMinutes() const
{
    return m_startTime.secsTo(m_endTime) / 60;
}

QJsonObject CalendarEvent::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["name"] = m_name;
    json["startTime"] = m_startTime.toString(Qt::ISODate);
    json["endTime"] = m_endTime.toString(Qt::ISODate);
    json["type"] = m_type;
    json["importance"] = m_importance;
    json["notes"] = m_notes;
    json["useTypeDefaults"] = m_useTypeDefaults;

    if (m_recurrence) {
        json["recurrence"] = m_recurrence->toJson();
    }

    if (m_actionTree) {
        json["actionTree"] = m_actionTree->toJson();
    }

    return json;
}

CalendarEvent* CalendarEvent::fromJson(const QJsonObject& json, QObject *parent)
{
    auto event = new CalendarEvent(parent);

    event->setId(json["id"].toString());
    event->setName(json["name"].toString());
    event->setStartTime(QDateTime::fromString(json["startTime"].toString(), Qt::ISODate));
    event->setEndTime(QDateTime::fromString(json["endTime"].toString(), Qt::ISODate));
    event->setType(json["type"].toString("default"));
    event->setImportance(json["importance"].toInt(5));
    event->setNotes(json["notes"].toString());
    event->setUseTypeDefaults(json["useTypeDefaults"].toBool(true));

    if (json.contains("recurrence")) {
        RecurrenceRule* recurrence = RecurrenceRule::fromJson(json["recurrence"].toObject(), event);
        event->setRecurrence(recurrence);
    }

    if (json.contains("actionTree")) {
        ActionTreeData* actionTree = ActionTreeData::fromJson(json["actionTree"].toObject(), event);
        event->setActionTree(actionTree);
    }

    return event;
}
