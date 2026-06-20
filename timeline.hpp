#pragma once

#include "application.hpp"

class TimelineGraph : public QQuickItem {
	Q_OBJECT
	QML_ELEMENT
public:
	explicit TimelineGraph(QQuickItem* parent = NULL) : QQuickItem(parent) {}
};
