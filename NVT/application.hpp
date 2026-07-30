#pragma once

#include "nvt.hpp"

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
