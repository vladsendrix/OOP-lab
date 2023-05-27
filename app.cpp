#include <memory>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"
#include "test/Test.h"

int main() {
    Test test;
    test.TestAll();
    std::shared_ptr<repository::Repository> scooters = std::make_shared<repository::Repository>();
    std::shared_ptr<controller::ProductController> controller = std::make_shared<controller::ProductController>();
    std::unique_ptr<ui::Console> app = std::make_unique<ui::Console>(controller);
    app->run();
    return 0;
}
