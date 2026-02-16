#ifndef EVENTLAYOUTCALCULATOR_H
#define EVENTLAYOUTCALCULATOR_H

#include <QList>
#include <QDateTime>
#include "models/CalendarEvent.h"

struct EventLayout
{
    CalendarEvent* event;
    int column;
    int totalColumns;
    double widthFraction;
    double offsetFraction;
};

class EventLayoutCalculator
{
public:
    // Calculate layout for events with overlaps
    static QList<EventLayout> calculateLayouts(QList<CalendarEvent*> events);

    // Check if two events overlap
    static bool eventsOverlap(CalendarEvent* event1, CalendarEvent* event2);

private:
    // Group overlapping events
    static QList<QList<CalendarEvent*>> groupOverlappingEvents(QList<CalendarEvent*> events);

    // Assign columns to events in a group
    static QList<EventLayout> assignColumns(const QList<CalendarEvent*>& group);
};

#endif // EVENTLAYOUTCALCULATOR_H
