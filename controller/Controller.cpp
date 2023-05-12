#include "Controller.h"

namespace controller {

    ProductController::ProductController(const repository::Repository &scooterRepo) {
        this->repo = scooterRepo;
    }


    void ProductController::addScooter() {

        std::string id, model, lastStandPlace, date;
        domain::Date commissionDate{};
        domain::State state;
        int mileage, stateNr;

        if (!repo.getScooters().empty()) id = generateID(repo.getScooters().back().getID());
        else id = "AAA";

        std::cout << "Enter the scooter details:\nModel: ";
        std::cin >> model;
        std::cout << "Comission Date (yyyy-mm-dd): ";
        std::cin >> date;
        commissionDate.year = std::stoi(date.substr(0, 4));
        commissionDate.month = std::stoi(date.substr(5, 2));
        commissionDate.day = std::stoi(date.substr(8, 2));
        std::cout << "Mileage: ";
        std::cin >> mileage;
        std::cout << "Last Stand Place: ";
        std::cin >> lastStandPlace;
        std::cout << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT| 5.OUT OF SERVICE)\nChoose one (1-5): ";
        std::cin >> stateNr;

        switch (stateNr) {
            case 2:
                state = domain::RESERVED;
                break;
            case 3:
                state = domain::INUSE;
                break;
            case 4:
                state = domain::INWAIT;
                break;
            case 5:
                state = domain::OUTOFSERVICE;
                break;
            default:
                state = domain::PARKED;
        }

        domain::Scooter newScooter = domain::Scooter(id, model, commissionDate, mileage, lastStandPlace, state);
        repo.addScooter(newScooter);
        std::cout << "Scooter added successfully!" << std::endl;

        //std::cin.ignore();
    }

    void ProductController::deleteScooter() {
        std::string scooterID;
        std::cout << "Enter the ID of the scooter to delete: ";
        std::cin >> scooterID;
        scooterID = scooterID.substr(0, 3);
        std::transform(scooterID.begin(), scooterID.end(), scooterID.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        int index = 0;
        std::vector<domain::Scooter> scooters = repo.getScooters();
        for (const auto &scooter: scooters) {
            if (scooter.getID() == scooterID) {
                break;
            }
            index++;
        }
        if (index == scooters.size()) {
            std::cout << "Scooter not found!" << std::endl;
        } else {
            domain::Scooter scooterToDelete = scooters.at(index);
            repo.deleteScooter(scooterToDelete);
            std::cout << "Scooter deleted successfully!" << std::endl;
        }
    }

    void ProductController::editScooter() {
        std::string scooterID;
        std::cout << "Enter the ID of the scooter to edit: ";
        std::cin >> scooterID;

        scooterID = scooterID.substr(0, 3);
        std::transform(scooterID.begin(), scooterID.end(), scooterID.begin(),
                       [](unsigned char c) { return std::toupper(c); });


        int index = 0;
        std::vector<domain::Scooter> scooters = repo.getScooters();
        for (const auto &scooter: scooters) {
            if (scooter.getID() == scooterID) {
                break;
            }
            index++;
        }
        if (index == scooters.size()) {
            std::cout << "Scooter not found!" << std::endl;
        } else {

            domain::Scooter *scooterToEdit = &scooters.at(index);

            std::string model, lastStandPlace, mileage, date;
            domain::Date commissionDate{};
            domain::State state;
            int stateNr;

            std::cout << "Edit Comission Date (yyyy-mm-dd): ";
            std::getline(std::cin, date);
            if (!date.empty()) {
                commissionDate.year = std::stoi(date.substr(0, 4));
                commissionDate.month = std::stoi(date.substr(5, 2));
                commissionDate.day = std::stoi(date.substr(8, 2));
                scooterToEdit->setCommissionDate(commissionDate);
            }

            std::cout << "Mileage: ";
            std::getline(std::cin, mileage);

            std::cout << "Last Stand Place: ";
            std::cin >> lastStandPlace;
            std::cout
                    << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT| 5.OUT OF SERVICE)\nChoose one (1-5): ";
            std::cin >> stateNr;

            switch (stateNr) {
                case 2:
                    state = domain::RESERVED;
                    break;
                case 3:
                    state = domain::INUSE;
                    break;
                case 4:
                    state = domain::INWAIT;
                    break;
                case 5:
                    state = domain::OUTOFSERVICE;
                    break;
                default:
                    state = domain::PARKED;
            }
            scooterToEdit->setState(state);
            std::cout << "Scooter edited successfully!" << std::endl;
        }
    }

    void ProductController::searchScooterByStandPlace() {
        std::string standPlace;
        std::cout << "Enter the stand place: ";
        std::cin >> standPlace;

        std::vector<domain::Scooter> scooters = repo.getScooters();
        bool found = false;
        for (const auto &scooter: scooters) {
            if (scooter.getLastStandPlace() == standPlace) {
                printScooter(scooter);
                found = true;
            }
            if (!found) {
                std::cout << "No scooters found with the specified stand place!" << std::endl;
            }
        }
    }

    void ProductController::filterScooterByAge() {
        int age;
        std::cout << "Enter the age: ";
        std::cin >> age;

        std::vector<domain::Scooter> scooters = repo.getScooters();
        bool found = false;
        for (const auto &scooter: scooters) {
            if (scooter.getMileage() > age) {
                std::cout << "Scooter: " << scooter.getID() << std::endl;
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
        for (const auto &scooter: scooters) {
            if (scooter.getMileage() > mileage) {
                printScooter(scooter);
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
        std::sort(scooters.begin(), scooters.end(),
                  [](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                      return scooter1.getMileage() < scooter2.getMileage();
                  });

        std::cout << "List of scooters sorted by age:" << std::endl;
        for (const auto &scooter: scooters) {
            printScooter(scooter);
        }
    }

    void ProductController::reserveScooter() {
    }

    void ProductController::useScooter() {
    }

    std::string ProductController::generateID(const std::string &id_) {
        if (id_.length() != 3) {
            return "";
        }
        std::string result = id_;
        if (result[2] == 'Z') {
            result[2] = 'A';

            if (result[1] == 'z') {
                result[1] = 'A';

                if (result[0] == 'Z') {
                    return "";
                } else {
                    result[0]++;
                }
            } else {
                result[1]++;
            }
        } else {
            result[2]++;
        }
        return result;
    }

    void ProductController::printScooter(const domain::Scooter &scooter) {
        std::cout << "Scooter: nr. " << scooter.getID() << std::endl
                  << "Model: " << scooter.getModel() << std::endl
                  << "Commission date: " << scooter.getCommissionDate().year << "."
                  << scooter.getCommissionDate().month << "."
                  << scooter.getCommissionDate().day << std::endl
                  << "Mileage: " << scooter.getMileage() << std::endl
                  << "Last stand place: " << scooter.getMileage() << std::endl
                  << "Last stand place: " << scooter.getMileage() << std::endl
                  << "State: ";
        switch (scooter.getState()) {
            case domain::PARKED:
                std::cout << "PARKED\n\n";
                break;
            case domain::RESERVED:
                std::cout << "RESERVED\n\n";
                break;
            case domain::INUSE:
                std::cout << "IN USE\n\n";
                break;
            case domain::INWAIT:
                std::cout << "IN WAIT\n\n";
                break;
            case domain::OUTOFSERVICE:
                std::cout << "OUT OF SERVICE\n\n";
                break;
            default:
                std::cout << "PARKED\n\n";
        }
    }

};
