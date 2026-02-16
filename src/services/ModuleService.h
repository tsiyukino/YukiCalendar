#ifndef MODULESERVICE_H
#define MODULESERVICE_H

#include <QObject>
#include <QMap>
#include <QString>
#include "modules/ICalendarModule.h"

class ModuleService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int moduleCount READ moduleCount NOTIFY modulesChanged)

public:
    explicit ModuleService(QObject *parent = nullptr);
    ~ModuleService();

    // Module registration
    Q_INVOKABLE void registerModule(ICalendarModule* module);
    Q_INVOKABLE void unregisterModule(const QString& moduleId);

    // Module access
    Q_INVOKABLE ICalendarModule* getModule(const QString& moduleId) const;
    Q_INVOKABLE QList<ICalendarModule*> getAllModules() const;
    Q_INVOKABLE QList<ICalendarModule*> getModulesByCategory(const QString& category) const;

    int moduleCount() const { return m_modules.size(); }

    // Module lifecycle
    Q_INVOKABLE void startModule(const QString& moduleId);
    Q_INVOKABLE void stopModule(const QString& moduleId);
    Q_INVOKABLE void startAllModules();
    Q_INVOKABLE void stopAllModules();

signals:
    void modulesChanged();
    void moduleRegistered(const QString& moduleId);
    void moduleUnregistered(const QString& moduleId);
    void moduleStatusChanged(const QString& moduleId, bool isRunning);

private:
    QMap<QString, ICalendarModule*> m_modules;
};

#endif // MODULESERVICE_H
