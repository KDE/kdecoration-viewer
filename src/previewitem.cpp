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
#include "previewitem.h"
#include "previewbridge.h"
#include <KDecoration2/Decoration>
#include <KDecoration2/DecoratedClient>
#include <QCursor>
#include <QPainter>

#include <QDebug>

namespace KDecoration2
{
namespace Preview
{

PreviewItem::PreviewItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_decoration(nullptr)
    , m_windowColor(QPalette().background().color())
{
    setAcceptHoverEvents(true);
    setFiltersChildMouseEvents(true);
    setAcceptedMouseButtons(Qt::MouseButtons(~Qt::NoButton));
    static_cast<PreviewBridge*>(DecorationBridge::self())->registerPreviewItem(this);
}

PreviewItem::~PreviewItem()
{
    static_cast<PreviewBridge*>(DecorationBridge::self())->unregisterPreviewItem(this);
}

Decoration *PreviewItem::decoration() const
{
    return m_decoration;
}

void PreviewItem::setDecoration(Decoration *deco)
{
    if (m_decoration == deco) {
        return;
    }
    auto updateSlot = static_cast<void (QQuickItem::*)()>(&QQuickItem::update);
    if (m_decoration) {
        disconnect(m_decoration, &Decoration::bordersChanged, this, updateSlot);
    }
    m_decoration = deco;
    connect(m_decoration, &Decoration::bordersChanged, this, updateSlot);
    connect(m_decoration, &Decoration::windowFrameSectionChanged, this,
        [this](Qt::WindowFrameSection section) {
            switch (section) {
                case Qt::TopRightSection:
            case Qt::BottomLeftSection:
                setCursor(Qt::SizeBDiagCursor);
                return;
            case Qt::TopLeftSection:
            case Qt::BottomRightSection:
                setCursor(Qt::SizeFDiagCursor);
                return;
            case Qt::TopSection:
            case Qt::BottomSection:
                setCursor(Qt::SizeVerCursor);
                return;
            case Qt::LeftSection:
            case Qt::RightSection:
                setCursor(Qt::SizeHorCursor);
                return;
            default:
                setCursor(Qt::ArrowCursor);
            }
        }
    );
    emit decorationChanged(m_decoration);
}

QColor PreviewItem::windowColor() const
{
    return m_windowColor;
}

void PreviewItem::setWindowColor(const QColor &color)
{
    if (m_windowColor == color) {
        return;
    }
    m_windowColor = color;
    emit windowColorChanged(m_windowColor);
    update();
}

void PreviewItem::paint(QPainter *painter)
{
    if (!m_decoration) {
        return;
    }
    m_decoration->paint(painter);
    painter->fillRect(m_decoration->borderLeft(), m_decoration->borderTop(),
                      width() - m_decoration->borderLeft() - m_decoration->borderRight(),
                      height() - m_decoration->borderTop() - m_decoration->borderBottom(),
                      m_windowColor);
}

void PreviewItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

void PreviewItem::mousePressEvent(QMouseEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

void PreviewItem::mouseReleaseEvent(QMouseEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

void PreviewItem::mouseMoveEvent(QMouseEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

void PreviewItem::hoverEnterEvent(QHoverEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

void PreviewItem::hoverLeaveEvent(QHoverEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

void PreviewItem::hoverMoveEvent(QHoverEvent *event)
{
    QCoreApplication::instance()->sendEvent(decoration(), event);
}

}
}
