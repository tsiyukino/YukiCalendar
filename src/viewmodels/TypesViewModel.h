#ifndef TYPESVIEWMODEL_H
#define TYPESVIEWMODEL_H

#include <QObject>
#include "services/EventTypeService.h"

class TypesViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int typeCount READ typeCount NOTIFY typeCountChanged)

public:
    explicit TypesViewModel(EventTypeService* typeService, QObject *parent = nullptr);

    int typeCount() const;

    Q_INVOKABLE QVariantList getTypes() const;
    Q_INVOKABLE void addType(const QString& name, const QString& color);
    Q_INVOKABLE void deleteType(const QString& id);

signals:
    void typeCountChanged();

private:
    EventTypeService* m_typeService;
};

#endif // TYPESVIEWMODEL_H
