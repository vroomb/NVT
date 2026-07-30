#pragma once

#include "nvt.hpp"

class MyItem : public QQuickItem {
	Q_OBJECT
	QML_ELEMENT
public:
	MyItem(QQuickItem* parent);
};
