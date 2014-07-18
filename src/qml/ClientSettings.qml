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
import org.kde.kquickcontrolsaddons 2.0 as KQuickControlsAddons

GridLayout {
    columns: 2

    Label {
        text: "Caption:"
    }
    TextField {
        text: client.caption
        onEditingFinished: {
            client.caption = text;
        }
    }

    Label {
        text: "Icon:"
    }
    RowLayout {
        TextField {
            text: client.iconName
            onEditingFinished: {
                client.iconName = text;
            }
        }
        KQuickControlsAddons.QIconItem {
            icon: client.icon
            width: 32
            height: 32
        }
    }

    Label {
        text: "Active:"
    }
    CheckBox {
        id: activeBox
        checked: client.active
        onClicked: {
            client.active = checked;
        }
    }

    Label {
        text: "Desktop"
    }
    SpinBox {
        id: desktopBox
        value: client.desktop
        minimumValue: -1.0
        maximumValue: 20.0
        onEditingFinished: {
            client.desktop = value;
        }
    }

    Label {
        text: "Closeable:"
    }
    CheckBox {
        id: closeableBox
        checked: client.closeable
        onClicked: {
            client.closeable = checked;
        }
    }

    Label {
        text: "Keep Above:"
    }
    CheckBox {
        id: keepAboveBox
        checked: client.keepAbove
        onClicked: {
            client.keepAbove = checked;
        }
    }

    Label {
        text: "Keep Below:"
    }
    CheckBox {
        id: keepBelowBox
        checked: client.keepBelow
        onClicked: {
            client.keepBelow = checked;
        }
    }

    Label {
        text: "Maximizable:"
    }
    CheckBox {
        id: maximizableBox
        checked: client.maximizable
        onClicked: {
            client.maximizable = checked;
        }
    }

    Label {
        text: "Maximized:"
    }
    CheckBox {
        id: maximizedBox
        checked: client.maximized
        enabled: false
    }

    Label {
        text: "Maximized Vertically:"
    }
    CheckBox {
        id: maximizedVerticallyBox
        checked: client.maximizedVertically
        onClicked: {
            client.maximizedVertically = checked;
        }
    }

    Label {
        text: "Maximized Horizontally:"
    }
    CheckBox {
        id: maximizedHorizontallyBox
        checked: client.maximizedHorizontally
        onClicked: {
            client.maximizedHorizontally = checked;
        }
    }

    Label {
        text: "Minimizable:"
    }
    CheckBox {
        id: minimizableBox
        checked: client.minimizable
        onClicked: {
            client.minimizable = checked;
        }
    }

    Label {
        text: "Modal:"
    }
    CheckBox {
        id: modalBox
        checked: client.modal
        onClicked: {
            client.modal = checked;
        }
    }

    Label {
        text: "Movable:"
    }
    CheckBox {
        id: movableBox
        checked: client.movable
        onClicked: {
            client.movable = checked;
        }
    }

    Label {
        text: "On All Dekstops:"
    }
    CheckBox {
        id: onAllDekstopsBox
        checked: client.onAllDekstops
        enabled: false
        onClicked: {
            client.onAllDekstops = checked;
        }
    }

    Label {
        text: "Resizable:"
    }
    CheckBox {
        id: resizableBox
        checked: client.resizable
        onClicked: {
            client.resizable = checked;
        }
    }

    Label {
        text: "Shadeable:"
    }
    CheckBox {
        id: shadeableBox
        checked: client.shadeable
        onClicked: {
            client.shadeable = checked;
        }
    }

    Label {
        text: "Shaded:"
    }
    CheckBox {
        id: shadedBox
        checked: client.shaded
        onClicked: {
            client.shaded = checked;
        }
    }

    Label {
        text: "Provides Context Help:"
    }
    CheckBox {
        id: providesContextHelpBox
        checked: client.providesContextHelp
        onClicked: {
            client.providesContextHelp = checked;
        }
    }

    Label {
        text: "Color Scheme:"
    }
    ComboBox {
        model: client.colorSchemeModel
        textRole: "display"
        currentIndex: client.colorSchemeIndex
        onCurrentIndexChanged: {
            client.colorSchemeIndex = currentIndex;
        }
    }
}
