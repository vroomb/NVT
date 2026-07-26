#include "project.hpp"

namespace cr = std::chrono;
using time_point = cr::time_point<cr::steady_clock>;
using seconds = cr::seconds;

nvt::global* nvt::global::m_instance = nullptr;
nvt::project* nvt::project::m_instance = nullptr;

int nvt::global::open(fs::path location) {
    if (m_instance != nullptr) {
        std::cout << "don't instantiate global twice.\n";
        return -1;
    }

    m_instance = new global(location);
    return 0;
}

nvt::global::global(fs::path location) :
    m_location{ location }
{
    auto stream = std::ifstream(location.string() + "config.json");
    config_json = nlohmann::json::parse(stream);

    if (stream.is_open() == true) {

        auto j = config_json["projects"];

        if (j.is_array() == true) {
            for (auto i : j) {
                if ((i["name"].is_string() == true) &&
                    (i["location"].is_string() == true)) {
                    if (i["last updated"].is_number_unsigned() == true)
                        m_launches.push_back({
                            i["name"],
                            i["location"],
                            i["last updated"]
                        });
                    else
                        m_launches.push_back({
                            i["name"],
                            i["location"],
                            0,
                        });
                }
            }

            // for (auto i = m.end() - 1; i != m.begin() - 1; i--) {
            //     addProject(std::get<0>(i.value()), std::get<1>(i.value()), i.key());
            // }

            std::stable_sort(m_launches.begin(), m_launches.end(),
                [](launch_details lhs, launch_details rhs) {
                    return lhs.last_updated > rhs.last_updated;
                }
            );
        }
    }
}

nvt::global* nvt::global::instance() {
    return m_instance;
}

std::list<nvt::launch_details> nvt::global::launches() {
    return m_launches;
}

void nvt::global::add_launch(launch_details ld) {
    config_json["projects"] += {
        { "name",         ld.name         },
        { "location",     ld.location     },
        { "last updated", ld.last_updated }
    };

    std::ofstream(m_location / "config.json",
        std::ios::out | std::ios::trunc) << config_json.dump(2);
}

void nvt::global::rem_launch(std::string location) {
    for (auto& i : config_json["projects"]) if (i["location"] == location)
            i = nullptr;

    std::ofstream(m_location / "config.json",
        std::ios::out | std::ios::trunc) << config_json.dump(2);
}

int nvt::global::close() {
    if (m_instance == nullptr) {
        return -1;
    } else {
        delete m_instance;
        return 0;
    }
}

nvt::global::~global() {}

int nvt::project::open(fs::path location) {
    if (m_instance != nullptr) {
        std::cout << "don't instantiate project twice.\n";
        return -1;
    }

    m_instance = new project(location);
    return 0;
}

nvt::project::project(fs::path location) :
    m_location{ location },
    m_config_dir{ location / ".nvt" }
{
    if (fs::directory_entry(m_config_dir).exists() == false) {
        std::error_code ec{};
        if (fs::create_directory(m_config_dir, ec) == false)
            std::cout << "project directory not created: " << ec << "\n";
    }

    db = std::make_unique<SQLite::Database>((m_config_dir / "db.db").string(),
        SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE
    );

    m_name = location.filename().string();
}

nvt::project* nvt::project::instance() {
    return m_instance;
}

std::string nvt::project::name() {
    return m_name;
}

int nvt::project::close() {
    if (m_instance == nullptr) {
        return -1;
    } else {
        delete m_instance;
        return 0;
    }
}

nvt::project::~project() {}