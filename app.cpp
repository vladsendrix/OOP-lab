#include <iostream>
#include "ui/Console.h"

int main() {
    repository::Repository scooters=repository::Repository();
    controller::ProductController controller=controller::ProductController(scooters);
    ui::Console ui=ui::Console(controller);
    ui.run();
    return 0;
}
