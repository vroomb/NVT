#pragma once

#include "launch.hpp"

using time_point = std::chrono::time_point<std::chrono::steady_clock>;

class LaunchHandle {
public:
    static void set_path_to_launch_list_file(std::string);
    static std::string path_to_launch_list_file();

    LaunchHandle(QString name, QString location, QQmlComponent* component);

    QString name() const {
        return m_name;
    }

    QString location() const {
        return m_location;
    }

    void setParent(QQuickItem* parent) {
        if (m_item != nullptr) m_item->setParentItem(parent);
    }

    void setVisible(bool v) {
        if (m_item != nullptr) m_item->setVisible(v);
    }

    time_point m_last_updated{};
private:
    QString m_name;
    QString m_location;
    std::unique_ptr<QQuickItem> m_item;

    static std::string m_path_to_launch_list_file;
};
