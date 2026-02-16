#ifndef VARIABLEMODULE_H
#define VARIABLEMODULE_H

#include "ICalendarModule.h"
#include <QObject>

class VariableModule : public QObject, public ICalendarModule
{
    Q_OBJECT

public:
    explicit VariableModule(QObject *parent = nullptr);
    ~VariableModule() override = default;

    // ICalendarModule interface
    QString id() const override { return "variable"; }
    QString name() const override { return "Variable"; }
    QString description() const override { return "Outputs a constant value"; }
    QString category() const override { return "Data"; }
    bool isRunning() const override { return m_isRunning; }

    QList<ModulePort> getInputPorts() const override;
    QList<ModulePort> getOutputPorts() const override;

    QVariantMap executeAsync(const QVariantMap& parameters) override;

    void startAsync() override;
    void stopAsync() override;

private:
    bool m_isRunning;
};

#endif // VARIABLEMODULE_H
