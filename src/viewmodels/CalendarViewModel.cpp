#include "CalendarViewModel.h"

CalendarViewModel::CalendarViewModel(EventService* eventService, EventTypeService* eventTypeService, QObject *parent)
    : QObject(parent)
    , m_eventService(eventService)
    , m_eventTypeService(eventTypeService)
    , m_selectedView("week")
{
    // Set to current week start (Monday)
    QDate today = QDate::currentDate();
    int dayOfWeek = today.dayOfWeek();
    QDate weekStart = today.addDays(1 - dayOfWeek); // Monday
    m_currentWeekStart = QDateTime(weekStart, QTime(0, 0));
}

QList<QObject*> CalendarViewModel::weekEvents()
{
    QDateTime weekEnd = m_currentWeekStart.addDays(7);
    QList<CalendarEvent*> events = m_eventService->getEventsInRange(m_currentWeekStart, weekEnd);

    QList<QObject*> result;
    for (CalendarEvent* event : events) {
        result.append(qobject_cast<QObject*>(event));
    }
    return result;
}

void CalendarViewModel::setCurrentWeekStart(const QDateTime& weekStart)
{
    if (m_currentWeekStart != weekStart) {
        m_currentWeekStart = weekStart;
        emit currentWeekStartChanged();
        emit weekEventsChanged();
    }
}

void CalendarViewModel::setSelectedView(const QString& view)
{
    if (m_selectedView != view) {
        m_selectedView = view;
        emit selectedViewChanged();
    }
}

void CalendarViewModel::navigateNextWeek()
{
    setCurrentWeekStart(m_currentWeekStart.addDays(7));
}

void CalendarViewModel::navigatePreviousWeek()
{
    setCurrentWeekStart(m_currentWeekStart.addDays(-7));
}

void CalendarViewModel::navigateToday()
{
    QDate today = QDate::currentDate();
    int dayOfWeek = today.dayOfWeek();
    QDate weekStart = today.addDays(1 - dayOfWeek);
    setCurrentWeekStart(QDateTime(weekStart, QTime(0, 0)));
}

void CalendarViewModel::createEvent(const QDateTime& start, const QDateTime& end)
{
    auto event = new CalendarEvent(m_eventService);
    event->setName("New Event");
    event->setStartTime(start);
    event->setEndTime(end);
    event->setType("default");

    m_eventService->addEvent(event);
    emit weekEventsChanged();
}

void CalendarViewModel::editEvent(const QString& id)
{
    // TODO: Open event dialog
    qDebug() << "Edit event:" << id;
}

void CalendarViewModel::deleteEvent(const QString& id)
{
    m_eventService->deleteEvent(id);
    emit weekEventsChanged();
}
