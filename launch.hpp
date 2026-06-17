#pragma once

#include "application.hpp"

class launch : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit launch(QQuickItem* parent = NULL) : QQuickItem(parent) {}
    Q_INVOKABLE QString say_hello();
};
