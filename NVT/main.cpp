#include <project.hpp>
#include <launch_handle.hpp>
#include "application.hpp"

void nvt::log(std::string str) {
    std::ofstream o(data_dir"log.txt", std::ios::app);
    qDebug() << str;
    if (o.is_open() == false) {
        std::cout << "bruuuh";
        return;
    }
    o << str << "\n";
}

int main(int argc, char *argv[]) {
    nvt::log("New run");

    int r = 0;

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("vroomb");
    QGuiApplication::setApplicationName("NVT");
    QGuiApplication::setWindowIcon(QIcon(src_dir"res/svg/lavender_arrow.svg"));

    // QQmlApplicationEngine engine2;
    // engine2.loadFromModule("NVT.Launch", "LaunchWindow");

    // if (engine2.rootObjects().isEmpty() == true) {
    //     nvt::log("engine2 was empty");
    //     return -1;
    // }

    // r = QGuiApplication::exec();

    QQmlApplicationEngine engine;
    engine.loadFromModule("NVTModule", "Main");

    if (engine.rootObjects().isEmpty() == true) {
        nvt::log("engine was empty");
        return -1;
    }

    r = QGuiApplication::exec();

    return r;
}
