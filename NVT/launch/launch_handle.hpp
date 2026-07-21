#pragma once

#include "launch.hpp"

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

private:
    QString m_name;
    QString m_location;
    std::unique_ptr<QQuickItem> m_item;

    static std::string m_path_to_launch_list_file;
};
