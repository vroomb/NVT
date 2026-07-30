#pragma once

#include <QQuickWindow>
#include <QQuickItem>

class MainWindow : public QQuickItem {
	Q_OBJECT
	QML_ELEMENT
public:
	explicit MainWindow(QQuickItem* parent);
};
