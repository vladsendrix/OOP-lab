#include "Controller.h"

namespace controller {

    ProductController::ProductController(const repository::Repository &scooterRepo) {
        this->repo = scooterRepo;
    }


    void ProductController::addScooter() {

        std::string id, model, lastStandPlace, date;
        domain::Date commissionDate{2023,01,01};
        domain::State state;
        int mileage, stateNr;

        if (!repo.getScooters().empty()) id = generateID(repo.getScooters().back().getID());
        else id = "AAA";

        std::cout << std::endl << "Enter the scooter details:\nModel: ";
        std::getline(std::cin >> std::ws, model);

        std::cout << std::endl << "Commission Date (yyyy-mm-dd): ";
        std::getline(std::cin >> std::ws, date);
        if (!date.empty()) {
            commissionDate.year = std::stoi(date.substr(0, 4));
            commissionDate.month = std::stoi(date.substr(5, 2));
            commissionDate.day = std::stoi(date.substr(8, 2));
        }


        std::cout << std::endl << "Mileage: ";
        std::cin >> mileage;

        std::cout << std::endl << "Last Stand Place: ";
        std::getline(std::cin >> std::ws, lastStandPlace);

        std::cout << std::endl
                  << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT | 5. OUT OF SERVICE)\nChoose one (1-5): ";
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
        std::cout << std::endl;
        domain::Scooter newScooter = domain::Scooter(id, model, commissionDate, mileage, lastStandPlace, state);
        repo.addScooter(newScooter);

        printDetailHeader();
        printScooter(newScooter);

        saveDataToFile();

        std::cout << "\nScooter added successfully!" << std::endl;

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

            std::string model, lastStandPlace, date;
            domain::Date commissionDate{2023,01,01};
            domain::State state;
            int stateNr,mileage;

            std::cout << std::endl << "Enter new commission Date (yyyy-mm-dd): ";
            std::getline(std::cin >> std::ws, date);
            if (!date.empty()) {
                commissionDate.year = std::stoi(date.substr(0, 4));
                commissionDate.month = std::stoi(date.substr(5, 2));
                commissionDate.day = std::stoi(date.substr(8, 2));
            }

            std::cout << std::endl << "Mileage: ";
            std::cin >> mileage;

            std::cout << std::endl << "Last Stand Place: ";
            std::getline(std::cin >> std::ws, lastStandPlace);

