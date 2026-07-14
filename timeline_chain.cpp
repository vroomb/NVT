#include "timeline_chain.hpp"

void TimelinePin::componentComplete() {
    QQuickItem::componentComplete();
    // connect(this, &TimelinePin::xChanged, [this]() {
    //         if (node() == nullptr) return;
    //         if (abs(node()->x() - x()) < 50) setValid(true);
    //         else                             setValid(false);
    //     });
    // connect(this, &TimelinePin::yChanged, [this]() {
    //         if (node() == nullptr) return;
    //         if (abs(node()->y() - y()) < 50) setValid(true);
    //         else                             setValid(false);
    //     });
}

bool TimelinePin::valid() {
    if (node() == nullptr)
        return true;
    if ((abs(node()->x() - x()) < 50) && (abs(node()->y() - y()) < 50))
        return true;
    else
        return false;
}

void TimelinePin::setValid(bool valid) {
    m_valid = valid;
    emit validChanged();
}

bool TimelinePin::accept() {
    return m_accept;
}

void TimelinePin::setAccept(bool accept) {
    m_accept = accept;
    emit acceptChanged();
}

QQuickItem* TimelinePin::node() {
    return m_node;
}

void TimelinePin::setNode(QQuickItem* node) {
    if (m_node != nullptr) {
        disconnect(m_node, nullptr, this, nullptr);
    }

    m_node = node;

    if (m_node != nullptr) {
        connect(m_node, &QQuickItem::xChanged, this, &TimelinePin::updateX);
        connect(m_node, &QQuickItem::yChanged, this, &TimelinePin::updateY);
        updateX();
        updateY();
    }
}

void TimelinePin::updateX() {
    setX(m_node->x());
}

void TimelinePin::updateY() {
    setY(m_node->y());
}

void TimelineChain::componentComplete() {
    QQuickItem::componentComplete();

    m_start = create_pin();
    m_end = create_pin();
    m_cursor = create_pin();

    m_start->setY(600);
    m_cursor->setAccept(false);
    m_end->setX(1000);

    switch (m_chainMode) {
    case horizontal:
        break;
    case vertical:
        break;
    default:
        log("unreachable TimelineChain::componentComplete on m_chainMode = " + std::to_string(m_chainMode));
        break;
    }

    connect(this, &TimelineChain::cursorEnabledChanged, this, &TimelineChain::update_polygon);

    update_polygon();
}

// questions? consult this graph: https://www.desmos.com/calculator/imc5insskm
bool TimelineChain::hit(QPointF where) {
    bool result = false;

    qreal l = strokeWidth() + hitWidth();

    auto x = where.x();
    auto y = where.y();

    for (int i = 0; (i < (m_path.length() - 1)) && (result == false); i++) {
        auto a = m_path[i].x();
        auto b = m_path[i].y();
        auto c = m_path[i+1].x();
        auto d = m_path[i+1].y();

        if (b == d) {
            result = ((((a < x) && (x < c)) || ((c < x) && (x < a))) && (abs(y - b) < l));
            continue;
        } else if (a == c) {
            result = ((((b < y) && (y < d)) || ((d < y) && (y < b))) && (abs(x - a) < l));
            continue;
        }

        auto tan_m = (b - d) / (a - c);
        auto csc_m = sqrt(1 + tan_m * tan_m) / tan_m;

        result = (((tan_m * (x - a - l * csc_m) + b) < y) && (y < (tan_m * (x - a + l * csc_m) + b)))
            && (((((-1 / tan_m) * (x - a) + b) < y) && (y < ((-1 / tan_m) * (x - c) + d)))
                || ((((-1 / tan_m) * (x - a) + b) > y) && (y > ((-1 / tan_m) * (x - c) + d))));
    }
    return result;
}

// questions? consult this graph: https://www.desmos.com/calculator/imc5insskm
QPointF TimelineChain::hit_project(QPointF where) {
    bool result = false;

    qreal l = strokeWidth() + hitWidth();

    auto x = where.x();
    auto y = where.y();

    int i = 0;
    for (; (i < (m_path.length() - 1)) && (result == false); i++) {
        auto a = m_path[i].x();
        auto b = m_path[i].y();
        auto c = m_path[i + 1].x();
        auto d = m_path[i + 1].y();

        if (b == d) {
            result = ((((a < x) && (x < c)) || ((c < x) && (x < a))) && (abs(y - b) < l));
            continue;
        }
        else if (a == c) {
            result = ((((b < y) && (y < d)) || ((d < y) && (y < b))) && (abs(x - a) < l));
            continue;
        }

        auto tan_m = (b - d) / (a - c);
        auto csc_m = sqrt(1 + tan_m * tan_m) / tan_m;

        result = (((tan_m * (x - a - l * csc_m) + b) < y) && (y < (tan_m * (x - a + l * csc_m) + b)))
            && (((((-1 / tan_m) * (x - a) + b) < y) && (y < ((-1 / tan_m) * (x - c) + d)))
                || ((((-1 / tan_m) * (x - a) + b) > y) && (y > ((-1 / tan_m) * (x - c) + d))));
    }

    if (result == false)
        return { std::numeric_limits<qreal>::infinity(), std::numeric_limits<qreal>::infinity() };

    auto a = m_path[i - 1].x();
    auto b = m_path[i - 1].y();
    auto c = m_path[i].x();
    auto d = m_path[i].y();
    if (b == d)
        return { x, b };
    else if (a == c)
        return { a, y };
    else {
        auto m = (b - d) / (a - c);
        auto h = (x + m * (y + m * a - b)) / (m * m + 1);
        auto k = m * (h - a) + b;
        return { h, k };
    }
}

