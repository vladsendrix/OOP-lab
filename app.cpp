#include <memory>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"
#include <iostream>
#include <QApplication>
#include "gui/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}


//int main() {
//    std::shared_ptr<repository::Repository> scooters = std::make_shared<repository::Repository>();
//    std::shared_ptr<controller::ProductController> controller = std::make_shared<controller::ProductController>();
//    std::unique_ptr<ui::Console> app = std::make_unique<ui::Console>(controller);
//    app->run();
//    return 0;
//}
