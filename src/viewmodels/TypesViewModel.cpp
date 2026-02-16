#include "TypesViewModel.h"

TypesViewModel::TypesViewModel(EventTypeService* typeService, QObject *parent)
    : QObject(parent)
    , m_typeService(typeService)
{
    connect(m_typeService, &EventTypeService::typesChanged, this, &TypesViewModel::typeCountChanged);
}

int TypesViewModel::typeCount() const
{
    return m_typeService->typeCount();
}

QVariantList TypesViewModel::getTypes() const
{
    QVariantList result;
    QList<EventType*> types = m_typeService->getAllTypes();

    for (EventType* type : types) {
        QVariantMap typeData;
        typeData["id"] = type->id();
        typeData["name"] = type->name();
        typeData["color"] = type->color().name();
        typeData["defaultImportance"] = type->defaultImportance();
        result.append(typeData);
    }

    return result;
}

void TypesViewModel::addType(const QString& name, const QString& color)
{
    auto type = new EventType(m_typeService);
    type->setName(name);
    type->setColor(QColor(color));
    m_typeService->addType(type);
}

void TypesViewModel::deleteType(const QString& id)
{
    m_typeService->deleteType(id);
}
