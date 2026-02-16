#include "EventService.h"
#include "utils/JsonSerializer.h"
#include <QDir>
#include <QJsonArray>
#include <algorithm>

EventService::EventService(QObject *parent)
    : QObject(parent)
{
    m_dataPath = getDefaultDataPath();
    loadFromDisk();
}

EventService::~EventService()
{
    saveToDisk();
    qDeleteAll(m_events);
    m_events.clear();
}

void EventService::addEvent(CalendarEvent* event)
{
    if (!event) {
        return;
    }

    // Check if event already exists
    auto it = std::find_if(m_events.begin(), m_events.end(),
                           [event](CalendarEvent* e) { return e->id() == event->id(); });

    if (it == m_events.end()) {
        event->setParent(this);
        m_events.append(event);
        emit eventsChanged();
        emit eventAdded(event);
        saveToDisk();
    }
}

void EventService::updateEvent(CalendarEvent* event)
{
    if (!event) {
        return;
    }

    auto it = std::find_if(m_events.begin(), m_events.end(),
                           [event](CalendarEvent* e) { return e->id() == event->id(); });

    if (it != m_events.end()) {
        emit eventsChanged();
        emit eventUpdated(event);
        saveToDisk();
    }
}

void EventService::deleteEvent(const QString& id)
{
    auto it = std::find_if(m_events.begin(), m_events.end(),
                           [&id](CalendarEvent* e) { return e->id() == id; });

    if (it != m_events.end()) {
        CalendarEvent* event = *it;
        m_events.erase(it);
        emit eventsChanged();
        emit eventDeleted(id);
        saveToDisk();
        event->deleteLater();
    }
}

CalendarEvent* EventService::getEvent(const QString& id) const
{
    auto it = std::find_if(m_events.begin(), m_events.end(),
                           [&id](CalendarEvent* e) { return e->id() == id; });

    return (it != m_events.end()) ? *it : nullptr;
}

QList<CalendarEvent*> EventService::getEventsInRange(const QDateTime& start, const QDateTime& end)
{
    QList<CalendarEvent*> result;

    for (CalendarEvent* event : m_events) {
        if (!event->recurrence() || event->recurrence()->type() == RecurrenceRule::None) {
            // Non-recurring event
            if (event->startTime() <= end && event->endTime() >= start) {
                result.append(event);
            }
        } else {
            // Recurring event - get occurrences
            QList<QDateTime> occurrences = event->recurrence()->calculateOccurrences(
                event->startTime(), start, end);

            if (!occurrences.isEmpty()) {
                result.append(event);
            }
        }
    }

    return result;
}

QList<CalendarEvent*> EventService::getEventOccurrences(const QString& id, const QDateTime& start, const QDateTime& end)
{
    QList<CalendarEvent*> result;
    CalendarEvent* event = getEvent(id);

    if (!event) {
        return result;
    }

    if (!event->recurrence() || event->recurrence()->type() == RecurrenceRule::None) {
        // Non-recurring event
        if (event->startTime() <= end && event->endTime() >= start) {
            result.append(event);
        }
    } else {
        // For recurring events, we would create virtual events for each occurrence
        // For now, just return the original event
        result.append(event);
    }

    return result;
}

bool EventService::save()
{
    saveToDisk();
    return true;
}

bool EventService::load()
{
    loadFromDisk();
    return true;
}

void EventService::setDataPath(const QString& path)
{
    if (m_dataPath != path) {
        m_dataPath = path;
        loadFromDisk();
    }
}

void EventService::loadFromDisk()
{
    QDir dir(QFileInfo(m_dataPath).dir());
    if (!dir.exists()) {
        return;
    }

    QJsonArray eventsArray = JsonSerializer::loadArrayFromFile(m_dataPath);

    qDeleteAll(m_events);
    m_events.clear();

    for (const QJsonValue& value : eventsArray) {
        CalendarEvent* event = CalendarEvent::fromJson(value.toObject(), this);
        m_events.append(event);
    }

    emit eventsChanged();
}

void EventService::saveToDisk()
{
    QJsonArray eventsArray;

    for (const CalendarEvent* event : m_events) {
        eventsArray.append(event->toJson());
    }

    JsonSerializer::saveToFile(m_dataPath, eventsArray);
}

QString EventService::getDefaultDataPath() const
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation);

    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return dir.filePath("events.json");
}