            std::cout << std::endl
                      << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT | 5. OUT OF SERVICE)\nChoose one (1-5): ";
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
            std::cout << std::endl;

            scooterToEdit->setCommissionDate(commissionDate);
            scooterToEdit->setMileage(mileage);
            scooterToEdit->setLastStandPlace(lastStandPlace);
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

    void ProductController::filterScooterByAge(bool lowerThan) {
        int age;
        std::string sortType;
        std::cout << "Enter the age: ";
        std::cin >> age;
        age=2022-age;
        bool printHeader = true;
        bool found = false;
        std::vector<domain::Scooter> scooters = repo.getScooters();

        if (lowerThan) {
            for (const auto &scooter: scooters) {
                if (scooter.getCommissionDate().year > age) {
                    if (printHeader) {
                        printDetailHeader();
                    }
                    printScooter(scooter);
                    printHeader = false;
                    found = true;
                }
            }
        } else {
            for (const auto &scooter: scooters) {
                if (scooter.getCommissionDate().year <= age) {
                    if (printHeader) {
                        printDetailHeader();
                    }
                    printScooter(scooter);
                    printHeader = false;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "No scooters found with an age greater than " << age << " years!" << std::endl;
        }
    }


    void ProductController::filterScooterByMileage(bool lowerThan) {
        int mileage;
        std::cout << "Enter the mileage: ";
        std::cin >> mileage;

        bool printHeader = true;
        bool found = false;
        std::vector<domain::Scooter> scooters = repo.getScooters();

        if (lowerThan) {
            for (const auto &scooter: scooters) {
                if (scooter.getMileage() < mileage) {
                    if (printHeader) {
                        printDetailHeader();
                    }
                    printScooter(scooter);
                    printHeader = false;
                    found = true;
                }
            }
        } else {
            for (const auto &scooter: scooters) {
                if (scooter.getMileage() >= mileage) {
                    if (printHeader) {
                        printDetailHeader();
                    }
                    printScooter(scooter);
                    printHeader = false;
                    found = true;
                }
            }
        }
        if (!found) {
            std::cout << "No scooters found with a mileage greater than " << mileage << " miles!" << std::endl;
        }
    }

    void ProductController::listScooterByAge(bool ascending) {
        std::vector<domain::Scooter> scooters = repo.getScooters();
        std::string sortType;
        if (ascending) {
            sortType = "ascending";
            // Sort the scooters by age in ascending order
            std::sort(scooters.begin(), scooters.end(),
                      [](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return scooter1.getMileage() < scooter2.getMileage();
                      });
        } else {
            sortType = "descending";
            // Sort the scooters by age in ascending order
            std::sort(scooters.begin(), scooters.end(),
                      [](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return scooter1.getMileage() > scooter2.getMileage();
                      });
        }

        std::cout << std::endl << "\nList of scooters sorted by mileage (" << sortType << "):" << std::endl;
        ProductController::printDetailHeader();
        for (const auto &scooter: scooters) {
            printScooter(scooter);
        }
        sortScootersByID(); // sort back scooters by ID so they remain sorted by ID
    }

    void ProductController::sortScootersByID() {
        std::vector<domain::Scooter> scooters = repo.getScooters();

        // Sort the scooters by age in ascending order
        std::sort(scooters.begin(), scooters.end(),
                  [](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                      return scooter1.getID() < scooter2.getID();
                  });

        //printScooterByID();
    }


    void ProductController::reserveScooter() {
        printDetailHeader();
        for (auto &scooter: repo.getScooters()) {
            printScooter(scooter);
        }
        std::cout << "Here are the scooters listed.\nPlease enter an ID to reserve a scooter: ";
        std::string readID;
        std::cin >> readID;
        readID = readID.substr(0, 3);
        std::transform(readID.begin(), readID.end(), readID.begin(), [](unsigned char c) { return std::toupper(c); });
        std::cout << readID << std::endl;
        bool found = false;

        for (auto &scooter: repo.getScooters()) {
            if (readID == scooter.getID()) {
                if (scooter.getState() == domain::RESERVED) {
                    std::cout << "\nSorry, the scooter with the ID " << readID << " is reserved by someone else.\n";
                    return;
                }
                found = true;
                scooter.setState(domain::RESERVED);
                break;
            }
        }
        if (!found) {
            std::cout << "\nSorry, the scooter with the ID " << readID << " was not found.\n";
            return;
        }
        std::cout << "\nThe scooter with the ID " << readID << " was reserved.\n";
    }

    void ProductController::useScooter() {
        std::cout << "\nPlease enter the ID of the scooter you reserved to use it: ";
        std::string readID;
        std::cin >> readID;
        readID = readID.substr(0, 3);
        std::transform(readID.begin(), readID.end(), readID.begin(), [](unsigned char c) { return std::toupper(c); });
        std::cout << readID << std::endl;
        bool found = false;

        for (auto &scooter: repo.getScooters()) {
            if (readID == scooter.getID()) {
                if (scooter.getState() == domain::RESERVED) {
                    found = true;
                    scooter.setState(domain::INUSE);
                    std::cout << "\nYou can use the scooter with the ID " << readID << "\n";
                    break;
                } else {
                    std::cout << "\nSorry, the scooter with the ID " << readID << " is not reserved\n";
                }
            }
        }
        if (!found) {
            std::cout << "\nSorry, the scooter with the ID " << readID << " was not found.\n";
            return;
        }
        std::cout << "\nThe scooter with the ID " << readID << " was reserved.\n";

    }

    void ProductController::printDetailHeader() {
        std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Model" <<
                  std::setw(20) << "Commission Date" << std::setw(15) << "Mileage" <<
                  std::setw(30) << "Last Stand Place" << std::setw(15) << "State" << std::endl;
        for (int i = 0; i < 95; i++) std::cout << "-";
        std::cout << std::endl;
    }

    void ProductController::printScooter(const domain::Scooter &scooter) {

        const domain::Date date = scooter.getCommissionDate();
        const std::string dateToString = std::to_string(date.year) + "." + std::to_string(date.month) +
                                         "." + std::to_string(date.day);

        std::cout << std::left << std::setw(5) << scooter.getID()
                  << std::setw(30) << scooter.getModel()
                  << std::setw(20) << dateToString
                  << std::setw(15) << scooter.getMileage()
                  << std::setw(30) << scooter.getLastStandPlace()
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

            std::string expectedID, expectedModel, expectedLastStandPlace;
            domain::State expectedState = domain::PARKED;
            domain::Date expectedDate{};
            int expectedMileage;

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

            expectedID = id;
            expectedModel = model;
            expectedMileage = mileage;
            expectedLastStandPlace = lastStandPlace;

            domain::Date commissionDate{2023, 01, 01};
            if (isValidDate(year, month, day)) {
                commissionDate = {year, month, day};
                expectedDate = {year, month, day};
            }
            domain::State state = domain::PARKED;
            auto stateIt = stateMap.find(stateString);
            if (stateIt != stateMap.end()) {
                state = stateIt->second;
                expectedState = stateIt->second;
            }
            domain::Scooter scooter(id, model, commissionDate, mileage, lastStandPlace, state);

            assert(expectedID == scooter.getID());
            assert(expectedModel == scooter.getModel());
            assert(expectedLastStandPlace == scooter.getLastStandPlace());
            assert(expectedMileage == scooter.getMileage());
            assert(expectedDate.year == scooter.getCommissionDate().year);
            assert(expectedDate.month == scooter.getCommissionDate().month);
            assert(expectedDate.day == scooter.getCommissionDate().day);
            assert(expectedState == scooter.getState());

            this->repo.addScooter(scooter);
        }
        file.close();
    }


    void ProductController::saveDataToFile() const {
        std::ofstream file("../scootersDataSaved.txt");
        if (!file.is_open()) {
            std::cout << "Error opening file: scootersData.txt" << std::endl;
            return;
        }

        const std::unordered_map<domain::State, std::string> stateMap{
                {domain::PARKED,       "PARKED"},
                {domain::RESERVED,     "RESERVED"},
                {domain::INUSE,        "INUSE"},
                {domain::INWAIT,       "INWAIT"},
                {domain::OUTOFSERVICE, "OUTOFSERVICE"}
        };
        for (const auto &scooter: this->repo.getScooters()) {
            file << scooter.getID() << "," << scooter.getModel() << ","
                 << std::setfill('0') << scooter.getCommissionDate().year << ","
                 << std::setfill('0') << scooter.getCommissionDate().month << ","
                 << std::setfill('0') << scooter.getCommissionDate().day << ","
                 << scooter.getMileage() << ","
                 << scooter.getLastStandPlace() << ","
                 << stateMap.at(scooter.getState()) << std::endl;
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

    void ProductController::printScooterByID() {
        std::cout << "List of scooters sorted by ID:" << std::endl;
        ProductController::printDetailHeader();
        for (const auto &scooter: repo.getScooters()) {
            printScooter(scooter);
        }
    }

}