#pragma once

#include "launch.hpp"

class NVTLaunchWindow : public QQuickWindow {
	Q_OBJECT
	QML_ELEMENT
public:
	explicit NVTLaunchWindow(QWindow* parent = nullptr) : QQuickWindow(parent) {}
};