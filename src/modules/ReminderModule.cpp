#include "ReminderModule.h"
#include <QApplication>
#include <QStyle>

ReminderModule::ReminderModule(QObject *parent)
    : QObject(parent)
    , m_isRunning(false)
    , m_trayIcon(nullptr)
{
}

ReminderModule::~ReminderModule()
{
    if (m_trayIcon) {
        delete m_trayIcon;
        m_trayIcon = nullptr;
    }
}

QList<ModulePort> ReminderModule::getInputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("Execute", "execute", "Execution trigger", false));
    ports.append(ModulePort("title", "string", "Notification title", true));
    ports.append(ModulePort("message", "string", "Notification message", true));
    ports.append(ModulePort("time", "DateTime", "Scheduled time (optional)", false));
    return ports;
}

QList<ModulePort> ReminderModule::getOutputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("Execute", "execute", "Execute next action", false));
    ports.append(ModulePort("success", "bool", "Whether notification was sent", false));
    return ports;
}

QVariantMap ReminderModule::executeAsync(const QVariantMap& parameters)
{
    QVariantMap outputs;

    QString title = parameters.value("title", "YukiCalendar").toString();
    QString message = parameters.value("message", "Reminder").toString();

    showNotification(title, message);

    outputs["success"] = true;
    return outputs;
}

void ReminderModule::startAsync()
{
    m_isRunning = true;

    // Create system tray icon if it doesn't exist
    if (!m_trayIcon) {
        m_trayIcon = new QSystemTrayIcon(this);
        QIcon trayIcon(":/icons/tray-icon.png");
        if (!trayIcon.isNull()) {
            m_trayIcon->setIcon(trayIcon);
        } else {
            // Fallback to default icon
            m_trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation));
        }
        m_trayIcon->show();
    }
}

void ReminderModule::stopAsync()
{
    m_isRunning = false;

    if (m_trayIcon) {
        m_trayIcon->hide();
    }
}

void ReminderModule::showNotification(const QString& title, const QString& message)
{
    if (!m_trayIcon) {
        startAsync();
    }

    if (m_trayIcon && QSystemTrayIcon::isSystemTrayAvailable()) {
        m_trayIcon->showMessage(title, message, QSystemTrayIcon::Information, 5000);
    }
}
