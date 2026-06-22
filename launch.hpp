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


// TODO: Turn this into a QSet based thing
class LaunchModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT

public:
    static void set_path_to_launch_list_file(std::string);

    enum LaunchRoles {
        NameRole = Qt::UserRole + 1,
        LocationRole,
    };

    explicit LaunchModel(QQuickItem* parent = NULL) : QAbstractListModel(parent) {
        init();
    }

    void add_launch(LaunchHandle handle);
    void init();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    std::string generate_launch_list_file();
    void overwrite_launch_list_file();
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<LaunchHandle> m_handles{};
    static std::string path_to_launch_list_file;
};
