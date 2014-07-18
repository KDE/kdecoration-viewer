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
import QtQuick.Dialogs 1.1

GridLayout {
    property alias border: canvasBorder.value
    property alias backgroundColor: backgroundColorDialog.color
    property alias windowColor: windowColorDialog.color
    columns: 2
    Label {
        text: "Canvas border:"
    }
    SpinBox {
        id: canvasBorder
        value: 20.0
    }
    Label {
        text: "Canvas background color:"
    }
    Button {
        ColorDialog {
            id: backgroundColorDialog
            color: "black"
        }
        text: backgroundColorDialog.color
        onClicked: {
            backgroundColorDialog.open();
        }
    }
    Label {
        text: "Window background color:"
    }
    Button {
        ColorDialog {
            id: windowColorDialog
            color: "white"
        }
        text: windowColorDialog.color
        onClicked: {
            windowColorDialog.open();
        }
    }
}
