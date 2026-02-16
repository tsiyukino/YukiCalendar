#ifndef ICALENDARMODULE_H
#define ICALENDARMODULE_H

#include <QString>
#include <QVariantMap>
#include <QList>

struct ModulePort
{
    QString name;
    QString type;        // "string", "int", "DateTime", "TimeSpan", "object", "bool"
    QString description;
    bool required;

    ModulePort(const QString& n, const QString& t, const QString& d, bool r = false)
        : name(n), type(t), description(d), required(r) {}
};

class ICalendarModule
{
public:
    virtual ~ICalendarModule() = default;

    // Module metadata
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString description() const = 0;
    virtual QString category() const = 0;
    virtual bool isRunning() const = 0;

    // Port definitions
    virtual QList<ModulePort> getInputPorts() const = 0;
    virtual QList<ModulePort> getOutputPorts() const = 0;
    virtual bool hasExecutePort() const { return false; }

    // Execution
    virtual QVariantMap executeAsync(const QVariantMap& parameters) = 0;

    // Lifecycle
    virtual void startAsync() = 0;
    virtual void stopAsync() = 0;
};

#endif // ICALENDARMODULE_H
