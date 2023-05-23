#include <memory>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"
#include "test/Test.h"

int main() {
    //Test test;
    //test.TestAll();
    std::string repositoryType = ui::inputRepositoryType();
    std::shared_ptr<controller::ProductController> controller = std::make_shared<controller::ProductController>(repositoryType);
    std::unique_ptr<ui::Console> app = std::make_unique<ui::Console>(controller);
    app->run();
    return 0;
}
