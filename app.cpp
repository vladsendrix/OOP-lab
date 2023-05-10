#include <iostream>
#include "controller/Controller.h"
#include "ui/Console.h"

int main() {
    controller::Controller controller;
    ui::ConsoleUI ui(controller);
    ui.run();
    return 0;
}
