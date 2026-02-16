#ifndef APIINPUTMODULE_H
#define APIINPUTMODULE_H

#include "ICalendarModule.h"
#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ApiInputModule : public QObject, public ICalendarModule
{
    Q_OBJECT

public:
    explicit ApiInputModule(QObject *parent = nullptr);
    ~ApiInputModule() override;

    // ICalendarModule interface
    QString id() const override { return "api-input"; }
    QString name() const override { return "API Input"; }
    QString description() const override { return "Fetches events from HTTP API"; }
    QString category() const override { return "Input"; }
    bool isRunning() const override { return m_isRunning; }

    QList<ModulePort> getInputPorts() const override;
    QList<ModulePort> getOutputPorts() const override;

    QVariantMap executeAsync(const QVariantMap& parameters) override;

    void startAsync() override;
    void stopAsync() override;

private slots:
    void onPollTimer();
    void onNetworkReply(QNetworkReply* reply);

private:
    bool m_isRunning;
    QTimer* m_pollTimer;
    QNetworkAccessManager* m_networkManager;
    QString m_apiUrl;
    int m_pollIntervalMs;

    QVariantList parseJsonResponse(const QByteArray& data);
};

#endif // APIINPUTMODULE_H
