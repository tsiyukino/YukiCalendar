#include "StartActionModule.h"

StartActionModule::StartActionModule(QObject *parent)
    : QObject(parent)
    , m_isRunning(false)
{
}

QList<ModulePort> StartActionModule::getInputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("eventData", "object", "Event data object", true));
    ports.append(ModulePort("triggerType", "int", "Trigger type (0=OnEventTime, 1=BeforeEvent, 2=AfterEvent, 3=SpecificTime, 4=DayBeforeAtTime)", false));
    ports.append(ModulePort("offsetMinutes", "int", "Offset in minutes (for BeforeEvent/AfterEvent)", false));
    ports.append(ModulePort("specificTime", "DateTime", "Specific time for trigger (for SpecificTime)", false));
    ports.append(ModulePort("dayBeforeTime", "string", "Time of day before event (HH:mm format)", false));
    return ports;
}

QList<ModulePort> StartActionModule::getOutputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("eventName", "string", "Name of the event", false));
    ports.append(ModulePort("startTime", "DateTime", "Start time of the event", false));
    ports.append(ModulePort("endTime", "DateTime", "End time of the event", false));
    ports.append(ModulePort("notes", "string", "Event notes", false));
    ports.append(ModulePort("importance", "int", "Event importance", false));
    ports.append(ModulePort("executionTime", "DateTime", "Calculated execution time", false));
    return ports;
}

QVariantMap StartActionModule::executeAsync(const QVariantMap& parameters)
{
    QVariantMap outputs;

    // Extract event data
    QString eventName = parameters.value("eventName", "").toString();
    QDateTime startTime = parameters.value("startTime").toDateTime();
    QDateTime endTime = parameters.value("endTime").toDateTime();
    QString notes = parameters.value("notes", "").toString();
    int importance = parameters.value("importance", 5).toInt();

    // Calculate execution time
    QDateTime executionTime = calculateExecutionTime(parameters);

    // Set outputs
    outputs["eventName"] = eventName;
    outputs["startTime"] = startTime;
    outputs["endTime"] = endTime;
    outputs["notes"] = notes;
    outputs["importance"] = importance;
    outputs["executionTime"] = executionTime;

    return outputs;
}

void StartActionModule::startAsync()
{
    m_isRunning = true;
}

void StartActionModule::stopAsync()
{
    m_isRunning = false;
}

QDateTime StartActionModule::calculateExecutionTime(const QVariantMap& parameters) const
{
    TriggerType triggerType = static_cast<TriggerType>(parameters.value("triggerType", 0).toInt());
    QDateTime startTime = parameters.value("startTime").toDateTime();

    switch (triggerType) {
    case OnEventTime:
        return startTime;

    case BeforeEvent: {
        int offsetMinutes = parameters.value("offsetMinutes", 0).toInt();
        return startTime.addSecs(-offsetMinutes * 60);
    }

    case AfterEvent: {
        int offsetMinutes = parameters.value("offsetMinutes", 0).toInt();
        QDateTime endTime = parameters.value("endTime").toDateTime();
        return endTime.addSecs(offsetMinutes * 60);
    }

    case SpecificTime: {
        return parameters.value("specificTime").toDateTime();
    }

    case DayBeforeAtTime: {
        QString timeStr = parameters.value("dayBeforeTime", "09:00").toString();
        QTime time = QTime::fromString(timeStr, "HH:mm");
        QDateTime dayBefore = startTime.addDays(-1);
        dayBefore.setTime(time);
        return dayBefore;
    }

    default:
        return startTime;
    }
}
