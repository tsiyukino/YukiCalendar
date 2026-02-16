#ifndef ACTIONTREESCRIPTSERVICE_H
#define ACTIONTREESCRIPTSERVICE_H

#include <QObject>
#include <QString>
#include <QMap>
#include "models/ActionTreeData.h"

class ActionTreeScriptService : public QObject
{
    Q_OBJECT

public:
    explicit ActionTreeScriptService(QObject *parent = nullptr);
    ~ActionTreeScriptService();

    // Load/Save action trees
    Q_INVOKABLE ActionTreeData* loadActionTree(const QString& id);
    Q_INVOKABLE bool saveActionTree(const QString& id, ActionTreeData* tree);
    Q_INVOKABLE bool deleteActionTree(const QString& id);
    Q_INVOKABLE bool actionTreeExists(const QString& id) const;

    // List available action trees
    Q_INVOKABLE QStringList listActionTrees() const;

    // Path management
    QString scriptsPath() const { return m_scriptsPath; }
    void setScriptsPath(const QString& path);

private:
    QString m_scriptsPath;
    QMap<QString, ActionTreeData*> m_cache;

    QString getDefaultScriptsPath() const;
    QString getActionTreeFilePath(const QString& id) const;
};

#endif // ACTIONTREESCRIPTSERVICE_H
