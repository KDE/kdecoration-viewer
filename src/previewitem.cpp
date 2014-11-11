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
#include <KDecoration2/DecorationShadow>
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
    PreviewBridge::instance().registerPreviewItem(this);
}

PreviewItem::~PreviewItem()
{
    PreviewBridge::instance().unregisterPreviewItem(this);
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
    m_decoration->setProperty("visualParent", QVariant::fromValue(this));
    connect(m_decoration, &Decoration::bordersChanged, this, updateSlot);
    connect(m_decoration, &Decoration::sectionUnderMouseChanged, this,
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
    int paddingLeft   = 0;
    int paddingTop    = 0;
    int paddingRight  = 0;
    int paddingBottom = 0;
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        const QImage img = shadow->shadow();
        const QRect topLeft     = QRect(QPoint(0, 0), shadow->topLeft());
        const QRect top         = QRect(QPoint(topLeft.width(), 0), shadow->top());
        const QRect topRight    = QRect(QPoint(topLeft.width() + top.width(), 0), shadow->topRight());
        const QRect right       = QRect(QPoint(topLeft.width() + top.width(), topRight.height()), shadow->right());
        const QRect left        = QRect(QPoint(0, topLeft.height()), shadow->left());
        const QRect bottomLeft  = QRect(QPoint(0, topLeft.height() + left.height()), shadow->bottomLeft());
        const QRect bottom      = QRect(QPoint(bottomLeft.width(), img.height() - shadow->bottom().height()), shadow->bottom());
        const QRect bottomRight = QRect(QPoint(bottomLeft.width() + bottom.width(), topRight.height() + right.height()), shadow->bottomRight());
        paddingLeft   = shadow->paddingLeft();
        paddingTop    = shadow->paddingTop();
        paddingRight  = shadow->paddingRight();
        paddingBottom = shadow->paddingBottom();

        painter->translate(paddingLeft, paddingTop);

        // top left
        painter->drawImage(QPoint(-paddingLeft, -paddingTop), img, topLeft);
        // top
        painter->drawImage(QRect(-paddingLeft + topLeft.width(), -paddingTop, width() - topLeft.width() - topRight.width(), top.height()), img, top);
        // top right
        painter->drawImage(QPoint(width() - topRight.width() - paddingLeft, -paddingTop), img, topRight);
        // right
        painter->drawImage(QRect(width() - right.width() - paddingLeft, -paddingTop + topRight.height(), right.width(), height() - topRight.height() - bottomRight.height()), img, right);
        // bottom right
        painter->drawImage(QPoint(width() - paddingLeft - bottomRight.width(), height() - paddingTop - bottomRight.height()), img, bottomRight);
        // bottom
        painter->drawImage(QRect(-paddingLeft + bottomLeft.width(), height() - bottom.height() - paddingTop, width() - bottomLeft.width() - bottomRight.width(), bottom.height()), img, bottom);
        // bottom left
        painter->drawImage(QPoint(-paddingLeft, height() - bottomLeft.height() - paddingTop), img, bottomLeft);
        // left
        painter->drawImage(QRect(-paddingLeft, -paddingTop + topLeft.height(), left.width(), height() - topLeft.height() - bottomLeft.height()), img, left);
    }
    m_decoration->paint(painter, QRegion(0, 0, width(), height()));
    if (m_drawBackground) {
        const QMargins &b = m_decoration->borders();
        painter->fillRect(b.left(), b.top(),
                        width() - b.left() - b.right() - paddingLeft - paddingRight,
                        height() - b.top() - b.bottom() - paddingTop - paddingBottom,
                        m_windowColor);
    }
}

void PreviewItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QMouseEvent e(event->type(),
                      event->localPos() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->button(),
                      event->buttons(),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

void PreviewItem::mousePressEvent(QMouseEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QMouseEvent e(event->type(),
                      event->localPos() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->button(),
                      event->buttons(),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

void PreviewItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QMouseEvent e(event->type(),
                      event->localPos() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->button(),
                      event->buttons(),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

void PreviewItem::mouseMoveEvent(QMouseEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QMouseEvent e(event->type(),
                      event->localPos() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->button(),
                      event->buttons(),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

void PreviewItem::hoverEnterEvent(QHoverEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QHoverEvent e(event->type(),
                      event->posF() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->oldPosF() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

void PreviewItem::hoverLeaveEvent(QHoverEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QHoverEvent e(event->type(),
                      event->posF() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->oldPosF() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

void PreviewItem::hoverMoveEvent(QHoverEvent *event)
{
    if (const DecorationShadow *shadow = ((const Decoration*)(m_decoration))->shadow()) {
        QHoverEvent e(event->type(),
                      event->posF() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->oldPosF() - QPointF(shadow->paddingLeft(), shadow->paddingTop()),
                      event->modifiers());
        QCoreApplication::instance()->sendEvent(decoration(), &e);
    } else {
        QCoreApplication::instance()->sendEvent(decoration(), event);
    }
}

bool PreviewItem::isDrawingBackground() const
{
    return m_drawBackground;
}

void PreviewItem::setDrawingBackground(bool set)
{
    if (m_drawBackground == set) {
        return;
    }
    m_drawBackground = set;
    emit drawingBackgroundChanged(set);
}

}
}
