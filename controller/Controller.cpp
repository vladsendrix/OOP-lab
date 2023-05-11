#include "Controller.h"

namespace controller {
    ProductController::ProductController(repository::Repository& scooterRepo) {
        this->repo = scooterRepo;
    }

    void ProductController::addScooter() {
        domain::Scooter newScooter;
        std::cout << "Enter the scooter details:" << std::endl;
        std::cin.ignore();

        repo.addScooter(newScooter);
        std::cout << "Scooter added successfully!" << std::endl;
    }

    void ProductController::deleteScooter() {
        std::string scooterID;
        std::cout << "Enter the ID of the scooter to delete: ";
        std::cin >> scooterID;

        domain::Scooter scooterToDelete;
        std::vector<domain::Scooter> scooters = repo.getScooters();
        for (const auto& scooter : scooters) {
            if (scooter.getID() == scooterID) {
                scooterToDelete = scooter;
                break;
            }
        }

        if (scooterToDelete.getID().empty()) {
            std::cout << "Scooter not found!" << std::endl;
        } else {
            repo.deleteScooter(scooterToDelete);
            std::cout << "Scooter deleted successfully!" << std::endl;
        }
    }

    void ProductController::editScooter() {
        std::string scooterID;
        std::cout << "Enter the ID of the scooter to edit: ";
        std::cin >> scooterID;

        domain::Scooter editedScooter;
        std::cout << "Enter the updated details of the scooter:" << std::endl;
        std::cin.ignore();

        std::vector<domain::Scooter> scooters = repo.getScooters();
        for (auto& scooter : scooters) {
            if (scooter.getID() == scooterID) {
                scooter = editedScooter;
                break;
            }
        }

        repo.editScooter(editedScooter);
        std::cout << "Scooter edited successfully!" << std::endl;
    }

    void ProductController::searchScooterByStandPlace() {
        std::string standPlace;
        std::cout << "Enter the stand place: ";
        std::cin >> standPlace;

        std::vector<domain::Scooter> scooters = repo.getScooters();
        bool found = false;
        for (const auto& scooter : scooters) {
            if (scooter.getLastStandPlace() == standPlace) {
                std::cout << "Scooter: " << scooter.getName() << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No scooters found with the specified stand place!" << std::endl;
        }
    }by mileage

void ProductController::filterScooterByAge() {
        int age;
        std::cout << "Enter the age: ";
        std::cin >> age;

        std::vector<domain::Scooter> scooters = repo.getScooters();
        bool found = false;
        for (const auto& scooter : scooters) {
            if (scooter.getAge() > age) {
                std::cout << "Scooter: " << scooter.getName() << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No scooters found with an age greater than " << age << " years!" << std::endl;
        }
    }

    void ProductController::filterScooterByMileage() {
        int mileage;
        std::cout << "Enter the mileage: ";
        std::cin >> mileage;

        std::vector<domain::Scooter> scooters = repo.getScooters();
        bool found = false;
        for (const auto& scooter : scooters) {
            if (scooter.getMileage() > mileage) {
                std::cout << "Scooter: " << scooter.getName() << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No scooters found with a mileage greater than " << mileage << " miles!" << std::endl;
        }
    }

    void ProductController::listScooterByAge() {
        std::vector<domain::Scooter> scooters = repo.getScooters();

        // Sort the scooters by age in ascending order
        std::sort(scooters.begin(), scooters.end(), [](const domain::Scooter& scooter1, const domain::Scooter& scooter2) {
            return scooter1.getAge() < scooter2.getAge();
        });

        std::cout << "List of scooters sorted by age:" << std::endl;
        for (const auto& scooter : scooters) {
            std::cout << "Scooter: " << scooter.getName() << ", Age: " << scooter.getAge() << " years" << std::endl;
        }
    }
    void ProductController::reserveScooter() {
    }
    void ProductController::useScooter()
    {
    }
};