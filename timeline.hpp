#pragma once

#include "application.hpp"

class TimelineNode : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TimelineNode(QQuickItem* parent = NULL) : QQuickItem(parent) {}

private:
};

class TimelineGraph : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
public:
    explicit TimelineGraph(QQuickItem* parent = NULL) : QQuickItem(parent) {}

    Q_INVOKABLE void update_vertices(qreal i, qreal j, qreal k, qreal l);
    Q_INVOKABLE void add_node(QPointF where);
    Q_INVOKABLE void clear_nodes();

    QPolygonF polygon() const;
    void setPolygon(QPolygonF polygon);

signals:
    void polygonChanged();

protected:
    void componentComplete() override;

private:
    QPolygonF m_polygon{};
    QSet<TimelineNode*> m_nodes{};
};
