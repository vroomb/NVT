#include "timeline.hpp"

void TimelineGraph::componentComplete() {
    QQuickItem::componentComplete();
    add_node({ 300, 100 });
}

void TimelineGraph::add_node(QPointF where) {
    auto engine = qmlEngine(this);
    QString qml_file = src_dir"qml/Node.qml";
    QQmlComponent comp(engine, QUrl::fromLocalFile(qml_file));
    if (comp.isError()) {
        qWarning() << "Failed to load " << qml_file << ": " << comp.errors();
        return;
    }
    auto item = qobject_cast<TimelineNode*>(comp.create());
    if (comp.isError()) {
        qWarning() << "Failed to create " << qml_file << ": " << comp.errors();
        return;
    }
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
