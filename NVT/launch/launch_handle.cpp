#include "launch_handle.hpp"

std::string LaunchHandle::m_path_to_launch_list_file = "";

LaunchHandle::LaunchHandle(std::string name_colon_location) {
    if (name_colon_location.contains(":") == false) {
        m_name = "parse_error";
        m_location = "parse_error";
        qWarning() << "launchHandle parse error:";
        qWarning() << "parse target: " << name_colon_location;
    } else {
        auto colon_index = name_colon_location.find(":");
        m_name = QString::fromStdString(name_colon_location.substr(0, colon_index));
        m_location = QString::fromStdString(name_colon_location.substr(colon_index + 1));
    }
}

std::string LaunchHandle::path_to_launch_list_file() {
    return m_path_to_launch_list_file;
}

void LaunchHandle::set_path_to_launch_list_file(std::string p) {
    m_path_to_launch_list_file = p;
}
