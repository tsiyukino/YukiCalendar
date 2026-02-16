#ifndef EVENTTYPESERVICE_H
#define EVENTTYPESERVICE_H

#include <QObject>
#include <QList>
#include <QString>
#include "models/EventType.h"

class EventTypeService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int typeCount READ typeCount NOTIFY typesChanged)

public:
    explicit EventTypeService(QObject *parent = nullptr);
    ~EventTypeService();

    // CRUD operations
    Q_INVOKABLE void addType(EventType* type);
    Q_INVOKABLE void updateType(EventType* type);
    Q_INVOKABLE void deleteType(const QString& id);
    Q_INVOKABLE EventType* getType(const QString& id) const;
    Q_INVOKABLE QList<EventType*> getAllTypes() const { return m_types; }

    int typeCount() const { return m_types.size(); }

    // Persistence
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool load();

    // Initialize default types
    Q_INVOKABLE void initializeDefaults();

    // Data path
    QString dataPath() const { return m_dataPath; }
    void setDataPath(const QString& path);

signals:
    void typesChanged();
    void typeAdded(EventType* type);
    void typeUpdated(EventType* type);
    void typeDeleted(const QString& id);

private:
    QList<EventType*> m_types;
    QString m_dataPath;

    void loadFromDisk();
    void saveToDisk();
    QString getDefaultDataPath() const;
};

#endif // EVENTTYPESERVICE_H
