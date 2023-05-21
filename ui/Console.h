#ifndef CONSOLE_H
#define CONSOLE_H

#include "../controller/Controller.h"
#include <memory>
#include <iomanip>

namespace ui {
    class Console {
    private:
        std::shared_ptr<controller::ProductController> ctrl;
    public:
        explicit Console(std::shared_ptr<controller::ProductController> scooterController);

        void run();

        void adminMethods();

        void userMethods();

        void printDetailHeader() ;

        void printScooter(const domain::Scooter &scooter);

        void printArrayOfScooters(const std::vector<domain::Scooter> &scooters);

    };
}

#endif