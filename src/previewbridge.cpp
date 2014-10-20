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

#include <KDecoration2/DecoratedClient>

namespace KDecoration2
{
namespace Preview
{

PreviewBridge::PreviewBridge()
    : DecorationBridge()
    , m_lastCreatedClient(nullptr)
    , m_lastCreatedSettings(nullptr)
{
}

PreviewBridge::~PreviewBridge() = default;

std::unique_ptr<DecoratedClientPrivate> PreviewBridge::createClient(DecoratedClient *client, Decoration *decoration)
{
    auto ptr = std::unique_ptr<PreviewClient>(new PreviewClient(client, decoration));
    m_lastCreatedClient = ptr.get();
    return std::move(ptr);
}

void PreviewBridge::update(Decoration *decoration, const QRect &geometry)
{
    Q_UNUSED(geometry)
    auto it = std::find_if(m_previewItems.constBegin(), m_previewItems.constEnd(), [decoration](PreviewItem *item) {
        return item->decoration() == decoration;
    });
    if (it != m_previewItems.constEnd()) {
        (*it)->update();
    }
}

std::unique_ptr<DecorationSettingsPrivate> PreviewBridge::settings(DecorationSettings *parent)
{
    auto ptr = std::unique_ptr<PreviewSettings>(new PreviewSettings(parent));
    m_lastCreatedSettings = ptr.get();
    return std::move(ptr);
}

void PreviewBridge::registerPreviewItem(PreviewItem *item)
{
    m_previewItems.append(item);
}

void PreviewBridge::unregisterPreviewItem(PreviewItem *item)
{
    m_previewItems.removeAll(item);
}

}
}
