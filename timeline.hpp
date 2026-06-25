#pragma once

#include "application.hpp"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))


class TimelineNode {
public:
    TimelineNode();

private:
};


class TimelineGraph : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
public:
    explicit TimelineGraph(QQuickItem* parent = NULL) : QQuickItem(parent) {}

    Q_INVOKABLE void add_node();
    Q_INVOKABLE void update_vertices(qreal i, qreal j, qreal k, qreal l);

    QPolygonF polygon();
    void setPolygon(QPolygonF polygon);

    static QPolygonF VerticesVH(QPointF FromV, QPointF ToH);
    static QPolygonF VerticesHV(QPointF FromH, QPointF ToV);
    static QPolygonF VerticesVV(QPointF FromV, QPointF ToV);
    static QPolygonF VerticesHH(QPointF FromH, QPointF ToH);

signals:
    void polygonChanged();

private:
    QPolygonF m_polygon{};
    QList<TimelineNode> m_nodes{};
};
