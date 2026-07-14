#pragma once

#include <QIcon>
#include <QQuickItem>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractListModel>
#include <QtLogging>
#include <QtQml>
#include <QMultiMap>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <format>
#include <algorithm>

#define src_dir "H:/projects/cpp/NVT/"
#define data_dir src_dir"temp_storage/"
#define timeline_graph_file data_dir"graph.txt"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

void log(std::string str);
