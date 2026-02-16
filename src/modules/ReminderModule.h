#ifndef REMINDERMODULE_H
#define REMINDERMODULE_H

#include "ICalendarModule.h"
#include <QObject>
#include <QSystemTrayIcon>

class ReminderModule : public QObject, public ICalendarModule
{
    Q_OBJECT

public:
    explicit ReminderModule(QObject *parent = nullptr);
    ~ReminderModule() override;

    // ICalendarModule interface
    QString id() const override { return "reminder"; }
    QString name() const override { return "Reminder"; }
    QString description() const override { return "Sends system notifications"; }
    QString category() const override { return "Notification"; }
    bool isRunning() const override { return m_isRunning; }

    QList<ModulePort> getInputPorts() const override;
    QList<ModulePort> getOutputPorts() const override;

    QVariantMap executeAsync(const QVariantMap& parameters) override;

    void startAsync() override;
    void stopAsync() override;

private:
    bool m_isRunning;
    QSystemTrayIcon* m_trayIcon;

    void showNotification(const QString& title, const QString& message);
};

#endif // REMINDERMODULE_H
