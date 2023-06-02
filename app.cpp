#include <memory>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include <QApplication>
#include "gui/MainWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::shared_ptr<repository::Repository> scooters = std::make_shared<repository::Repository>("ScootersData.csv");
    std::shared_ptr<controller::ProductController> controller = std::make_shared<controller::ProductController>(scooters);
    MainWindow mainWindow(controller);
    mainWindow.show();

    return QApplication::exec();
}
