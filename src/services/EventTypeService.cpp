#include "EventTypeService.h"
#include "utils/JsonSerializer.h"
#include <QDir>
#include <QStandardPaths>
#include <QJsonArray>
#include <algorithm>

EventTypeService::EventTypeService(QObject *parent)
    : QObject(parent)
{
    m_dataPath = getDefaultDataPath();
    loadFromDisk();

    // Initialize defaults if no types exist
    if (m_types.isEmpty()) {
        initializeDefaults();
    }
}

EventTypeService::~EventTypeService()
{
    saveToDisk();
    qDeleteAll(m_types);
    m_types.clear();
}

void EventTypeService::addType(EventType* type)
{
    if (!type) {
        return;
    }

    auto it = std::find_if(m_types.begin(), m_types.end(),
                           [type](EventType* t) { return t->id() == type->id(); });

    if (it == m_types.end()) {
        type->setParent(this);
        m_types.append(type);
        emit typesChanged();
        emit typeAdded(type);
        saveToDisk();
    }
}

void EventTypeService::updateType(EventType* type)
{
    if (!type) {
        return;
    }

    auto it = std::find_if(m_types.begin(), m_types.end(),
                           [type](EventType* t) { return t->id() == type->id(); });

    if (it != m_types.end()) {
        emit typesChanged();
        emit typeUpdated(type);
        saveToDisk();
    }
}

void EventTypeService::deleteType(const QString& id)
{
    auto it = std::find_if(m_types.begin(), m_types.end(),
                           [&id](EventType* t) { return t->id() == id; });

    if (it != m_types.end()) {
        EventType* type = *it;
        m_types.erase(it);
        emit typesChanged();
        emit typeDeleted(id);
        saveToDisk();
        type->deleteLater();
    }
}

EventType* EventTypeService::getType(const QString& id) const
{
    auto it = std::find_if(m_types.begin(), m_types.end(),
                           [&id](EventType* t) { return t->id() == id; });

    return (it != m_types.end()) ? *it : nullptr;
}

bool EventTypeService::save()
{
    saveToDisk();
    return true;
}

bool EventTypeService::load()
{
    loadFromDisk();
    return true;
}

void EventTypeService::initializeDefaults()
{
    QList<EventType*> defaultTypes = EventType::createDefaultTypes(this);

    for (EventType* type : defaultTypes) {
        m_types.append(type);
    }

    emit typesChanged();
    saveToDisk();
}

void EventTypeService::setDataPath(const QString& path)
{
    if (m_dataPath != path) {
        m_dataPath = path;
        loadFromDisk();
    }
}

void EventTypeService::loadFromDisk()
{
    QDir dir(QFileInfo(m_dataPath).dir());
    if (!dir.exists()) {
        return;
    }

    QJsonArray typesArray = JsonSerializer::loadArrayFromFile(m_dataPath);

    qDeleteAll(m_types);
    m_types.clear();

    for (const QJsonValue& value : typesArray) {
        EventType* type = EventType::fromJson(value.toObject(), this);
        m_types.append(type);
    }

    emit typesChanged();
}

void EventTypeService::saveToDisk()
{
    QJsonArray typesArray;

    for (const EventType* type : m_types) {
        typesArray.append(type->toJson());
    }

    JsonSerializer::saveToFile(m_dataPath, typesArray);
}

QString EventTypeService::getDefaultDataPath() const
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation);

    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return dir.filePath("types.json");
}
