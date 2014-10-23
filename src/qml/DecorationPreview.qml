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
import org.kde.kdecoration2.preview 1.0

Rectangle {
    id: base
    property real canvasBorder: 0.0
    property alias windowColor: preview.windowColor

    PreviewItem {
        id: preview
        decoration: client.decoration
        anchors {
            fill: parent
            topMargin: base.canvasBorder
            bottomMargin: base.canvasBorder
            rightMargin: base.canvasBorder
            leftMargin: base.canvasBorder
        }
        Component.onCompleted: {
            client.width = Qt.binding(function() {
                var shadowOffset = preview.decoration.shadow ? preview.decoration.shadow.paddingLeft + preview.decoration.shadow.paddingRight : 0;
                return preview.width - preview.decoration.borderLeft - preview.decoration.borderRight - shadowOffset;
            });
            client.height = Qt.binding(function() {
                var shadowOffset = preview.decoration.shadow ? preview.decoration.shadow.paddingTop + preview.decoration.shadow.paddingBottom : 0;
                return preview.height - preview.decoration.borderTop - preview.decoration.borderBottom - shadowOffset;
            });
            preview.decoration.init();
        }
    }
}
