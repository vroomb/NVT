#pragma once

#include "../application.hpp"

class app::launch : public QQuickItem {
    Q_OBJECT
public:
    explicit launch(QQuickItem* parent = NULL) : QQuickItem(parent) {}
    Q_INVOKABLE QString say_hello();
};
