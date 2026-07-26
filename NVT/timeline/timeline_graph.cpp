#include "timeline_graph.hpp"

void TimelineGraph::componentComplete() {
    QQuickItem::componentComplete();
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

    connect(item, &TimelineNode::remove, this,
        [this, item]() {
            remove_node(item);
        });

    m_nodes.insert(item);
}

void TimelineGraph::remove_node(TimelineNode* what) {
    if (m_nodes.contains(what)) {
        what->deleteLater();
        m_nodes.erase(what);
    } else {
        nvt::log("TimelineGraph::remove_node(): tried to remove a node that isn't in the timeline graph.");
    }
}

QQuickItem* TimelineGraph::fetch_node(QPointF where) {
    QQuickItem* result = nullptr;
    for (auto i : m_nodes) {
        if ((abs(where.x() - i->x()) < 50) && (abs(where.y() - i->y()) < 50)) result = i;
    }
    return result;
}

void TimelineGraph::add_chain(QPointF where) {
    auto engine = qmlEngine(this);
    QString qml_file = src_dir"qml/Chain.qml";
    QQmlComponent comp(engine, QUrl::fromLocalFile(qml_file));
    if (comp.isError()) {
        qWarning() << "Failed to load " << qml_file << ": " << comp.errors();
        return;
    }
    auto item = qobject_cast<TimelineChain*>(comp.create());
    if (comp.isError()) {
        qWarning() << "Failed to create " << qml_file << ": " << comp.errors();
        return;
    }
    item->setParentItem(this);
    item->setX(where.x());
    item->setY(where.y());

    connect(item, &TimelineChain::remove, this,
        [this, item]() {
            remove_chain(item);
        });

    m_chains.insert(item);
}

void TimelineGraph::remove_chain(TimelineChain* what) {
    if (m_chains.contains(what)) {
        what->deleteLater();
        m_chains.erase(what);
    } else {
        nvt::log("TimelineGraph::remove_chain(): tried to remove a chain that isn't in the timeline graph.");
    }
}

QQuickItem* TimelineGraph::fetch_chain(QPointF where) {
    QQuickItem* result = nullptr;
    for (auto i : m_chains) {
        if (i->hit(where)) {
            result = i;
            break;
        }
    }
    return result;
}

void TimelineGraph::clear_nodes() {
    for (auto i : m_nodes) {
        delete i;
    }
    m_nodes = {};
}
