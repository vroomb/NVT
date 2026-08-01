#pragma once

#include "nvt.hpp"

class MainWindow : public QQuickWindow {
	Q_OBJECT
	QML_ELEMENT
public:
	MainWindow(QQuickWindow* parent = nullptr);
};
