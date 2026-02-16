#include "ModuleService.h"

ModuleService::ModuleService(QObject *parent)
    : QObject(parent)
{
}

ModuleService::~ModuleService()
{
    stopAllModules();

    // Clean up modules
    qDeleteAll(m_modules.values());
    m_modules.clear();
}

void ModuleService::registerModule(ICalendarModule* module)
{
    if (!module) {
        return;
    }

    QString moduleId = module->id();

    if (!m_modules.contains(moduleId)) {
        m_modules[moduleId] = module;
        emit modulesChanged();
        emit moduleRegistered(moduleId);
    }
}

void ModuleService::unregisterModule(const QString& moduleId)
{
    if (m_modules.contains(moduleId)) {
        ICalendarModule* module = m_modules[moduleId];

        if (module->isRunning()) {
            module->stopAsync();
        }

        m_modules.remove(moduleId);
        delete module;

        emit modulesChanged();
        emit moduleUnregistered(moduleId);
    }
}

ICalendarModule* ModuleService::getModule(const QString& moduleId) const
{
    return m_modules.value(moduleId, nullptr);
}

QList<ICalendarModule*> ModuleService::getAllModules() const
{
    return m_modules.values();
}

QList<ICalendarModule*> ModuleService::getModulesByCategory(const QString& category) const
{
    QList<ICalendarModule*> result;

    for (ICalendarModule* module : m_modules.values()) {
        if (module->category() == category) {
            result.append(module);
        }
    }

    return result;
}

void ModuleService::startModule(const QString& moduleId)
{
    ICalendarModule* module = getModule(moduleId);

    if (module && !module->isRunning()) {
        module->startAsync();
        emit moduleStatusChanged(moduleId, true);
    }
}

void ModuleService::stopModule(const QString& moduleId)
{
    ICalendarModule* module = getModule(moduleId);

    if (module && module->isRunning()) {
        module->stopAsync();
        emit moduleStatusChanged(moduleId, false);
    }
}

void ModuleService::startAllModules()
{
    for (const QString& moduleId : m_modules.keys()) {
        startModule(moduleId);
    }
}

void ModuleService::stopAllModules()
{
    for (const QString& moduleId : m_modules.keys()) {
        stopModule(moduleId);
    }
}
