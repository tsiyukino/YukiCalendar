#include "ActionTreeScriptService.h"
#include "utils/JsonSerializer.h"
#include <QDir>
#include <QStandardPaths>
#include <QFileInfo>

ActionTreeScriptService::ActionTreeScriptService(QObject *parent)
    : QObject(parent)
{
    m_scriptsPath = getDefaultScriptsPath();

    // Ensure scripts directory exists
    QDir dir(m_scriptsPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

ActionTreeScriptService::~ActionTreeScriptService()
{
    qDeleteAll(m_cache.values());
    m_cache.clear();
}

ActionTreeData* ActionTreeScriptService::loadActionTree(const QString& id)
{
    // Check cache first
    if (m_cache.contains(id)) {
        return m_cache[id];
    }

    QString filePath = getActionTreeFilePath(id);
    QFileInfo fileInfo(filePath);

    if (!fileInfo.exists()) {
        return nullptr;
    }

    QJsonObject json = JsonSerializer::loadObjectFromFile(filePath);
    ActionTreeData* tree = ActionTreeData::fromJson(json, this);

    // Cache the loaded tree
    m_cache[id] = tree;

    return tree;
}

bool ActionTreeScriptService::saveActionTree(const QString& id, ActionTreeData* tree)
{
    if (!tree) {
        return false;
    }

    QString filePath = getActionTreeFilePath(id);
    QJsonObject json = tree->toJson();

    bool success = JsonSerializer::saveToFile(filePath, json);

    if (success) {
        // Update cache
        if (m_cache.contains(id) && m_cache[id] != tree) {
            m_cache[id]->deleteLater();
        }
        m_cache[id] = tree;
        tree->setParent(this);
    }

    return success;
}

bool ActionTreeScriptService::deleteActionTree(const QString& id)
{
    QString filePath = getActionTreeFilePath(id);
    QFile file(filePath);

    // Remove from cache
    if (m_cache.contains(id)) {
        m_cache[id]->deleteLater();
        m_cache.remove(id);
    }

    return file.remove();
}

bool ActionTreeScriptService::actionTreeExists(const QString& id) const
{
    QString filePath = getActionTreeFilePath(id);
    return QFileInfo::exists(filePath);
}

QStringList ActionTreeScriptService::listActionTrees() const
{
    QStringList result;
    QDir dir(m_scriptsPath);

    QStringList filters;
    filters << "*.json";

    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);

    for (const QFileInfo& fileInfo : files) {
        result.append(fileInfo.baseName());
    }

    return result;
}

void ActionTreeScriptService::setScriptsPath(const QString& path)
{
    if (m_scriptsPath != path) {
        m_scriptsPath = path;

        // Clear cache when path changes
        qDeleteAll(m_cache.values());
        m_cache.clear();

        // Ensure new directory exists
        QDir dir(m_scriptsPath);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
    }
}

QString ActionTreeScriptService::getDefaultScriptsPath() const
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation);

    return dir.filePath("scripts");
}

QString ActionTreeScriptService::getActionTreeFilePath(const QString& id) const
{
    return QDir(m_scriptsPath).filePath(id + ".json");
}
