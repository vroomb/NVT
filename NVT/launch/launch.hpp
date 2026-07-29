#pragma once

#include <QQuickItem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <format>
#include <chrono>
#include <project.hpp>

class LaunchHandle;
class LaunchList;

#define prj_dir "H:/projects/cpp/NVT/"
#define src_dir "H:/projects/cpp/NVT/NVT/timeline/"
#define data_dir prj_dir"temp_storage/"

namespace nvt {
	void log(std::string);
}
