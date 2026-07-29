#pragma once

#include <QIcon>
#include <QQuickItem>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtLogging>
#include <QtQml>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#define src_dir "H:/projects/cpp/NVT/"
#define data_dir src_dir"temp_storage/"
#define timeline_graph_file data_dir"graph.txt"

namespace nvt {
    void log(std::string str);

    class application;
}

class nvt::application : public QGuiApplication {
public:
    application(int& argc, char** argv);
    ~application();

    bool has_errors();
    std::string error_message();

private:
    void add_error(std::string str);

    QQmlApplicationEngine main_engine{};

    global* g = nullptr;
    std::optional<std::string> err = std::nullopt;
};
