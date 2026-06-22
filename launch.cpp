#include "launch.hpp"

std::string LaunchModel::path_to_launch_list_file = "";

LaunchHandle::LaunchHandle(std::string name_colon_location) {
    if (name_colon_location.contains(":") == false) {
        m_name = "parse_error";
        m_location = "parse_error";
        qWarning() << "launchHandle parse error:";
        qWarning() << "parse target: " << name_colon_location;
    } else {
        auto colon_index = name_colon_location.find(":");
        m_name = QString::fromStdString(name_colon_location.substr(0, colon_index));
        m_location = QString::fromStdString(name_colon_location.substr(colon_index + 1));
    }
}

void LaunchModel::set_path_to_launch_list_file(std::string p) {
    LaunchModel::path_to_launch_list_file = p;
}

void LaunchModel::add_launch(LaunchHandle handle) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_handles.append(handle);
    endInsertRows();
}

void LaunchModel::init() {
    std::ifstream i(path_to_launch_list_file);

    if (i.is_open() == false) {
        qWarning() << "launch file \"" << path_to_launch_list_file << "\" not found or is busy.";
        return;
    }

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

std::string LaunchModel::generate_launch_list_file() {
    std::string s = "";
    for (auto i : m_handles) {
        s = s + i.name().toLocal8Bit() + ":" + i.location().toLocal8Bit() + "\n";
    }
    s.pop_back();
    return s;
}

void LaunchModel::overwrite_launch_list_file() {
    std::ofstream o(path_to_launch_list_file, std::ios::out | std::ios::trunc);

    if (o.is_open() == false) {
        qWarning() << "launch file \"" << path_to_launch_list_file << "\" not found or is busy.";
        return;
    }

    o << generate_launch_list_file();
}

QHash<int, QByteArray> LaunchModel::roleNames() const {
    QHash<int, QByteArray> roles{};
    roles[NameRole] = "name";
    roles[LocationRole] = "location";
    return roles;
}
