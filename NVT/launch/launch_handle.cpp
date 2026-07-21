#include "launch_handle.hpp"

std::string LaunchHandle::m_path_to_launch_list_file = "";

std::string LaunchHandle::path_to_launch_list_file() {
    return m_path_to_launch_list_file;
}

void LaunchHandle::set_path_to_launch_list_file(std::string p) {
    m_path_to_launch_list_file = p;
}

LaunchHandle::LaunchHandle(QString name, QString location, QQmlComponent* component) :
    m_name{ name },
    m_location{ location }
{
    if (component->isError()) {
        qWarning() << "LaunchHandle::LaunchHandle(): " << component->errors();
    }
    m_item = std::unique_ptr<QQuickItem>(qobject_cast<QQuickItem*>(component->create()));
    if (component->isError()) {
        qWarning() << "LaunchHandle::LaunchHandle(): " << component->errors();
    }
    m_item->setProperty("name", m_name);
    m_item->setProperty("location", m_location);
}
