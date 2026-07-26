#pragma once

#include "launch.hpp"
#include <project.hpp>

namespace cr = std::chrono;
using time_point = cr::time_point<cr::steady_clock>;
using seconds = cr::seconds;

class LaunchList : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString launchLocation
        READ   launchLocation
        WRITE  setLaunchLocation
        NOTIFY launchLocationChanged
    )

    Q_PROPERTY(QQuickItem* projectListItem
        READ   projectListItem
        WRITE  setProjectListItem
        NOTIFY projectListItemChanged
    )

    Q_PROPERTY(QQmlComponent* projectListComponent
        READ   projectListComponent
        WRITE  setProjectListComponent
        NOTIFY projectListComponentChanged
    )

public:
    explicit LaunchList(QQuickItem* parent = NULL);
    ~LaunchList();

    // create new contents for list file
    std::string generate_launch_list_file();

    QString launchLocation();
    void setLaunchLocation(QString l);

    QQuickItem* projectListItem();
    void setProjectListItem(QQuickItem* l);

    QQmlComponent* projectListComponent();
    void setProjectListComponent(QQmlComponent* l);

    LaunchHandle* project(QString location);

    void addProject(nvt::launch_details &ld);

    Q_INVOKABLE void reset();

    Q_INVOKABLE void createProject(QString name, QString location);
    Q_INVOKABLE void removeProject(QString location);

    Q_INVOKABLE void find(QString text);

signals:
    void launchLocationChanged();
    void launchRequested();
    void projectListItemChanged();
    void projectListComponentChanged();

protected:
    void componentComplete() override;

private:
    std::set<LaunchHandle*> m_handles{};

    QString m_launchLocation{};
    QQuickItem* m_projectListItem{};
    std::unique_ptr<QQmlComponent> m_projectListComponent{};
};
