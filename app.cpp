#include <iostream>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"

int main() {
    repository::Repository scooters=repository::Repository();
    controller::ProductController controller=controller::ProductController(scooters);
    ui::Console ui=ui::Console(controller);
    ui.run();
    return 0;
}
