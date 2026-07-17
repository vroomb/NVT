#pragma once

#include "library.hpp"

#define debug_pin_opacity 0

class TimelinePin : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickItem* node READ node WRITE setNode)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
    Q_PROPERTY(bool accept READ accept WRITE setAccept NOTIFY acceptChanged)

public:
    explicit TimelinePin(QQuickItem* parent = NULL): QQuickItem(parent) {}

    QQuickItem* node();
    void setNode(QQuickItem* node);

    bool accept();
    void setAccept(bool accept);

    void updateX();
    void updateY();

    bool valid();

signals:
    void validChanged();
    void acceptChanged();

    void pressed();
    void released();

protected:
    void componentComplete() override;

private:
    void setValid(bool valid);

    QQuickItem* m_node{};
    bool m_valid = true;
    bool m_accept = true;
};
