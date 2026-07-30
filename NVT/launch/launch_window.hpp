#pragma once

#include "launch.hpp"

class NVTLaunchWindow : public QQuickItem {
	Q_OBJECT
	QML_ELEMENT
public:
	explicit NVTLaunchWindow(QQuickItem* parent = nullptr) : QQuickItem(parent) {}
};