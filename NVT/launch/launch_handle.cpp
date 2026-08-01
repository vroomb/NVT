#include "launch_handle.hpp"

LaunchHandle::LaunchHandle(const nvt::launch_details ld, QQmlComponent* component) :
    m_name    { QString::fromStdString(ld.name)              },
    m_location{ QString::fromStdString(ld.location.string()) }
{
    m_item = std::unique_ptr<QQuickItem>(qobject_cast<QQuickItem*>(component->create()));
    if (component->isError()) {
        qWarning() << "LaunchHandle::LaunchHandle(): " << component->errors();
    }
    m_item->setProperty("name", m_name);
    m_item->setProperty("location", m_location);
}
