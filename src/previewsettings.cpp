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
#include "previewsettings.h"


namespace KDecoration2
{

namespace Preview
{

PreviewSettings::PreviewSettings(DecorationSettings *parent)
    : QObject()
    , DecorationSettingsPrivate(parent)
    , m_alphaChannelSupported(true)
    , m_onAllDesktopsAvailable(true)
{
    connect(this, &PreviewSettings::alphaChannelSupportedChanged, parent, &DecorationSettings::alphaChannelSupportedChanged);
    connect(this, &PreviewSettings::onAllDesktopsAvailableChanged, parent, &DecorationSettings::onAllDesktopsAvailableChanged);
}

PreviewSettings::~PreviewSettings() = default;

bool PreviewSettings::isAlphaChannelSupported() const
{
    return m_alphaChannelSupported;
}

bool PreviewSettings::isOnAllDesktopsAvailable() const
{
    return m_onAllDesktopsAvailable;
}

void PreviewSettings::setAlphaChannelSupported(bool supported)
{
    if (m_alphaChannelSupported == supported) {
        return;
    }
    m_alphaChannelSupported = supported;
    emit alphaChannelSupportedChanged(m_alphaChannelSupported);
}

void PreviewSettings::setOnAllDesktopsAvailable(bool available)
{
    if (m_onAllDesktopsAvailable == available) {
        return;
    }
    m_onAllDesktopsAvailable = available;
    emit onAllDesktopsAvailableChanged(m_onAllDesktopsAvailable);
}

}
}
