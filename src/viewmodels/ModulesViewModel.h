#ifndef MODULESVIEWMODEL_H
#define MODULESVIEWMODEL_H

#include <QObject>
#include "services/ModuleService.h"

class ModulesViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int moduleCount READ moduleCount NOTIFY moduleCountChanged)

public:
    explicit ModulesViewModel(ModuleService* moduleService, QObject *parent = nullptr);

    int moduleCount() const;

    Q_INVOKABLE void toggleModule(const QString& moduleId);
    Q_INVOKABLE QVariantList getModules() const;

signals:
    void moduleCountChanged();

private:
    ModuleService* m_moduleService;
};

#endif // MODULESVIEWMODEL_H
