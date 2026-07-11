#pragma once

#include "application.hpp"

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

    qint8 chainMode() const;
    void setChainMode(qint8 chainMode);

    QPolygonF polygon() const;
    void setPolygon(QPolygonF polygon);

    void update_path();

    QPolygonF path() const;
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
    qint8 m_chainMode = vertical;

    QPolygonF m_path{};
    QPolygonF m_polygon{};

    QSet<QQuickItem*> inserted_pins{};
    QSet<QQuickItem*> inserter_pins{};
};

