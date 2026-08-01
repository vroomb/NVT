#pragma once

#include "launch.hpp"

class LAUNCH_API NVTLaunchWindow : public QQuickWindow {
	Q_OBJECT
	QML_ELEMENT
public:
	explicit NVTLaunchWindow(QQuickWindow* parent = nullptr) : QQuickWindow(parent) {}

signals:
	void launchRequested(QString location);
};