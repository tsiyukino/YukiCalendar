#include "TestRunner.h"
#include "utils/EventLayoutCalculator.h"
#include "models/RecurrenceRule.h"
#include <QDateTime>

TestRunner::TestRunner(EventService* eventService, ModuleService* moduleService, QObject *parent)
    : QObject(parent)
    , m_eventService(eventService)
    , m_moduleService(moduleService)
{
}

void TestRunner::runLayoutTest()
{
    clearResults();
    appendResult("=== Event Layout Test ===");

    // Create 10 overlapping events
    QList<CalendarEvent*> events;
    QDateTime baseTime = QDateTime::currentDateTime();

    for (int i = 0; i < 10; ++i) {
        auto event = new CalendarEvent(this);
        event->setName(QString("Event %1").arg(i + 1));
        event->setStartTime(baseTime.addSecs(i * 1800)); // 30 min intervals
        event->setEndTime(baseTime.addSecs(i * 1800 + 3600)); // 1 hour duration
        events.append(event);
    }

    QList<EventLayout> layouts = EventLayoutCalculator::calculateLayouts(events);

    appendResult(QString("Created %1 events").arg(events.size()));
    appendResult(QString("Calculated %1 layouts").arg(layouts.size()));

    for (const EventLayout& layout : layouts) {
        appendResult(QString("  %1: column=%2/%3")
                     .arg(layout.event->name())
                     .arg(layout.column)
                     .arg(layout.totalColumns));
    }

    appendResult("✅ Layout test completed");
}

void TestRunner::runActionTreeTest()
{
    clearResults();
    appendResult("=== Action Tree Test ===");
    appendResult("⚠️ Not yet implemented");
}

void TestRunner::runRecurrenceTest()
{
    clearResults();
    appendResult("=== Recurrence Test ===");

    RecurrenceRule* rule = new RecurrenceRule(this);
    rule->setType(RecurrenceRule::Daily);
    rule->setInterval(1);

    QDateTime start = QDateTime::currentDateTime();
    QDateTime rangeStart = start;
    QDateTime rangeEnd = start.addDays(30);

    QList<QDateTime> occurrences = rule->calculateOccurrences(start, rangeStart, rangeEnd);

    appendResult(QString("Daily recurrence for 30 days"));
    appendResult(QString("Generated %1 occurrences").arg(occurrences.size()));

    if (occurrences.size() > 0) {
        appendResult(QString("First: %1").arg(occurrences.first().toString()));
        appendResult(QString("Last: %1").arg(occurrences.last().toString()));
    }

    appendResult("✅ Recurrence test completed");
}

void TestRunner::runAnimationTest()
{
    clearResults();
    appendResult("=== Animation Test ===");
    appendResult("⚠️ Not yet implemented (requires QML integration)");
}

void TestRunner::runAllTests()
{
    runLayoutTest();
    appendResult("");
    runRecurrenceTest();
    appendResult("");
    runActionTreeTest();
    appendResult("");
    runAnimationTest();
}

void TestRunner::appendResult(const QString& message)
{
    if (!m_results.isEmpty()) {
        m_results += "\n";
    }
    m_results += message;
    emit resultsChanged();
}

void TestRunner::clearResults()
{
    m_results.clear();
    emit resultsChanged();
}
