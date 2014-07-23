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
import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

RowLayout {
    width: 800
    height: 640
    ScrollView {
        frameVisible: true
        Layout.fillHeight: true
        Layout.preferredWidth: contentItem.width
        ColumnLayout {
            Label {
                text: i18n("Client Settings")
                font.bold: true
                font.underline: true
            }
            ClientSettings {
            }
            Label {
                text: i18n("Decoration Settings")
                font.bold: true
                font.underline: true
            }
            DecorationSettings {
            }
            Label {
                text: i18n("Canvas Settings")
                font.bold: true
                font.underline: true
            }
            CanvasSettings {
                id: canvasSettings
            }
        }
    }
    DecorationPreview {
        color: canvasSettings.backgroundColor
        windowColor: canvasSettings.windowColor
        canvasBorder: canvasSettings.border
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
