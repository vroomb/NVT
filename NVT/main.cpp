#include <project.hpp>
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

    nvt::application app(argc, argv);
    if (app.has_errors()) {
        nvt::log(app.error_message());
        return -1;
    }

    int r = app.exec();
    return r;
}
