#include "timeline.hpp"

qint8 TimelineChain::chainMode() {
    return m_chainMode;
}
void TimelineChain::setChainMode(qint8 chainMode) {
    m_chainMode = chainMode;
    emit chainModeChanged();
}

QPolygonF TimelineChain::polygon() {
    return m_polygon;
}
void TimelineChain::setPolygon(QPolygonF polygon) {
    m_polygon = polygon;
    emit polygonChanged();

    update_path();
}

void TimelineChain::update_path() {
    QPolygonF result{};

    for (int i = 0; i < (m_polygon.length() - 1); i++) {
        if (chainMode() == horizontal)
            result += VerticesHH(m_polygon[i], m_polygon[i + 1]);
        else if (chainMode() == vertical)
            result += VerticesVV(m_polygon[i], m_polygon[i + 1]);
    }

    setPath(result);
}

QPolygonF TimelineChain::path() {
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

// ---------------------------------------------------------------------------

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

void TimelineGraph::add_node(QPointF where) {
    auto engine = qmlEngine(this);
    QQmlComponent comp(engine, QUrl::fromLocalFile(src_dir"qml/Node.qml"));
    if (comp.isError()) {
        qWarning() << "Failed to load Node.qml:" << comp.errors();
        return;
    }
    auto object = comp.create();
    if (comp.isError()) {
        qWarning() << "Failed to create Node.qml:" << comp.errors();
        return;
    }
    auto item = qobject_cast<QQuickItem*>(object);
    item->setParentItem(this);
    item->setX(where.x());
    item->setY(where.y());
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
