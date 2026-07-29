#include <project.hpp>
#include "application.hpp"

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

    main_engine.loadFromModule("NVTModule", "Main");
    if (main_engine.rootObjects().isEmpty() == true) {
        add_error("nvt::application::main_engine was empty");
        return;
    }
}

nvt::application::~application() {
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
