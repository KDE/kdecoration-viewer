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
#ifndef KDECOARTIONS_PREVIEW_BRIDGE_H
#define KDECOARTIONS_PREVIEW_BRIDGE_H

#include <KDecoration2/Private/DecorationBridge>

#include <QList>

namespace KDecoration2
{
namespace Preview
{

class PreviewClient;
class PreviewItem;
class PreviewSettings;

class PreviewBridge : public DecorationBridge
{
public:
    explicit PreviewBridge();
    virtual ~PreviewBridge();
    DecoratedClientPrivate *createClient(DecoratedClient *client, Decoration *decoration) override;
    void update(Decoration* decoration, const QRect& geometry) override;
    DecorationSettingsPrivate *settings(DecorationSettings *parent) override;

    PreviewClient *lastCreatedClient() {
        return m_lastCreatedClient;
    }
    PreviewSettings *lastCreatedSettings() {
        return m_lastCreatedSettings;
    }

    void registerPreviewItem(PreviewItem *item);
    void unregisterPreviewItem(PreviewItem *item);

private:
    PreviewClient *m_lastCreatedClient;
    PreviewSettings *m_lastCreatedSettings;
    QList<PreviewItem*> m_previewItems;
};

}
}

#endif
