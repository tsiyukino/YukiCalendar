#include "EventLayoutCalculator.h"
#include <algorithm>

QList<EventLayout> EventLayoutCalculator::calculateLayouts(QList<CalendarEvent*> events)
{
    QList<EventLayout> layouts;

    if (events.isEmpty()) {
        return layouts;
    }

    // Sort events by start time
    std::sort(events.begin(), events.end(), [](CalendarEvent* a, CalendarEvent* b) {
        return a->startTime() < b->startTime();
    });

    // Group overlapping events
    QList<QList<CalendarEvent*>> groups = groupOverlappingEvents(events);

    // Calculate layout for each group
    for (const auto& group : groups) {
        QList<EventLayout> groupLayouts = assignColumns(group);
        layouts.append(groupLayouts);
    }

    return layouts;
}

bool EventLayoutCalculator::eventsOverlap(CalendarEvent* event1, CalendarEvent* event2)
{
    return event1->startTime() < event2->endTime() && event2->startTime() < event1->endTime();
}

QList<QList<CalendarEvent*>> EventLayoutCalculator::groupOverlappingEvents(QList<CalendarEvent*> events)
{
    QList<QList<CalendarEvent*>> groups;

    for (CalendarEvent* event : events) {
        bool addedToGroup = false;

        for (auto& group : groups) {
            // Check if event overlaps with any event in this group
            bool overlapsWithGroup = false;
            for (CalendarEvent* groupEvent : group) {
                if (eventsOverlap(event, groupEvent)) {
                    overlapsWithGroup = true;
                    break;
                }
            }

            if (overlapsWithGroup) {
                group.append(event);
                addedToGroup = true;
                break;
            }
        }

        if (!addedToGroup) {
            QList<CalendarEvent*> newGroup;
            newGroup.append(event);
            groups.append(newGroup);
        }
    }

    return groups;
}

QList<EventLayout> EventLayoutCalculator::assignColumns(const QList<CalendarEvent*>& group)
{
    QList<EventLayout> layouts;

    if (group.isEmpty()) {
        return layouts;
    }

    if (group.size() == 1) {
        EventLayout layout;
        layout.event = group[0];
        layout.column = 0;
        layout.totalColumns = 1;
        layout.widthFraction = 1.0;
        layout.offsetFraction = 0.0;
        layouts.append(layout);
        return layouts;
    }

    // Track which columns are occupied at each time point
    QList<CalendarEvent*> sortedEvents = group;
    std::sort(sortedEvents.begin(), sortedEvents.end(), [](CalendarEvent* a, CalendarEvent* b) {
        return a->startTime() < b->startTime();
    });

    QList<QList<CalendarEvent*>> columns;
    int maxColumns = 0;

    for (CalendarEvent* event : sortedEvents) {
        int assignedColumn = -1;

        // Find the first available column
        for (int col = 0; col < columns.size(); ++col) {
            bool columnAvailable = true;

            for (CalendarEvent* colEvent : columns[col]) {
                if (eventsOverlap(event, colEvent)) {
                    columnAvailable = false;
                    break;
                }
            }

            if (columnAvailable) {
                assignedColumn = col;
                break;
            }
        }

        // If no available column found, create a new one
        if (assignedColumn == -1) {
            QList<CalendarEvent*> newColumn;
            newColumn.append(event);
            columns.append(newColumn);
            assignedColumn = columns.size() - 1;
        } else {
            columns[assignedColumn].append(event);
        }

        maxColumns = std::max(maxColumns, static_cast<int>(columns.size()));

        EventLayout layout;
        layout.event = event;
        layout.column = assignedColumn;
        layout.totalColumns = 0; // Will be updated below
        layout.widthFraction = 0.0; // Will be updated below
        layout.offsetFraction = 0.0; // Will be updated below
        layouts.append(layout);
    }

    // Update total columns and calculate fractions
    for (auto& layout : layouts) {
        layout.totalColumns = maxColumns;
        layout.widthFraction = 1.0 / maxColumns;
        layout.offsetFraction = static_cast<double>(layout.column) / maxColumns;
    }

    return layouts;
}
