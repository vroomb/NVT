#include "timeline_pin.hpp"

void TimelinePin::componentComplete() {
    QQuickItem::componentComplete();
    // connect(this, &TimelinePin::xChanged, [this]() {
    //         if (node() == nullptr) return;
    //         if (abs(node()->x() - x()) < 50) setValid(true);
    //         else                             setValid(false);
    //     });
    // connect(this, &TimelinePin::yChanged, [this]() {
    //         if (node() == nullptr) return;
    //         if (abs(node()->y() - y()) < 50) setValid(true);
    //         else                             setValid(false);
    //     });
}

bool TimelinePin::valid() {
    if (node() == nullptr)
        return true;
    if ((abs(node()->x() - x()) < 50) && (abs(node()->y() - y()) < 50))
        return true;
    else
        return false;
}

void TimelinePin::setValid(bool valid) {
    m_valid = valid;
    emit validChanged();
}

bool TimelinePin::accept() {
    return m_accept;
}

void TimelinePin::setAccept(bool accept) {
    m_accept = accept;
    emit acceptChanged();
}

QQuickItem* TimelinePin::node() {
    return m_node;
}

void TimelinePin::setNode(QQuickItem* node) {
    if (m_node != nullptr) {
        disconnect(m_node, nullptr, this, nullptr);
    }

    m_node = node;

    if (m_node != nullptr) {
        connect(m_node, &QQuickItem::xChanged, this, &TimelinePin::updateX);
        connect(m_node, &QQuickItem::yChanged, this, &TimelinePin::updateY);
        updateX();
        updateY();
    }
}

void TimelinePin::updateX() {
    setX(m_node->x());
}

void TimelinePin::updateY() {
    setY(m_node->y());
}

