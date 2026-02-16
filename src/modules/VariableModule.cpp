#include "VariableModule.h"
#include <QDateTime>

VariableModule::VariableModule(QObject *parent)
    : QObject(parent)
    , m_isRunning(false)
{
}

QList<ModulePort> VariableModule::getInputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("value", "object", "The value to output", true));
    ports.append(ModulePort("valueType", "string", "Type of the value (string, int, bool, DateTime, etc.)", false));
    return ports;
}

QList<ModulePort> VariableModule::getOutputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("output", "object", "The configured value", false));
    return ports;
}

QVariantMap VariableModule::executeAsync(const QVariantMap& parameters)
{
    QVariantMap outputs;

    QVariant value = parameters.value("value");
    QString valueType = parameters.value("valueType", "string").toString();

    // Convert value based on type if needed
    QVariant convertedValue = value;

    if (valueType == "int") {
        convertedValue = value.toInt();
    } else if (valueType == "bool") {
        convertedValue = value.toBool();
    } else if (valueType == "double") {
        convertedValue = value.toDouble();
    } else if (valueType == "string") {
        convertedValue = value.toString();
    } else if (valueType == "DateTime") {
        convertedValue = value.toDateTime();
    }

    outputs["output"] = convertedValue;
    return outputs;
}

void VariableModule::startAsync()
{
    m_isRunning = true;
}

void VariableModule::stopAsync()
{
    m_isRunning = false;
}
