#include "timeline.hpp"

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
    auto item = qobject_cast<TimelineNode*>(object);
    item->setParentItem(this);
    item->setX(where.x());
    item->setY(where.y());

    m_nodes += item;
}

void TimelineGraph::clear_nodes() {
    for (auto i : m_nodes) {
        delete i;
    }
    m_nodes = {};
}

void TimelineGraph::update_vertices(qreal i, qreal j, qreal k, qreal l) {
    setPolygon({ { i, j }, { k, l } });
}

QPolygonF TimelineGraph::polygon() const {
    return m_polygon;
}

void TimelineGraph::setPolygon(QPolygonF polygon) {
    m_polygon = polygon;

    emit polygonChanged();
}
