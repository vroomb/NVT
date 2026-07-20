#include "launch.hpp"

void LaunchList::addProject(LaunchHandle handle) {
    m_handles.append(handle);
}

LaunchList::LaunchList(QQuickItem* parent) : QQuickItem(parent) {
    auto i = std::ifstream(LaunchHandle::path_to_launch_list_file());

    if (i.is_open() == true) {
        nlohmann::json j = nlohmann::json::parse(i)["projects"];

        if (j.is_array() == true) {
            for (auto i : j["projects"]) {
                if ((i["name"].is_string() == false) && (i["location"].is_string() == false))
                    addProject({ i["name"], i["location"] });
            }
        }
    }
}

QString LaunchList::launchLocation() {
    return m_launchLocation;
}

void LaunchList::setLaunchLocation(QString l) {
    m_launchLocation = l;
    emit launchLocationChanged();
}

std::string LaunchList::generate_launch_list_file() {
    nlohmann::json j =
        nlohmann::json::parse(std::ifstream(LaunchHandle::path_to_launch_list_file()));

    j["projects"].clear();
    for (auto i : m_handles) {
        j["projects"]["name"]     = i.name().toStdString();
        j["projects"]["location"] = i.location().toStdString();
    }

    return j.dump(2);
}

void LaunchList::overwrite_launch_list_file() {
    auto s = generate_launch_list_file();
    std::ofstream o(LaunchHandle::path_to_launch_list_file(), std::ios::out | std::ios::trunc);

    o.clear();
    if (o.is_open() == false) {
        qWarning() << "launch file \"" 
            << LaunchHandle::path_to_launch_list_file() << "\" not found or is busy.";
        return;
    }
    o << s;
}
