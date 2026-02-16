#ifndef STARTACTIONMODULE_H
#define STARTACTIONMODULE_H

#include "ICalendarModule.h"
#include <QObject>
#include <QDateTime>

class StartActionModule : public QObject, public ICalendarModule
{
    Q_OBJECT

public:
    enum TriggerType {
        OnEventTime = 0,
        BeforeEvent = 1,
        AfterEvent = 2,
        SpecificTime = 3,
        DayBeforeAtTime = 4
    };

    explicit StartActionModule(QObject *parent = nullptr);
    ~StartActionModule() override = default;

    // ICalendarModule interface
    QString id() const override { return "start-action"; }
    QString name() const override { return "Start Action"; }
    QString description() const override { return "Starting point for action tree execution"; }
    QString category() const override { return "Control"; }
    bool isRunning() const override { return m_isRunning; }

    QList<ModulePort> getInputPorts() const override;
    QList<ModulePort> getOutputPorts() const override;
    bool hasExecutePort() const override { return true; }

    QVariantMap executeAsync(const QVariantMap& parameters) override;

    void startAsync() override;
    void stopAsync() override;

private:
    bool m_isRunning;

    QDateTime calculateExecutionTime(const QVariantMap& parameters) const;
};

#endif // STARTACTIONMODULE_H
