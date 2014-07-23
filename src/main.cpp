/*
 * Copyright 2014  Martin Gräßlin <mgraesslin@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "previewbridge.h"
#include "previewclient.h"
#include "previewitem.h"
#include "previewsettings.h"

#include <KDecoration2/Decoration>
#include <KDecoration2/DecorationSettings>

#include <KAboutData>
#include <KPluginTrader>
#include <KLocalizedString>
#include <kdeclarative/kdeclarative.h>

#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QStandardPaths>

static const QString s_pluginName = QStringLiteral("org.kde.kdecoration2");

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    KAboutData aboutData(QStringLiteral("kdecorationviewer"),
                         i18n("KDecoration Viewer"),
                         QStringLiteral("1.0.0"), // TODO: proper version number
                         i18n("Viewer for KDecoration2 Plugins"),
                         KAboutLicense::GPL);
    aboutData.addAuthor(i18n("Martin Gräßlin"), i18n("Maintainer"), QStringLiteral("mgraesslin@kde.org"));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    QCommandLineOption listOption(QStringList({QStringLiteral("l"), QStringLiteral("list")}), i18n("List all available plugins"));
    parser.addOption(listOption);
    parser.addHelpOption();
    parser.addPositionalArgument(QStringLiteral("plugin"), i18n("The plugin to load."));
    aboutData.setupCommandLine(&parser);

    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(listOption)) {
        const auto offers = KPluginTrader::self()->query(s_pluginName, s_pluginName);
        for (const auto &offer : offers) {
            qDebug() << offer.pluginName();
        }
        return 0;
    }

    if (parser.positionalArguments().count() != 1) {
        qCritical() << i18n("Expects exactly one plugin name");
        return 1;
    }

    KDecoration2::Preview::PreviewBridge bridge;
    KDecoration2::DecorationSettings::self(&app);

    QString error;
    KPluginTrader::createInstanceFromQuery<KDecoration2::Decoration>(QStringLiteral("org.kde.kdecoration2"),
                                                                     QStringLiteral("org.kde.kdecoration2"),
                                                                     QStringLiteral("[X-KDE-PluginInfo-Name] == '%1'").arg(parser.positionalArguments().first()),
                                                                     &app,
                                                                     QVariantList(),
                                                                     &error);
    if (!error.isNull()) {
        qCritical() << i18n("Plugin failed to load: %1", error);
        return 1;
    }

    QQuickView view;
    KDeclarative::KDeclarative kdeclarative;
    kdeclarative.setDeclarativeEngine(view.engine());
    kdeclarative.setupBindings();
    qRegisterMetaType<KDecoration2::Decoration*>();
    qmlRegisterType<KDecoration2::Decoration>();
    qmlRegisterType<KDecoration2::Preview::PreviewItem>("org.kde.kdecoration2.preview", 1, 0, "PreviewItem");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.engine()->rootContext()->setContextProperty(QStringLiteral("client"), bridge.lastCreatedClient());
    view.engine()->rootContext()->setContextProperty(QStringLiteral("settings"), bridge.lastCreatedSettings());
    view.setSource(QUrl::fromLocalFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("org.kde.kdecorationviewer/qml/main.qml"))));

    view.show();

    return app.exec();
}
