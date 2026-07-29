#include "launch_list.hpp"
#include "launch_handle.hpp"

void nvt::log(std::string str) {
    std::ofstream o(data_dir"log.txt", std::ios::app);
    qDebug() << str;
    if (o.is_open() == false) {
        std::cout << "bruuuh";
        return;
    }
    o << str << "\n";
}

LaunchList::LaunchList(QQuickItem* parent) : QQuickItem(parent) {}

LaunchList::~LaunchList() {
    for (auto i : m_handles) delete i;
}

void LaunchList::componentComplete() {
    QQuickItem::componentComplete();
    
    nvt::log("what");
    
    reset();
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
    auto g = nvt::global::instance();
    g->rem_launch(location.toStdString());

    reset();
}

void LaunchList::createProject(QString name, QString location) {
    auto g = nvt::global::instance();
    location = location + "/" + name;
    g->rem_launch(location.toStdString());

    nvt::launch_details ld{
        name.toStdString(),
        location.toStdString(),
        cr::duration_cast<seconds>(cr::steady_clock::now().time_since_epoch()).count()
    };

    g->add_launch(ld);

    reset();
}

void LaunchList::addProject(nvt::launch_details& ld) {
    auto h = new LaunchHandle{ ld, projectListComponent() };
    h->setParent(projectListItem());
    m_handles.insert(h);
}

void LaunchList::reset() {
    for (auto i : m_handles) delete i;
    m_handles.clear();

    auto g = nvt::global::instance();
    for (auto &i : g->launches()) addProject(i);
}

QString LaunchList::launchLocation() {
    return m_launchLocation;
}

void LaunchList::setLaunchLocation(QString l) {
    m_launchLocation = l;
    emit launchLocationChanged();
}

void LaunchList::find(QString text) {
    for (auto i : m_handles) {
        if (i->name().startsWith(text)) i->setVisible(true);
        else                            i->setVisible(false);
    }
}
