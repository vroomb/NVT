#include "launch_list.hpp"
#include "launch_handle.hpp"

namespace cr = std::chrono;
using time_point = cr::time_point<cr::steady_clock>;
using seconds = cr::seconds;

LaunchList::LaunchList(QQuickItem* parent) : QQuickItem(parent) {
    LaunchHandle::set_path_to_launch_list_file("H:/Projects/cpp/NVT/temp_storage/config.json");
}

LaunchList::~LaunchList() {
    overwrite_launch_list_file();

    for (auto i : m_handles) {
        delete i;
    }
}

void LaunchList::componentComplete() {
    QQuickItem::componentComplete();

    auto stream = std::ifstream(LaunchHandle::path_to_launch_list_file());

    if (stream.is_open() == true) {
        nlohmann::json j = nlohmann::json::parse(stream)["projects"];
        if (j.is_array() == true) {

            QMultiMap<time_point, std::pair<QString, QString>> m{};

            for (auto i : j) {
                if ((i["name"].is_string() == true) && (i["location"].is_string() == true)) {
                    if (i["last updated"].is_number_unsigned() == true)
                        m.insert(
                            time_point(seconds(i["last updated"])),
                            std::pair(
                                QString::fromStdString(i["name"]),
                                QString::fromStdString(i["location"])
                            )
                        );
                    else
                        m.insert(
                            time_point(seconds(0)),
                            std::pair(
                                QString::fromStdString(i["name"]),
                                QString::fromStdString(i["location"])
                            )
                        );
                }
            }

            for (auto i = m.end() - 1; i != m.begin() - 1; i--) {
                addProject(std::get<0>(i.value()), std::get<1>(i.value()), i.key());
            }
        }
    }
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

LaunchHandle* LaunchList::project(QString location) {
    for (auto i : m_handles)
        if (i->location() == location) return i;
    return nullptr;
}

void LaunchList::removeProject(QString location) {
    for (auto i : m_handles) {
        if (i->location() == location) {
            delete i;
            m_handles.remove(i);
        }
    }
}

void LaunchList::addProject(QString name, QString location, time_point tp) {
    removeProject(location);

    auto h = new LaunchHandle{ name, location, projectListComponent() };
    h->setParent(projectListItem());
    h->m_last_updated = tp;
    m_handles.insert(h);
}

QString LaunchList::launchLocation() {
    return m_launchLocation;
}

void LaunchList::setLaunchLocation(QString l) {
    m_launchLocation = l;
    emit launchLocationChanged();
}

std::string LaunchList::generate_launch_list_file() {
    auto i = std::ifstream(LaunchHandle::path_to_launch_list_file());

    nlohmann::json j = nullptr;

    if (i.is_open() == true) j = nlohmann::json::parse(i);

    j["projects"].clear();
    j["projects"] = nlohmann::json::array();

    for (auto i : m_handles) {
        j["projects"] += {
            { "name",         i->name().toStdString() },
            { "location",     i->location().toStdString() },
            { "last updated", cr::duration_cast<seconds>(i->m_last_updated.time_since_epoch()).count() }
        };
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

void LaunchList::find(QString text) {
    for (auto i : m_handles) {
        if (i->name().startsWith(text)) i->setVisible(true);
        else                            i->setVisible(false);
    }
}
