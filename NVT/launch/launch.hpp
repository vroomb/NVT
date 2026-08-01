#pragma once

#include <QQuickItem>
#include <QQuickWindow>

#include <fstream>
#include <nlohmann/json.hpp>
#include <format>
#include <chrono>
#include <project.hpp>

#if defined(LAUNCHLIB)
#  define LAUNCH_API Q_DECL_EXPORT
#else
#  define LAUNCH_API Q_DECL_IMPORT
#endif

#define prj_dir "H:/projects/cpp/NVT/"
#define src_dir "H:/projects/cpp/NVT/NVT/timeline/"
#define data_dir prj_dir"temp_storage/"

namespace nvt {
	void log(std::string);
}

class LaunchHandle;
class LaunchList;
class NVTLaunchWindow;
