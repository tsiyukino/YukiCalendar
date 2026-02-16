#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>

class JsonSerializer
{
public:
    // Save JSON to file
    static bool saveToFile(const QString& filePath, const QJsonObject& json);
    static bool saveToFile(const QString& filePath, const QJsonArray& json);

    // Load JSON from file
    static QJsonObject loadObjectFromFile(const QString& filePath);
    static QJsonArray loadArrayFromFile(const QString& filePath);

    // Ensure directory exists
    static bool ensureDirectoryExists(const QString& filePath);

    // Pretty print JSON
    static QString toFormattedString(const QJsonObject& json);
    static QString toFormattedString(const QJsonArray& json);
};

#endif // JSONSERIALIZER_H
