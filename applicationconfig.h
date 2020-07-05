#ifndef APPLICATIONCONFIG_H
#define APPLICATIONCONFIG_H

#include <QObject>
#include <QJsonObject>

class ApplicationConfig : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationConfig(QString &configFile, QObject *parent = nullptr);
    Q_INVOKABLE QJsonObject getConfig() const {
        return m_config;
    }
signals:

private:
    void loadConfig();
    void saveConfig();

    QString m_configFilePath;
    QJsonObject m_config;
};

#endif // APPLICATIONCONFIG_H
