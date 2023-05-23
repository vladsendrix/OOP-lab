#include <memory>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"
#include "test/Test.h"

int main() {
    Test test;
    test.TestAll();
    std::string repositoryType = ui::inputRepositoryType();
    std::shared_ptr<controller::ProductController> controller = std::make_shared<controller::ProductController>(repositoryType);
    std::unique_ptr<ui::Console> app = std::make_unique<ui::Console>(controller);
    app->run();
    return 0;
}


/*
AAA,Honda Activa,2022-01-05,1200,Central Station,INWAIT
AAB,Vespa Primavera,2021-11-20,800,Old Town Square,INWAIT
AAC,Yamaha Nmax,2022-03-15, 1500,City Hall,INWAIT
AAD,Piaggio Liberty,2021-12-01,1000,Main Street,INWAIT
AAE,Kymco Agility,2022-02-25,900,Shopping Mall,INWAIT
AAF,Suzuki Burgman,2022-04-10,2000,Airport,INWAIT
AAG,BMW C 650 GT,2021-10-15,500,Train Station,INWAIT
AAH,Aprilia SR Motard,2022-05-05,300,University Campus,INWAIT
AAI,SYM Jet,2022-03-20,1200,Beach,INWAIT
AAJ,Triumph Trident,2022-01-20,700,Park,INWAIT
 */