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

GridLayout {
    columns: 2

    Label {
        text: "On all desktops available:"
    }
    CheckBox {
        id: onAllDesktopsBox
        checked: settings.onAllDesktopsAvailable
        onClicked: {
            settings.onAllDesktopsAvailable = checked;
        }
    }

    Label {
        text: "Alpha channel:"
    }
    CheckBox {
        id: alphaChannelBox
        checked: settings.alphaChannelSupported
        onClicked: {
            settings.alphaChannelSupported = checked;
        }
    }

    Label {
        text: i18n("Left Decoration Buttons:")
    }
    ScrollView {
        ListView {
            id: leftButtons
            model: settings.leftButtonsModel
            delegate: Item {
                id: delegate
                width: parent.width
                height: childrenRect.height
                RowLayout {
                    Label {
                        Layout.fillWidth: true
                        text: display
                    }
                    Button {
                        iconName: "list-remove"
                        text: i18n("Remove")
                        onClicked: settings.leftButtonsModel.remove(index)
                    }
                    Button {
                        visible: index != 0 && delegate.ListView.view.count > 1
                        iconName: "go-up"
                        text: i18n("Up")
                        onClicked: settings.leftButtonsModel.up(index)
                    }
                    Button {
                        visible: index != delegate.ListView.view.count - 1 && delegate.ListView.view.count > 1
                        iconName: "go-down"
                        text: i18n("Down")
                        onClicked: settings.leftButtonsModel.down(index)
                    }
                }
            }
        }
    }
    Label {
        text: i18n("Available Buttons:")
    }
    ScrollView {
        ListView {
            id: availableButtons
            model: settings.availableButtonsModel
            delegate: Item {
                id: delegate
                width: parent.width
                height: childrenRect.height
                RowLayout {
                    Label {
                        Layout.fillWidth: true
                        text: display
                    }
                    Button {
                        iconName: "go-left"
                        text: i18n("To left")
                        onClicked: settings.addButtonToLeft(index)
                    }
                    Button {
                        iconName: "go-right"
                        text: i18n("To right")
                        onClicked: settings.addButtonToRight(index)
                    }
                }
            }
        }
    }
    Label {
        text: i18n("Right Decoration Buttons:")
    }
    ScrollView {
        ListView {
            id: rightButtons
            model: settings.rightButtonsModel
            delegate: Item {
                id: delegate
                width: parent.width
                height: childrenRect.height
                RowLayout {
                    Label {
                        Layout.fillWidth: true
                        text: display
                    }
                    Button {
                        iconName: "list-remove"
                        text: i18n("Remove")
                        onClicked: settings.rightButtonsModel.remove(index)
                    }
                    Button {
                        visible: index != 0 && delegate.ListView.view.count > 1
                        iconName: "go-up"
                        text: i18n("Up")
                        onClicked: settings.rightButtonsModel.up(index)
                    }
                    Button {
                        visible: index != delegate.ListView.view.count - 1  && delegate.ListView.view.count > 1
                        iconName: "go-down"
                        text: i18n("Down")
                        onClicked: settings.rightButtonsModel.down(index)
                    }
                }
            }
        }
    }

//     Label {
//         text: ":"
//     }
//     CheckBox {
//         id:
//         checked: client.
//         onClicked: {
//             client. = checked;
//         }
//     }
}
