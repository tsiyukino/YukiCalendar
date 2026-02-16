#ifndef EVENTSERVICE_H
#define EVENTSERVICE_H

#include <QObject>
#include <QList>
#include <QDateTime>
#include <QString>
#include <QStandardPaths>
#include "models/CalendarEvent.h"

class EventService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int eventCount READ eventCount NOTIFY eventsChanged)

public:
    explicit EventService(QObject *parent = nullptr);
    ~EventService();

    // CRUD operations
    Q_INVOKABLE void addEvent(CalendarEvent* event);
    Q_INVOKABLE void updateEvent(CalendarEvent* event);
    Q_INVOKABLE void deleteEvent(const QString& id);
    Q_INVOKABLE CalendarEvent* getEvent(const QString& id) const;

    // Query operations
    Q_INVOKABLE QList<CalendarEvent*> getEventsInRange(const QDateTime& start, const QDateTime& end);
    Q_INVOKABLE QList<CalendarEvent*> getEventOccurrences(const QString& id, const QDateTime& start, const QDateTime& end);
    Q_INVOKABLE QList<CalendarEvent*> getAllEvents() const { return m_events; }

    int eventCount() const { return m_events.size(); }

    // Persistence
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool load();

    // Data path
    QString dataPath() const { return m_dataPath; }
    void setDataPath(const QString& path);

signals:
    void eventsChanged();
    void eventAdded(CalendarEvent* event);
    void eventUpdated(CalendarEvent* event);
    void eventDeleted(const QString& id);

private:
    QList<CalendarEvent*> m_events;
    QString m_dataPath;

    void loadFromDisk();
    void saveToDisk();
    QString getDefaultDataPath() const;
};

#endif // EVENTSERVICE_H
