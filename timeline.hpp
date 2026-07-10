#pragma once

#include "application.hpp"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

#define timeline_graph_file data_dir"graph.txt"


class TimelineNode : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TimelineNode(QQuickItem* parent = NULL) : QQuickItem(parent) {}

private:
};

class TimelineChain : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(qint8 chainMode READ chainMode WRITE setChainMode NOTIFY chainModeChanged)
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
    Q_PROPERTY(QPolygonF path READ path WRITE setPath NOTIFY pathChanged)
public:
    explicit TimelineChain(QQuickItem* parent = NULL) : QQuickItem(parent) {}

    enum ChainMode {
        vertical,
        horizontal
    };

    qint8 chainMode();
    void setChainMode(qint8 chainMode);

    QPolygonF polygon();
    void setPolygon(QPolygonF polygon);

    void update_path();

    QPolygonF path();
    void setPath(QPolygonF polygon);

    static QPolygonF VerticesVH(QPointF FromV, QPointF ToH);
    static QPolygonF VerticesHV(QPointF FromH, QPointF ToV);
    static QPolygonF VerticesVV(QPointF FromV, QPointF ToV);
    static QPolygonF VerticesHH(QPointF FromH, QPointF ToH);

signals:
    void chainModeChanged();
    void polygonChanged();
    void pathChanged();

private:
    qint8 m_chainMode;
    QPolygonF m_path{};
    QPolygonF m_polygon{};
};

class TimelineGraph : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
public:
    explicit TimelineGraph(QQuickItem* parent = NULL) : QQuickItem(parent) {}

    Q_INVOKABLE void add_node(QPointF where);
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
