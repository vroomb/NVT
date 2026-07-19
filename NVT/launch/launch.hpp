#pragma once

#include <QQuickItem>
#include <fstream>
#include <nlohmann/json.hpp>
#include "launch_handle.hpp"

// TODO: Turn this into a QSet based thing
class LaunchList : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString launchLocation READ launchLocation WRITE setLaunchLocation NOTIFY launchLocationChanged)
public:
    explicit LaunchList(QQuickItem* parent = NULL);

    // create new contents for list file
    std::string generate_launch_list_file();

    QString launchLocation();
    void setLaunchLocation(QString l);

    Q_INVOKABLE void addProject(LaunchHandle handle);

    // overwrite previous contents with updated ones
    Q_INVOKABLE void overwrite_launch_list_file();

signals:
    void launchLocationChanged();
    void launchRequested();

private:
    QList<LaunchHandle> m_handles{};

    QString m_launchLocation{};
};
