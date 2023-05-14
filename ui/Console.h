#ifndef CONSOLE_H
#define CONSOLE_H
#include "../controller/Controller.h"

namespace ui {
    class Console {
    private:
        controller::ProductController ctrl;
    public:
        explicit Console(controller::ProductController &scooterController);

        void run();

        void adminMethods();

        void userMethods();
    };
}

#endif