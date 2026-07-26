#pragma once

#include <QQuickItem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <format>
#include <chrono>
#include <project.hpp>

class LaunchHandle;
class LaunchList;

namespace nvt {
	global* global_instance();

	void log(std::string);
}
