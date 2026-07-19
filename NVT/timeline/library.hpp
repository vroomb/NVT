#pragma once

#include <QQuickItem>
#include <QGuiApplication>
#include <QtLogging>
#include <QtQml>
#include <QMap>

//#include <project.hpp>

#include <string>
#include <cmath>

#define prj_dir "H:/projects/cpp/NVT/"
#define src_dir "H:/projects/cpp/NVT/NVT/timeline/"
#define data_dir prj_dir"temp_storage/"
#define timeline_graph_file data_dir"graph.txt"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

namespace nvt {
	void log(std::string str);
}

