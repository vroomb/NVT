#include "repeating_texture.hpp"

RepeatingTexture::RepeatingTexture(QQuickItem* parent, int mode):
    QQuickItem(parent),
    m_anchorMode(mode)
{}

QPointF RepeatingTexture::anchorPoint() const {
    if (m_anchorMode == absolute)
        return m_anchorPoint;
    else
        return (m_anchorPoint + m_relAnchorPoint);
}
void RepeatingTexture::setAnchorPoint(QPointF new_anchorPoint) {
    if      (anchorXEnabled() == true  && anchorYEnabled() == true ) m_anchorPoint = new_anchorPoint;
    else if (anchorXEnabled() == false && anchorYEnabled() == true ) m_anchorPoint.setY(new_anchorPoint.y());
    else if (anchorXEnabled() == true  && anchorYEnabled() == false) m_anchorPoint.setX(new_anchorPoint.x());
    else                                                             return;
    emit anchorPointChanged();
}

void RepeatingTexture::setAnchorPointX(qreal new_anchorPointX) {
    m_anchorPoint.setX(new_anchorPointX);
    emit anchorPointChanged();
}
void RepeatingTexture::setAnchorPointY(qreal new_anchorPointY) {
    m_anchorPoint.setY(new_anchorPointY);
    emit anchorPointChanged();
}

QQuickItem* RepeatingTexture::anchorItem() const {
    return m_anchorItem;
}
void RepeatingTexture::setAnchorItem(QQuickItem * new_anchorItem) {
    if (m_anchorItem != NULL) {
        qDebug() << m_anchorItem->objectName() << " disconnected";
        QObject::disconnect(m_anchorItem, nullptr, this, nullptr);
    }
    if (new_anchorItem != NULL) {
        qDebug() << new_anchorItem->objectName() << " connected";
        QObject::connect(new_anchorItem, &QQuickItem::xChanged, this,
            [this, new_anchorItem]() {
                this->setAnchorPointX(new_anchorItem->x());
            }, Qt::AutoConnection);

        QObject::connect(new_anchorItem, &QQuickItem::yChanged, this,
            [this, new_anchorItem]() {
                this->setAnchorPointY(new_anchorItem->y());
            }, Qt::AutoConnection);

        QPointF a = { new_anchorItem->x(), new_anchorItem->y() };
        m_relAnchorPoint = anchorPoint() - a;
        setAnchorPoint(a);
    }
    m_anchorItem = new_anchorItem;
    emit anchorItemChanged();
}

QQmlComponent* RepeatingTexture::texture() const {
    return m_texture;
}
void RepeatingTexture::setTexture(QQmlComponent * new_texture) {
    m_texture = new_texture;
    emit textureChanged();
}

bool RepeatingTexture::anchorXEnabled() const {
    return m_anchorXEnabled;
}
void RepeatingTexture::setAnchorXEnabled(bool new_anchorXEnabled) {
    m_anchorXEnabled = new_anchorXEnabled;
    emit anchorXEnabledChanged();
}

bool RepeatingTexture::anchorYEnabled() const {
    return m_anchorYEnabled;
}
void RepeatingTexture::setAnchorYEnabled(bool new_anchorYEnabled) {
    m_anchorYEnabled = new_anchorYEnabled;
    emit anchorYEnabledChanged();
}

int RepeatingTexture::anchorMode() const {
    return m_anchorMode;
}
void RepeatingTexture::setAnchorMode(int new_anchorMode) {
    m_anchorMode = new_anchorMode;
    if ((m_anchorMode == relative) && (m_anchorItem != NULL)) {
        m_relAnchorPoint = {0, 0};
    }
    emit anchorPointChanged();
    emit anchorModeChanged();
}

