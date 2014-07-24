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
#ifndef KDECOARTIONS_PREVIEW_SETTINGS_H
#define KDECOARTIONS_PREVIEW_SETTINGS_H

#include <KDecoration2/Private/DecorationSettingsPrivate>
#include <KDecoration2/DecorationSettings>
#include <QObject>
#include <QAbstractListModel>

namespace KDecoration2
{

namespace Preview
{

class ButtonsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ButtonsModel(const QList< DecorationButtonType > &buttons, QObject *parent = 0);
    virtual ~ButtonsModel();
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash< int, QByteArray > roleNames() const override;

    QList< DecorationButtonType > buttons() const {
        return m_buttons;
    }

    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void up(int index);
    Q_INVOKABLE void down(int index);

    void add(DecorationButtonType type);

private:
    QList< DecorationButtonType > m_buttons;
};

class BorderSizesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BorderSizesModel(QObject *parent = 0);
    virtual ~BorderSizesModel();
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash< int, QByteArray > roleNames() const override;
private:
    QMap<BorderSize, QString> m_borders;
};

class PreviewSettings : public QObject, public DecorationSettingsPrivate
{
    Q_OBJECT
    Q_PROPERTY(bool onAllDesktopsAvailable READ isOnAllDesktopsAvailable WRITE setOnAllDesktopsAvailable NOTIFY onAllDesktopsAvailableChanged)
    Q_PROPERTY(bool alphaChannelSupported READ isAlphaChannelSupported WRITE setAlphaChannelSupported NOTIFY alphaChannelSupportedChanged)
    Q_PROPERTY(bool closeOnDoubleClickOnMenu READ isCloseOnDoubleClickOnMenu WRITE setCloseOnDoubleClickOnMenu NOTIFY closeOnDoubleClickOnMenuChanged)
    Q_PROPERTY(QAbstractItemModel *leftButtonsModel READ leftButtonsModel CONSTANT)
    Q_PROPERTY(QAbstractItemModel *rightButtonsModel READ rightButtonsModel CONSTANT)
    Q_PROPERTY(QAbstractItemModel *availableButtonsModel READ availableButtonsModel CONSTANT)
    Q_PROPERTY(QAbstractItemModel *borderSizesModel READ borderSizesModel CONSTANT)
    Q_PROPERTY(int borderSizesIndex READ borderSizesIndex WRITE setBorderSizesIndex NOTIFY borderSizesIndexChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
public:
    explicit PreviewSettings(DecorationSettings *parent);
    virtual ~PreviewSettings();
    bool isAlphaChannelSupported() const override;
    bool isOnAllDesktopsAvailable() const override;
    bool isCloseOnDoubleClickOnMenu() const override {
        return m_closeOnDoubleClick;
    }
    BorderSize borderSize() const override;

    void setOnAllDesktopsAvailable(bool available);
    void setAlphaChannelSupported(bool supported);
    void setCloseOnDoubleClickOnMenu(bool enabled);

    QAbstractItemModel *leftButtonsModel() const {
        return m_leftButtons;
    }
    QAbstractItemModel *rightButtonsModel() const {
        return m_rightButtons;
    }
    QAbstractItemModel *availableButtonsModel() const {
        return m_availableButtons;
    }
    QAbstractItemModel *borderSizesModel() const {
        return m_borderSizes;
    }

    QList< DecorationButtonType > decorationButtonsLeft() const;
    QList< DecorationButtonType > decorationButtonsRight() const;

    Q_INVOKABLE void addButtonToLeft(int row);
    Q_INVOKABLE void addButtonToRight(int row);

    int borderSizesIndex() const {
        return m_borderSize;
    }
    void setBorderSizesIndex(int index);

    QFont font() const {
        return m_font;
    }
    void setFont(const QFont &font);

Q_SIGNALS:
    void onAllDesktopsAvailableChanged(bool);
    void alphaChannelSupportedChanged(bool);
    void closeOnDoubleClickOnMenuChanged(bool);
    void borderSizesIndexChanged(int);
    void fontChanged(const QFont &);

private:
    bool m_alphaChannelSupported;
    bool m_onAllDesktopsAvailable;
    bool m_closeOnDoubleClick;
    ButtonsModel *m_leftButtons;
    ButtonsModel *m_rightButtons;
    ButtonsModel *m_availableButtons;
    BorderSizesModel *m_borderSizes;
    int m_borderSize;
    QFont m_font;
};

}

}

#endif
