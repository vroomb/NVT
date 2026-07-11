#include "timeline_chain.hpp"

qint8 TimelineChain::chainMode() const {
    return m_chainMode;
}
void TimelineChain::setChainMode(qint8 chainMode) {
    m_chainMode = chainMode;
    emit chainModeChanged();
}

QPolygonF TimelineChain::polygon() const {
    return m_polygon;
}
void TimelineChain::setPolygon(QPolygonF polygon) {
    m_polygon = polygon;
    emit polygonChanged();

    update_path();
}

void TimelineChain::update_path() {
    QPolygonF result{};

    int i = 0;
    for (; i < (m_polygon.length() - 1); i++) {
        if (chainMode() == horizontal)
            result += VerticesHH(m_polygon[i], m_polygon[i + 1]);
        else if (chainMode() == vertical)
            result += VerticesVV(m_polygon[i], m_polygon[i + 1]);
    }

    result += m_polygon[i];

    setPath(result);
}

QPolygonF TimelineChain::path() const {
    return m_path;
}
void TimelineChain::setPath(QPolygonF path) {
    m_path = path;
    emit pathChanged();
}

QPolygonF TimelineChain::VerticesVH(QPointF FromV, QPointF ToH) {
    qreal a = ToH.x() - FromV.x();
    qreal b = ToH.y() - FromV.y();

    qreal B = sgn(b) * max(std::abs(b) - std::abs(a), 0);
    qreal A = sgn(a * b) * (b - B);

    return QPolygonF{ 
        FromV, 
        {FromV.x(), (FromV.y() + B)},
        {(FromV.x() + A), ToH.y()},
    };
}

QPolygonF TimelineChain::VerticesHV(QPointF FromH, QPointF ToV) {
    qreal a = FromH.x() - ToV.x();
    qreal b = FromH.y() - ToV.y();

    qreal B = sgn(b) * max(std::abs(b) - std::abs(a), 0);
    qreal A = sgn(a * b) * (b - B);

    return QPolygonF{ 
        FromH, 
        {(ToV.x() + A), FromH.y()},
        {ToV.x(), (ToV.y() + B)},
    };
}

QPolygonF TimelineChain::VerticesVV(QPointF FromV, QPointF ToV) {
    auto median = (FromV + ToV) / 2;

    auto p = VerticesVH(FromV, median);
    p += VerticesHV(median, ToV);

    return p;
}

QPolygonF TimelineChain::VerticesHH(QPointF FromH, QPointF ToH) {
    auto median = (FromH + ToH) / 2;

    auto p = VerticesHV(FromH, median);
    p += VerticesVH(median, ToH);

    return p;
}
