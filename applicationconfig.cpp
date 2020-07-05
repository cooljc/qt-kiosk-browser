#include "applicationconfig.h"

#include <QFile>
#include <QDir>
#include <QJsonDocument>

ApplicationConfig::ApplicationConfig(QString &configFile, QObject *parent) : QObject(parent)
{
    if (configFile.isEmpty()) {
        m_configFilePath = QDir::homePath() + "/.qt-kiosk-browser.json";
    } else {
        m_configFilePath = configFile;
    }
    loadConfig();
}

void ApplicationConfig::loadConfig()
{
    QFile configFile(m_configFilePath);
    if (configFile.open(QIODevice::ReadOnly)) {
        QByteArray configData = configFile.readAll();
        QJsonDocument config(QJsonDocument::fromJson(configData));
        configFile.close();
        m_config = config.object();
    } else {
        // existing file does not exist
        // create new config
        m_config.insert("URL", "https://www.raspberrypi.org");
        m_config.insert("ScreenSaverTimeout", 60000); // 1 minute
        m_config.insert("RestartTimeout", 0); // disabled
        saveConfig();
    }
}

void ApplicationConfig::saveConfig()
{
    QFile configFile(m_configFilePath);
    if (configFile.open(QIODevice::WriteOnly)) {
        configFile.write(QJsonDocument(m_config).toJson());
        configFile.close();
    }
}
