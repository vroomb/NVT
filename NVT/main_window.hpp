#pragma once

#include <QQuickWindow>

class NVTMainWindow : public QQuickWindow {
	Q_OBJECT
	QML_ELEMENT
public:
	explicit NVTMainWindow(QWindow* parent = nullptr) : QQuickWindow(parent) {}
};
