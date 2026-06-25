#pragma once

#include "application.hpp"

class RepeatingTexture : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QPointF anchorPoint READ anchorPoint WRITE setAnchorPoint NOTIFY anchorPointChanged)
    Q_PROPERTY(bool anchorXEnabled READ anchorXEnabled WRITE setAnchorXEnabled NOTIFY anchorXEnabledChanged)
    Q_PROPERTY(bool anchorYEnabled READ anchorYEnabled WRITE setAnchorYEnabled NOTIFY anchorYEnabledChanged)
    Q_PROPERTY(QQuickItem* anchorItem READ anchorItem WRITE setAnchorItem NOTIFY anchorItemChanged REQUIRED)
    Q_PROPERTY(QQmlComponent* texture READ texture WRITE setTexture NOTIFY textureChanged REQUIRED)
    Q_PROPERTY(qint8 anchorMode READ anchorMode WRITE setAnchorMode NOTIFY anchorModeChanged)
public:
    enum anchor_modes {
        absolute = 0,
        relative = 1,
    };

    explicit RepeatingTexture(QQuickItem* parent = NULL, int mode = relative);

    QPointF anchorPoint() const;
    void setAnchorPoint(QPointF new_anchorPoint);
    void setAnchorPointX(qreal new_anchorPointX);
    void setAnchorPointY(qreal new_anchorPointY);

    QQuickItem* anchorItem() const;
    void setAnchorItem(QQuickItem * new_anchorItem);

    QQmlComponent* texture() const;
    void setTexture(QQmlComponent * new_texture);

    bool anchorXEnabled() const;
    void setAnchorXEnabled(bool new_anchorXEnabled);

    bool anchorYEnabled() const;
    void setAnchorYEnabled(bool new_anchorYEnabled);

    int anchorMode() const;
    void setAnchorMode(int new_anchorMode);

signals:
    void anchorPointChanged();
    void anchorItemChanged();

    void anchorXEnabledChanged();
    void anchorYEnabledChanged();

    void textureChanged();

    void anchorModeChanged();

private:
    QPointF m_anchorPoint{};
    QPointF m_relAnchorPoint{};
    QQuickItem* m_anchorItem = NULL;
    QQmlComponent* m_texture = NULL;
    bool m_anchorXEnabled = false;
    bool m_anchorYEnabled = false;
    int m_anchorMode;
};
