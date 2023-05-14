#include <memory>
#include "repository/Repository.h"
#include "controller/Controller.h"
#include "ui/Console.h"

int main() {
    std::shared_ptr<repository::Repository> scooters = std::make_shared<repository::Repository>();
    std::shared_ptr<controller::ProductController> controller = std::make_shared<controller::ProductController>();
    std::unique_ptr<ui::Console> app = std::make_unique<ui::Console>(controller);
    app->run();
    return 0;
}


/*
AAA,Honda Activa,2022-01-05,1200,Central Station,PARKED
AAB,Vespa Primavera,2021-11-20,800,Old Town Square,PARKED
AAC,Yamaha Nmax,2022-03-15, 1500,City Hall,PARKED
AAD,Piaggio Liberty,2021-12-01,1000,Main Street,PARKED
AAE,Kymco Agility,2022-02-25,900,Shopping Mall,PARKED
AAF,Suzuki Burgman,2022-04-10,2000,Airport,PARKED
AAG,BMW C 650 GT,2021-10-15,500,Train Station,PARKED
AAH,Aprilia SR Motard,2022-05-05,300,University Campus,PARKED
AAI,SYM Jet,2022-03-20,1200,Beach,PARKED
AAJ,Triumph Trident,2022-01-20,700,Park,PARKED
 */