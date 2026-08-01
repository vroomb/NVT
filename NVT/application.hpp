#pragma once

#include "nvt.hpp"

#include <project.hpp>
#include <launch_window.hpp>
#include "main_window.hpp"

class nvt::application : public QGuiApplication {
public:
    application(int& argc, char** argv);
    ~application();

    bool has_errors();
    std::string error_message();

private:
    void add_error(std::string str);
    int launch_project(QString location);

    QQmlApplicationEngine engine{};

    global* g = nullptr;
    std::optional<std::string> err = std::nullopt;

    NVTLaunchWindow* launch_window = nullptr;
    MainWindow* main_window = nullptr;
};
