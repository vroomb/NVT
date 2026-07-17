#include "project.hpp"

project::project* project::project::m_instance = nullptr;

project::project::project(fs::path location) :
	m_location{ location },
	m_config_dir{ location / ".nvt" }
{
	if (fs::directory_entry(m_config_dir).exists() == false) {
		std::error_code ec{};
		if (fs::create_directory(m_config_dir, ec) == false)
			std::cout << "project directory not created: " << ec << "\n";
	}

	db = new SQLite::Database(m_config_dir / "db.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE | SQLite::OPEN_FULLMUTEX);

	m_name = location.filename().string();
}

int project::project::instantiate(fs::path location) {
	if (m_instance != nullptr) {
		std::cout << "don't instantiate project twice.\n";
		return -1;
	}

	m_instance = new project(location);
	return 0;
}

project::project* project::project::instance() {
	return m_instance;
}

std::string project::project::name() {
	return m_name;
}