#pragma once

#include "application.hpp"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))


class TimelineNode {
public:
    TimelineNode();

    static QPolygonF VerticesVH(QPointF FromV, QPointF ToH) {
        qreal a = ToH.x() - FromV.x();
        qreal b = ToH.y() - FromV.y();
        // qreal b = - (ToH.y() - FromV.y());

        qreal B = sgn(b) * max(std::abs(b) - std::abs(a), 0);
        qreal A = sgn(a * b) * (b - B);
        // qreal A = std::signbit(a) * (b - B);

        return QPolygonF{ 
            FromV, 
            {FromV.x(), (FromV.y() + B)},
            {(FromV.x() + A), ToH.y()},
            ToH
        };
    }
    // static QPolygonF VerticesHV(QPointF FromH, QPoint ToV);
    // static QPolygonF VerticesVV(QPointF FromV, QPoint ToV);
    // static QPolygonF VerticesHH(QPointF FromH, QPoint ToH);

private:
};


class TimelineGraph : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TimelineGraph(QQuickItem* parent = NULL) : QQuickItem(parent) {}
    Q_INVOKABLE void add_node();
    Q_INVOKABLE void update_vertices(qreal i, qreal j, qreal k, qreal l) {
        auto v1 = findChild<QQuickItem*>("vertex1");
        auto v2 = findChild<QQuickItem*>("vertex2");

        bool err = false;
        if (v1 == nullptr) {
            err = true;
            log("v1 = nullptr");
        }
        if (v2 == nullptr) {
            err = true;
            log("v2 = nullptr");
        }
        if (err) return;

        auto pg = TimelineNode::VerticesVH({ i, j }, { k, l });

        v1->setX(pg[1].x());
        v1->setY(pg[1].y());

        v2->setX(pg[2].x());
        v2->setY(pg[2].y());

        std::cout << std::format("update: [{:.1f}, {:.1f}], [{:.1f}, {:.1f}], [{:.1f}, {:.1f}], [{:.1f}, {:.1f}]\n",
            pg[0].x(), pg[0].y(),
            pg[1].x(), pg[1].y(),
            pg[2].x(), pg[2].y(),
            pg[3].x(), pg[3].y()
        );
    }
};
