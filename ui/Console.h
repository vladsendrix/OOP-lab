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

        static void printDetailHeader();

        static void printScooter(const domain::Scooter &scooter);

        static void printArrayOfScooters(const std::vector<domain::Scooter> &scooters);

        static void printMessage(const std::string &message);

        static void preventMenuPopUp();

        static int readNumber();

        static std::string readString();

    };

    std::string inputRepositoryType();

}

#endif