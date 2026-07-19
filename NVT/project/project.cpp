#include "project.hpp"

nvt::project* nvt::project::m_instance = nullptr;

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

nvt::project::~project() {}

int nvt::project::open(fs::path location) {
    if (m_instance != nullptr) {
        std::cout << "don't instantiate project twice.\n";
        return -1;
    }

    m_instance = new project(location);
    return 0;
}

int nvt::project::close() {
    if (m_instance == nullptr) {
        return -1;
    } else {
        delete m_instance;
        return 0;
    }
}

nvt::project* nvt::project::instance() {
    return m_instance;
}

std::string nvt::project::name() {
    return m_name;
}