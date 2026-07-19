#include <project.hpp>
#include "application.hpp"
#include "launch.hpp"

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

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("vroomb");
    QGuiApplication::setApplicationName("NVT");
    QGuiApplication::setWindowIcon(QIcon(src_dir"res/svg/lavender_arrow.svg"));

    //LaunchHandle::set_path_to_launch_list_file(data_dir"thing.txt");

    QQmlApplicationEngine engine;
    engine.loadFromModule("NVTModule", "Main");

    if (engine.rootObjects().isEmpty() == true) {
        nvt::log("engine was empty");
        return -1;
    }

    nvt::project::open(data_dir"project1");

    int r = QGuiApplication::exec();

    nvt::project::close();

    return r;
}
