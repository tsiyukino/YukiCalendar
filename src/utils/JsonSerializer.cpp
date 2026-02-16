#include "JsonSerializer.h"
#include <QTextStream>
#include <QFileInfo>

bool JsonSerializer::saveToFile(const QString& filePath, const QJsonObject& json)
{
    ensureDirectoryExists(filePath);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonDocument doc(json);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool JsonSerializer::saveToFile(const QString& filePath, const QJsonArray& json)
{
    ensureDirectoryExists(filePath);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonDocument doc(json);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

QJsonObject JsonSerializer::loadObjectFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return QJsonObject();
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.object();
}

QJsonArray JsonSerializer::loadArrayFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return QJsonArray();
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.array();
}

bool JsonSerializer::ensureDirectoryExists(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.dir();

    if (!dir.exists()) {
        return dir.mkpath(".");
    }

    return true;
}

QString JsonSerializer::toFormattedString(const QJsonObject& json)
{
    QJsonDocument doc(json);
    return QString::fromUtf8(doc.toJson(QJsonDocument::Indented));
}

QString JsonSerializer::toFormattedString(const QJsonArray& json)
{
    QJsonDocument doc(json);
    return QString::fromUtf8(doc.toJson(QJsonDocument::Indented));
}
