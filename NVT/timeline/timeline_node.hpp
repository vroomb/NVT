#pragma once

#include "library.hpp"

class TimelineNode : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TimelineNode(QQuickItem* parent = NULL) : QQuickItem(parent) {}

signals:
    void pressed();
    void released();

private:
};
