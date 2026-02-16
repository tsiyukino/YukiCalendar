#include "ModulesViewModel.h"

ModulesViewModel::ModulesViewModel(ModuleService* moduleService, QObject *parent)
    : QObject(parent)
    , m_moduleService(moduleService)
{
    connect(m_moduleService, &ModuleService::modulesChanged, this, &ModulesViewModel::moduleCountChanged);
}

int ModulesViewModel::moduleCount() const
{
    return m_moduleService->moduleCount();
}

void ModulesViewModel::toggleModule(const QString& moduleId)
{
    ICalendarModule* module = m_moduleService->getModule(moduleId);
    if (module) {
        if (module->isRunning()) {
            m_moduleService->stopModule(moduleId);
        } else {
            m_moduleService->startModule(moduleId);
        }
    }
}

QVariantList ModulesViewModel::getModules() const
{
    QVariantList result;
    QList<ICalendarModule*> modules = m_moduleService->getAllModules();

    for (ICalendarModule* module : modules) {
        QVariantMap moduleData;
        moduleData["id"] = module->id();
        moduleData["name"] = module->name();
        moduleData["description"] = module->description();
        moduleData["category"] = module->category();
        moduleData["isRunning"] = module->isRunning();
        result.append(moduleData);
    }

    return result;
}
