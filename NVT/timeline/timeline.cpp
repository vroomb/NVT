#include "timeline.hpp"

void TimelineGraph::componentComplete() {
    QQuickItem::componentComplete();
    add_node({ 300, 100 });

    //nvt::project::instantiate(data_dir"project1/");
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

QQuickItem* TimelineGraph::fetch_node(QPointF where) {
    QQuickItem* result = nullptr;
    for (auto i : m_nodes) {
        if ((abs(where.x() - i->x()) < 50) && (abs(where.y() - i->y()) < 50)) result = i;
    }
    return result;
}

void TimelineGraph::clear_nodes() {
    for (auto i : m_nodes) {
        delete i;
    }
    m_nodes = {};
}
