#include "application.hpp"
#include "launch.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ofstream log(src_dir"log.txt", std::ios::app);
    log << "\n\n\nNew run\n-------";

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("vroomb");
    QGuiApplication::setApplicationName("NVT");
    QGuiApplication::setWindowIcon(QIcon(src_dir"res/svg/lavender_arrow.svg"));

    QQmlApplicationEngine engine;
    // engine.load(QUrl("qrc:/src/main.qml"));
    engine.loadFromModule("NVTModule", "Main");

    if (engine.rootObjects().isEmpty() == true) {
        log << "\n" << "engine was empty";
        return -1;
    }

    return QGuiApplication::exec();
}
