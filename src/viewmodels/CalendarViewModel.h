#ifndef CALENDARVIEWMODEL_H
#define CALENDARVIEWMODEL_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include "services/EventService.h"
#include "services/EventTypeService.h"

class CalendarViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime currentWeekStart READ currentWeekStart WRITE setCurrentWeekStart NOTIFY currentWeekStartChanged)
    Q_PROPERTY(QList<QObject*> weekEvents READ weekEvents NOTIFY weekEventsChanged)
    Q_PROPERTY(QString selectedView READ selectedView WRITE setSelectedView NOTIFY selectedViewChanged)

public:
    explicit CalendarViewModel(EventService* eventService, EventTypeService* eventTypeService, QObject *parent = nullptr);

    QDateTime currentWeekStart() const { return m_currentWeekStart; }
    QList<QObject*> weekEvents();
    QString selectedView() const { return m_selectedView; }

    void setCurrentWeekStart(const QDateTime& weekStart);
    void setSelectedView(const QString& view);

    Q_INVOKABLE void navigateNextWeek();
    Q_INVOKABLE void navigatePreviousWeek();
    Q_INVOKABLE void navigateToday();
    Q_INVOKABLE void createEvent(const QDateTime& start, const QDateTime& end);
    Q_INVOKABLE void editEvent(const QString& id);
    Q_INVOKABLE void deleteEvent(const QString& id);

signals:
    void currentWeekStartChanged();
    void weekEventsChanged();
    void selectedViewChanged();

private:
    EventService* m_eventService;
    EventTypeService* m_eventTypeService;
    QDateTime m_currentWeekStart;
    QString m_selectedView;
};

#endif // CALENDARVIEWMODEL_H
