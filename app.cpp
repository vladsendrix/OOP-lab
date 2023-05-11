#include <iostream>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"

int main() {
    repository::Repository scooters=repository::Repository();
    controller::Controller controller;
    ui::ConsoleUI ui(controller);
    ui.run();
    return 0;
}
