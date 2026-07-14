#pragma once

#include "application.hpp"

#define debug_pin_opacity 0

class TimelinePin : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickItem* node READ node WRITE setNode)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
    Q_PROPERTY(bool accept READ accept WRITE setAccept NOTIFY acceptChanged)

public:
    explicit TimelinePin(QQuickItem* parent = NULL): QQuickItem(parent) {}

    QQuickItem* node();
    void setNode(QQuickItem* node);

    bool accept();
    void setAccept(bool accept);

    void updateX();
    void updateY();

    bool valid();

signals:
    void validChanged();
    void acceptChanged();

    void pressed();
    void released();

protected:
    void componentComplete() override;

private:
    void setValid(bool valid);

    QQuickItem* m_node{};
    bool m_valid = true;
    bool m_accept = true;
};

class TimelineChain : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT

    // Q_PROPERTY(qint8 chainMode READ chainMode WRITE setChainMode NOTIFY chainModeChanged)
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
    Q_PROPERTY(QPolygonF path READ path WRITE setPath NOTIFY pathChanged)

    Q_PROPERTY(qint32 strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)
    Q_PROPERTY(qint32 hitWidth READ hitWidth WRITE setHitWidth NOTIFY hitWidthChanged)

    Q_PROPERTY(bool cursorEnabled READ cursorEnabled WRITE setCursorEnabled NOTIFY cursorEnabledChanged)
    Q_PROPERTY(QQuickItem* start READ start)
    Q_PROPERTY(QQuickItem* cursor READ cursor)
    Q_PROPERTY(QQuickItem* end READ end)

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

    TimelinePin* create_pin();

    TimelinePin* start();
    TimelinePin* cursor();
    TimelinePin* end();

    Q_INVOKABLE bool hit(QPointF where);
    Q_INVOKABLE QPointF hit_project(QPointF where);
    Q_INVOKABLE TimelinePin* pin(QQuickItem* node);
    Q_INVOKABLE void unpin(QQuickItem* node);
    Q_INVOKABLE void validate();

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

    TimelinePin* m_start{};
    TimelinePin* m_end{};
    TimelinePin* m_cursor{};
    QMap<QQuickItem*, TimelinePin*> pins{};
};

