#pragma once

#include "application.hpp"

class TimelineChain : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    // Q_PROPERTY(qint8 chainMode READ chainMode WRITE setChainMode NOTIFY chainModeChanged)
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
    Q_PROPERTY(QPolygonF path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(qint32 strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)
    Q_PROPERTY(qint32 hitWidth READ hitWidth WRITE setHitWidth NOTIFY hitWidthChanged)
    Q_PROPERTY(bool cursorEnabled READ cursorEnabled WRITE setCursorEnabled NOTIFY cursorEnabledChanged)
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

    qint32 strokeWidth() const;
    void setStrokeWidth(qint32 width);

    qint32 hitWidth() const;
    void setHitWidth(qint32 width);

    bool cursorEnabled() const;
    void setCursorEnabled(bool enabled);

    void update_path();
    void update_polygon();
    QQuickItem* add_pin(QQuickItem* item);
    QQuickItem* create_pin();
    Q_INVOKABLE bool hit(QPointF where);
    Q_INVOKABLE QPointF hit_project(QPointF where);

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
    void strokeWidthChanged();
    void hitWidthChanged();
    void cursorEnabledChanged();

protected:
    void componentComplete() override;

private:
    qint8 m_chainMode = horizontal;
    qint32 m_strokeWidth = 16;
    qint32 m_hitWidth = 16;
    bool m_cursorEnabled = false;

    QPolygonF m_path{};
    QPolygonF m_polygon{};

    QQuickItem* start{};
    QQuickItem* end{};
    QQuickItem* cursor{};
    QList<QQuickItem*> pins{};
};

