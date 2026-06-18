#include "launch.hpp"

LaunchHandle::LaunchHandle(std::string name_colon_location) {
    if (name_colon_location.contains(":") == false) {
        m_name = "parse_error";
        m_location = "parse_error";
        qWarning() << "launchhandle parse error:";
        qWarning() << "parse target: " << name_colon_location;
    } else {
        auto colon_index = name_colon_location.find(":");
        m_name = QString::fromStdString(name_colon_location.substr(0, colon_index));
        m_location = QString::fromStdString(name_colon_location.substr(colon_index + 1));
    }
}

void LaunchModel::add_launch(LaunchHandle handle) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_handles.append(handle);
    endInsertRows();
}

void LaunchModel::init(const std::string& path_to_launch_list_file) {
    std::ifstream i(path_to_launch_list_file);
    std::string s{};

    for (char c = i.get(); c != EOF; c = i.get()) {
        if (c == '\n') {
            if (s.length() != 0) {
                add_launch(LaunchHandle(s));
            }
            s = "";
        } else {
            s.push_back(c);
        }
    }
    if (s.length() != 0) {
        add_launch(LaunchHandle(s));
    }
}
int LaunchModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_handles.count();
}

QVariant LaunchModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= m_handles.count())
        return QVariant();

    const LaunchHandle& handle = m_handles[index.row()];
    if (role == NameRole)
        return handle.name();
    else if (role == LocationRole)
        return handle.location();

    qWarning() << "Unreachable in LaunchModel::data";

    return QVariant();
}

QHash<int, QByteArray> LaunchModel::roleNames() const {
    QHash<int, QByteArray> roles{};
    roles[NameRole] = "name";
    roles[LocationRole] = "location";
    return roles;
}
