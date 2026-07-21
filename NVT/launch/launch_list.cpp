#include "launch_list.hpp"
#include "launch_handle.hpp"

LaunchList::LaunchList(QQuickItem* parent) : QQuickItem(parent) {
    LaunchHandle::set_path_to_launch_list_file("H:/Projects/cpp/NVT/temp_storage/config.json");

    auto i = std::ifstream(LaunchHandle::path_to_launch_list_file());

    if (i.is_open() == true) {
        nlohmann::json j = nlohmann::json::parse(i)["projects"];

        if (j.is_array() == true) {
            for (auto i : j["projects"]) {
                if ((i["name"].is_string() == true) && (i["location"].is_string() == true))
                    addProject(QString::fromStdString(i["name"]), QString::fromStdString(i["location"]));
            }
        }
    }
}

void LaunchList::componentComplete() {
    QQuickItem::componentComplete();
}

QQuickItem* LaunchList::projectListItem() {
    return m_projectListItem;
}

void LaunchList::setProjectListItem(QQuickItem* l) {
    m_projectListItem = l;
    emit projectListItemChanged();
}

QQmlComponent* LaunchList::projectListComponent() {
    return m_projectListComponent.get();
}

void LaunchList::setProjectListComponent(QQmlComponent* l) {
    m_projectListComponent = std::unique_ptr<QQmlComponent>(l);
    emit projectListComponentChanged();
}


void LaunchList::addProject(QString name, QString location) {
    m_handles.insert({ location, name, projectListComponent()});
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
    for (auto &i : m_handles) {
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
