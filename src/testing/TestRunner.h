#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>
#include <QString>
#include "services/EventService.h"
#include "services/ModuleService.h"

class TestRunner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString results READ results NOTIFY resultsChanged)

public:
    explicit TestRunner(EventService* eventService, ModuleService* moduleService, QObject *parent = nullptr);

    QString results() const { return m_results; }

    Q_INVOKABLE void runLayoutTest();
    Q_INVOKABLE void runActionTreeTest();
    Q_INVOKABLE void runRecurrenceTest();
    Q_INVOKABLE void runAnimationTest();
    Q_INVOKABLE void runAllTests();

signals:
    void resultsChanged();

private:
    EventService* m_eventService;
    ModuleService* m_moduleService;
    QString m_results;

    void appendResult(const QString& message);
    void clearResults();
};

#endif // TESTRUNNER_H
