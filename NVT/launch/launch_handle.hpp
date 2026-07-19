#pragma once

#include <QQuickItem>
#include <fstream>
#include <nlohmann/json.hpp>

class LaunchHandle {
public:
    static void set_path_to_launch_list_file(std::string);
    static std::string path_to_launch_list_file();

    LaunchHandle(std::string name, std::string location) {
        m_name     = QString::fromStdString(name);
        m_location = QString::fromStdString(location);
    }

    LaunchHandle(std::string name_colon_location);

    QString name() const {
        return m_name;
    }
    QString location() const {
        return m_location;
    }

private:
    QString m_name;
    QString m_location;

    static std::string m_path_to_launch_list_file;
};
