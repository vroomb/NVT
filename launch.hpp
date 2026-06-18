#pragma once

#include "application.hpp"

class LaunchHandle {
public:
    LaunchHandle(std::string name, std::string location) {
        m_name     = QString::fromStdString(name);
        m_location = QString::fromStdString(location);
    }

    LaunchHandle(std::string name_colon_location);

    QString name() const {
        return m_name;
    }
    QString location() const {
        return m_location;
    }

private:
    QString m_name;
    QString m_location;
};


// TODO: Turn this into a qset based thing
class LaunchModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
    // QML_SINGLETON

public:
    enum LaunchRoles {
        NameRole = Qt::UserRole + 1,
        LocationRole,
    };

    explicit LaunchModel(QQuickItem* parent = NULL) : QAbstractListModel(parent) {
        // add_launch(LaunchHandle("hey", "hey"));
        // add_launch(LaunchHandle("hey", "hey"));
        // add_launch(LaunchHandle("hey", "hey"));
        // add_launch(LaunchHandle("hey", "hey"));
        init(data_dir"thing.txt");
    }

    void add_launch(LaunchHandle handle);

    void init(const std::string& path_to_launch_list_file);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<LaunchHandle> m_handles{};
};
