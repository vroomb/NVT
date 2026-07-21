#pragma once

#include "launch.hpp"

// TODO: Turn this into a QSet based thing
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

    // create new contents for list file
    std::string generate_launch_list_file();

    QString launchLocation();
    void setLaunchLocation(QString l);

    QQuickItem* projectListItem();
    void setProjectListItem(QQuickItem* l);

    QQmlComponent* projectListComponent();
    void setProjectListComponent(QQmlComponent* l);

    Q_INVOKABLE void addProject(QString name, QString location);

    // overwrite previous contents with updated ones
    Q_INVOKABLE void overwrite_launch_list_file();

signals:
    void launchLocationChanged();
    void launchRequested();
    void projectListItemChanged();
    void projectListComponentChanged();

protected:
    void componentComplete() override;

private:
    QSet<LaunchHandle> m_handles{};

    QString m_launchLocation{};
    QQuickItem* m_projectListItem{};
    std::unique_ptr<QQmlComponent> m_projectListComponent{};
};
