#include "ApiInputModule.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>

ApiInputModule::ApiInputModule(QObject *parent)
    : QObject(parent)
    , m_isRunning(false)
    , m_pollTimer(new QTimer(this))
    , m_networkManager(new QNetworkAccessManager(this))
    , m_pollIntervalMs(30000) // 30 seconds
{
    connect(m_pollTimer, &QTimer::timeout, this, &ApiInputModule::onPollTimer);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &ApiInputModule::onNetworkReply);
}

ApiInputModule::~ApiInputModule()
{
    stopAsync();
}

QList<ModulePort> ApiInputModule::getInputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("apiUrl", "string", "API endpoint URL", true));
    ports.append(ModulePort("pollIntervalMs", "int", "Polling interval in milliseconds (default: 30000)", false));
    ports.append(ModulePort("headers", "object", "HTTP headers (optional)", false));
    return ports;
}

QList<ModulePort> ApiInputModule::getOutputPorts() const
{
    QList<ModulePort> ports;
    ports.append(ModulePort("Execute", "execute", "Execute when new data arrives", false));
    ports.append(ModulePort("events", "object", "Array of event objects", false));
    ports.append(ModulePort("success", "bool", "Whether request was successful", false));
    ports.append(ModulePort("errorMessage", "string", "Error message if failed", false));
    return ports;
}

QVariantMap ApiInputModule::executeAsync(const QVariantMap& parameters)
{
    QVariantMap outputs;

    m_apiUrl = parameters.value("apiUrl", "").toString();
    m_pollIntervalMs = parameters.value("pollIntervalMs", 30000).toInt();

    if (m_apiUrl.isEmpty()) {
        outputs["success"] = false;
        outputs["errorMessage"] = "API URL is required";
        return outputs;
    }

    // Perform immediate fetch
    QNetworkRequest request(m_apiUrl);

    // Add custom headers if provided
    QVariantMap headers = parameters.value("headers").toMap();
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        request.setRawHeader(it.key().toUtf8(), it.value().toString().toUtf8());
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_networkManager->get(request);

    outputs["success"] = true;
    return outputs;
}

void ApiInputModule::startAsync()
{
    m_isRunning = true;

    if (!m_apiUrl.isEmpty()) {
        m_pollTimer->start(m_pollIntervalMs);
    }
}

void ApiInputModule::stopAsync()
{
    m_isRunning = false;
    m_pollTimer->stop();
}

void ApiInputModule::onPollTimer()
{
    if (m_apiUrl.isEmpty()) {
        return;
    }

    QNetworkRequest request(m_apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_networkManager->get(request);
}

void ApiInputModule::onNetworkReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QVariantList events = parseJsonResponse(data);

        // Emit signal or store results
        // For now, just parse and discard
        qDebug() << "Received" << events.size() << "events from API";
    } else {
        qWarning() << "API request failed:" << reply->errorString();
    }

    reply->deleteLater();
}

QVariantList ApiInputModule::parseJsonResponse(const QByteArray& data)
{
    QVariantList events;

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isArray()) {
        QJsonArray array = doc.array();
        for (const QJsonValue& value : array) {
            events.append(value.toObject().toVariantMap());
        }
    } else if (doc.isObject()) {
        QJsonObject obj = doc.object();
        // Check if there's an "events" array in the object
        if (obj.contains("events") && obj["events"].isArray()) {
            QJsonArray array = obj["events"].toArray();
            for (const QJsonValue& value : array) {
                events.append(value.toObject().toVariantMap());
            }
        } else {
            // Single event object
            events.append(obj.toVariantMap());
        }
    }

    return events;
}
