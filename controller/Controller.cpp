#include "Controller.h"

namespace controller {
    ProductController::ProductController(const repository::Repository &scooterRepo) {
        this->repo = scooterRepo;
    }

    void ProductController::addScooter() {
    }

    void ProductController::deleteScooter() {
    }

    void ProductController::editScooter() {
    }

    void ProductController::searchScooterByStandPlace() { 
        std::cout << "Enter the stand place: " << std::endl;
        int standPlace;
        std::cin >> standPlace;
        std::vector<domain::Scooter> scooters = this->repo.getScooters();
        for (auto &scooter : scooters) {
            if (scooter.getLastStandPlace() == standPlace) {
                std::cout << scooter.getName() << std::endl;
            }
        }  
    }

    void ProductController::filterScooterByAge() {
        std::cout << "Enter the age: " << std::endl;
        int age;
        std::cin >> age;
        std::vector<domain::Scooter> scooters = this->repo.getScooters();
        for (auto &scooter : scooters) {
            if (scooter.getAge() > age) {
                std::cout << scooter.getName() << std::endl;
            }
        }
    }

    void ProductController::filterScooterByMileage() {
        std::cout << "Enter the mileage. " << std::endl;
        int mileage;
        std::cin >> mileage;
        std::vector<domain::Scooter> scooters = this->repo.getScooters();
        for (auto &scooter : scooters) {
            if (scooter.getMileage() > mileage) {
                std::cout << scooter.getName() << std::endl;
            }
        }
    }

    void ProductController::listScooterByAge() {
        std::vector<domain::Scooter> scooters = this->repo.getScooters();
        std::sort(scooters.begin(), scooters.end(), [](domain::Scooter &scooter1, domain::Scooter &scooter2) {
            return scooter1.getAge() < scooter2.getAge();
        });
        for (auto &scooter : scooters) {
            std::cout << scooter.getName() << std::endl;
        }

    }
    void ProductController::reserveScooter() {
    }
    void ProductController::useScooter()
    {
    }
};