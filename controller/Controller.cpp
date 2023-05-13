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
                state = domain::INWAIT;
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
        ProductController::printDetailHeader();
        for (const auto &scooter: scooters) {
            printScooter(scooter);
        }
    }

    void ProductController::reserveScooter() {
    }

    void ProductController::useScooter() {
    }

    void ProductController::printDetailHeader() {
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Model" <<
                  std::setw(20) << "Commission Date" << std::setw(15) << "Mileage" <<
                  std::setw(20) << "Last Stand Place" << std::setw(15) << "State" << std::endl;
        for (int i=0; i<95; i++) std::cout<<"-";
        std::cout<<std::endl;
    }

    void ProductController::printScooter(const domain::Scooter &scooter) {

        const domain::Date date = scooter.getCommissionDate();
        const std::string dateToString = std::to_string(date.year) + "." + std::to_string(date.month) +
                                         "." + std::to_string(date.day);

        std::cout << std::left << std::setw(5) << scooter.getID()
                  << std::setw(25) << scooter.getModel()
                  << std::setw(20) << dateToString
                  << std::setw(15) << scooter.getMileage()
                  << std::setw(20) << scooter.getLastStandPlace()
                  << std::setw(15) << std::left;

        switch (scooter.getState()) {
            case domain::PARKED:
                std::cout << "PARKED" << std::endl;
                break;
            case domain::RESERVED:
                std::cout << "RESERVED" << std::endl;
                break;
            case domain::INUSE:
                std::cout << "IN USE" << std::endl;
                break;
            case domain::INWAIT:
                std::cout << "IN WAIT" << std::endl;
                break;
            case domain::OUTOFSERVICE:
                std::cout << "OUT OF SERVICE" << std::endl;
                break;
            default:
                std::cout << "PARKED" << std::endl;
        }
    }

    void ProductController::loadDataFromFile() {
        std::ifstream file("../scootersData.txt");
        if (!file.is_open()) {
            std::cout << "Error opening file: scooters.txt" << std::endl;
            return;
        }

        const std::unordered_map<std::string, domain::State> stateMap{
                {"PARKED",       domain::PARKED},
                {"RESERVED",     domain::RESERVED},
                {"INUSE",        domain::INUSE},
                {"INWAIT",       domain::INWAIT},
                {"OUTOFSERVICE", domain::OUTOFSERVICE}
        };
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, model, lastStandPlace, stateString;
            int year, month, day, mileage;

            std::getline(ss, id, ',');
            std::getline(ss, model, ',');
            ss >> year;
            ss.ignore();
            ss >> month;
            ss.ignore();
            ss >> day;
            ss.ignore();
            ss >> mileage;
            ss.ignore();
            std::getline(ss, lastStandPlace, ',');
            std::getline(ss, stateString, ',');


            domain::Date commissionDate{2023, 01, 01};
            if (isValidDate(year, month, day)) {
                commissionDate = {year, month, day};
            }
            domain::State state = domain::PARKED;
            auto stateIt = stateMap.find(stateString);
            if (stateIt != stateMap.end()) {
                state = stateIt->second;
            }
            domain::Scooter scooter(id, model, commissionDate, mileage, lastStandPlace, state);
            this->repo.addScooter(scooter);
        }
        file.close();
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

    bool ProductController::isValidDate(int year, int month, int day) {
        if (month < 1 || month > 12) {
            return false;
        }
        if (day < 1 || day > 31) {
            return false;
        }
        if (month == 2) {
            if (year % 4 == 0) {
                if (year % 100 == 0 && year % 400 != 0) {
                    if (day > 28) {
                        return false;
                    }
                } else {
                    if (day > 29) {
                        return false;
                    }
                }
            } else {
                if (day > 28) {
                    return false;
                }
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) {
                return false;
            }
        }
        return true;
    }


};
