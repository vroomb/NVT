#include "application.hpp"
#include <project/global.hpp>
#include <project/story.hpp>

nvt::application::application(int& argc, char** argv) :
    QGuiApplication(argc, argv)
{
    setOrganizationName("vroomb");
    setApplicationName("NVT");
    setWindowIcon(QIcon(src_dir"res/svg/lavender_arrow.svg"));

    if (nvt::global::open(data_dir) != 0) {
        add_error("nvt::global::open() failed");
        return;
    }
    g = nvt::global::instance();

    engine.loadFromModule("NVT.Launch", "LaunchWindow");
    if (engine.rootObjects().isEmpty() == true) {
        add_error("nvt::application::engine was empty");
        return;
    }

    launch_window = qobject_cast<NVTLaunchWindow*>(engine.rootObjects()[0]);

    connect(launch_window, &NVTLaunchWindow::launchRequested, this, &nvt::application::launch_project);
}

nvt::application::~application() {
    nvt::story::close();
    nvt::global::close();
}

void nvt::application::add_error(std::string str) {
    err = error_message() + str + "\n";
}

bool nvt::application::has_errors() {
    return (err != std::nullopt);
}

std::string nvt::application::error_message() {
    if (err != std::nullopt)
        return err.value();
    else
        return "";
}

int nvt::application::launch_project(QString location) {
    int r = nvt::story::open(location.toStdString());

    // if (r == 0) {

    // } else {

    // }

    launch_window->deleteLater();
    launch_window = nullptr;

    engine.loadFromModule("NVTModule", "Main");

    auto m = engine.rootObjects();
    auto m2 = engine.children();

    main_window = qobject_cast<MainWindow*>(engine.rootObjects().back());

    if (main_window->isVisible() == false) main_window->show();

    return r;
}
