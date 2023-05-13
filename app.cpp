#include <iostream>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"

int main() {
    repository::Repository scooters = repository::Repository();
    controller::ProductController controller=controller::ProductController(scooters);
    ui::Console app=ui::Console(controller);
    app.run();
    return 0;
}
