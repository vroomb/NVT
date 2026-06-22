#pragma once

#include <QIcon>
#include <QQuickItem>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractListModel>
#include <QtLogging>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <format>

#define src_dir "H:/projects/cpp/NVT/"
#define data_dir src_dir"temp_storage/"

void log(std::string str);
