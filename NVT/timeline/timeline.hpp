#pragma once

#include "application.hpp"
#include "timeline_node.hpp"
#include "timeline_chain.hpp"

class TimelineGraph : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TimelineGraph(QQuickItem* parent = NULL) : QQuickItem(parent) {}

    Q_INVOKABLE void add_node(QPointF where);
    Q_INVOKABLE QQuickItem* fetch_node(QPointF where);
    Q_INVOKABLE void clear_nodes();

signals:
    void polygonChanged();

protected:
    void componentComplete() override;

private:
    QPolygonF m_polygon{};
    QSet<TimelineNode*> m_nodes{};
};
