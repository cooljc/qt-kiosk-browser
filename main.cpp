/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include <QApplication>
#include <QtWebEngine>

#include "inputeventhandler.hpp"
#include "browser.hpp"
#include "applicationconfig.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    // Set application name and version for command line parser
    QCoreApplication::setApplicationName("qt-kiosk-browser");
    QCoreApplication::setApplicationVersion("0.2");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QtWebEngine::initialize();

    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QT Kiosk Browser");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configFileOption(QStringList() << "c" << "config-file",
        QCoreApplication::translate("main", "Optional path to config file <file> (default is $HOME/.qt-kiosk-browser.json)"),
        QCoreApplication::translate("main", "file"));
    parser.addOption(configFileOption);

    // Process the actual command line arguments given by the user
    parser.process(app);
    QString configFile = parser.value(configFileOption);
    // Load application config data
    ApplicationConfig appConfig(configFile);

    qmlRegisterSingletonType<InputEventHandler>("Browser", 1, 0, "Browser", [](QQmlEngine *, QJSEngine *) -> QObject * {
        return new Browser();
    });
    qmlRegisterType<InputEventHandler>("Browser", 1, 0, "InputEventHandler");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("configData", &appConfig);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
