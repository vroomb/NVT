#include "timeline.hpp"

QPolygonF TimelineGraph::VerticesVH(QPointF FromV, QPointF ToH) {
    qreal a = ToH.x() - FromV.x();
    qreal b = ToH.y() - FromV.y();

    qreal B = sgn(b) * max(std::abs(b) - std::abs(a), 0);
    qreal A = sgn(a * b) * (b - B);

    return QPolygonF{ 
        FromV, 
        {FromV.x(), (FromV.y() + B)},
        {(FromV.x() + A), ToH.y()},
        ToH
    };
}

QPolygonF TimelineGraph::VerticesHV(QPointF FromH, QPointF ToV) {
    qreal a = FromH.x() - ToV.x();
    qreal b = FromH.y() - ToV.y();

    qreal B = sgn(b) * max(std::abs(b) - std::abs(a), 0);
    qreal A = sgn(a * b) * (b - B);

    return QPolygonF{ 
        FromH, 
        {(ToV.x() + A), FromH.y()},
        {ToV.x(), (ToV.y() + B)},
        ToV
    };
}

QPolygonF TimelineGraph::VerticesVV(QPointF FromV, QPointF ToV) {
    auto median = (FromV + ToV) / 2;

    auto p = VerticesVH(FromV, median);
    p.pop_back();
    p += VerticesHV(median, ToV);

    return p;
}
QPolygonF TimelineGraph::VerticesHH(QPointF FromH, QPointF ToH) {
    auto median = (FromH + ToH) / 2;

    auto p = VerticesHV(FromH, median);
    p.pop_back();
    p += VerticesVH(median, ToH);

    return p;
}

void TimelineGraph::add_node() {
    log("heh");
}

void TimelineGraph::update_vertices(qreal i, qreal j, qreal k, qreal l) {
    setPolygon(VerticesHH({ i, j }, { k, l }));
}

QPolygonF TimelineGraph::polygon() {
    return m_polygon;
}

void TimelineGraph::setPolygon(QPolygonF polygon) {
    m_polygon = polygon;

    emit polygonChanged();
}