TimelinePin* TimelineChain::create_pin() {
    auto engine = qmlEngine(this);
    QString qml_file = src_dir"qml/Pin.qml";
    QQmlComponent comp(engine, QUrl::fromLocalFile(qml_file));
    if (comp.isError()) {
        qWarning() << "Failed to load " << qml_file << ": " << comp.errors();
        return nullptr;
    }
    auto item = qobject_cast<TimelinePin*>(comp.create());
    if (comp.isError()) {
        qWarning() << "Failed to create " << qml_file << ": " << comp.errors();
        return nullptr;
    }
    item->setParentItem(this);

    connect(item, &QQuickItem::xChanged, this, &TimelineChain::update_polygon);
    connect(item, &QQuickItem::yChanged, this, &TimelineChain::update_polygon);
    item->setOpacity(debug_pin_opacity);
    return item;
}

TimelinePin* TimelineChain::pin(QQuickItem* item) {
    if (item == nullptr)     return nullptr;
    if (pins.contains(item)) return pins[item];

    auto pin = create_pin();
    pin->setNode(item);

    pins.insert(item, pin);
    update_polygon();

    connect(pin, &TimelinePin::released, this, &TimelineChain::validate);

    return pin;
}

void TimelineChain::unpin(QQuickItem* item) {
    if (pins.contains(item)) {
        delete m_cursor;

        m_cursor = pins[item];
        m_cursor->setNode(nullptr);

        pins.remove(item);
    } else {
        log("TimelineChain::unpin(): you tried to remove a pin that doesn't exist");
    }
}

void TimelineChain::validate() {
    for (auto i : pins.keys()) {
        auto j = pins[i];
        if (j->valid() == false)
            unpin(i);
        else {
            j->updateX(); j->updateY(); 
        }
    }
    update_polygon();
}

TimelinePin* TimelineChain::start() {
    return m_start;
}

TimelinePin* TimelineChain::cursor() {
    return m_cursor;
}

TimelinePin* TimelineChain::end() {
    return m_end;
}

qint8 TimelineChain::chainMode() const {
    return m_chainMode;
}

void TimelineChain::setChainMode(qint8 chainMode) {
    m_chainMode = chainMode;
    emit chainModeChanged();
}

qint32 TimelineChain::strokeWidth() const {
    return m_strokeWidth;
}

void TimelineChain::setStrokeWidth(qint32 width) {
    m_strokeWidth = width;
    emit strokeWidthChanged();
}

qint32 TimelineChain::hitWidth() const {
    return m_hitWidth;
}

void TimelineChain::setHitWidth(qint32 width) {
    m_hitWidth = width;
    emit hitWidthChanged();
}

bool TimelineChain::cursorEnabled() const {
    return m_cursorEnabled;
}

void TimelineChain::setCursorEnabled(bool enabled) {
    m_cursorEnabled = enabled;
    emit cursorEnabledChanged();
}

QPolygonF TimelineChain::polygon() const {
    return m_polygon;
}

void TimelineChain::setPolygon(QPolygonF polygon) {
    m_polygon = polygon;
    emit polygonChanged();

    update_path();
}

void TimelineChain::update_polygon() {
    QPolygonF result{};

    result += {m_start->x(), m_start->y()};
    result += {m_end->x(), m_end->y()};

    if (cursorEnabled()) result += {m_cursor->x(), m_cursor->y()};

    for (auto i : pins) {
        result += {i->x(), i->y()};
    }

    auto mode = chainMode();

    std::stable_sort(result.begin(), result.end(),
        [mode](QPointF lhs, QPointF rhs) {
            if (mode == horizontal) return lhs.x() < rhs.x();
            else                    return lhs.y() < rhs.y();
        }
    );
    
    setPolygon(result);
}

void TimelineChain::update_path() {
    QPolygonF result{};

    int i = 0;
    for (; i < (m_polygon.length() - 1); i++) {
        if (chainMode() == horizontal)
            result += VerticesHH(m_polygon[i], m_polygon[i + 1]);
        else if (chainMode() == vertical)
            result += VerticesVV(m_polygon[i], m_polygon[i + 1]);
    }

    result += m_polygon[i];

    setPath(result);
}

QPolygonF TimelineChain::path() const {
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
