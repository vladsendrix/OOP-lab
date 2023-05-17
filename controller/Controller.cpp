#include "Controller.h"

namespace controller {


    ProductController::ProductController(std::unique_ptr<repository::Repository> scooterRepo_) {
        this->repo = std::move(scooterRepo_);
    }


    void ProductController::addScooter() {

        std::string id, model, lastStandPlace, date;
        domain::Date commissionDate{2023, 01, 01};
        domain::State state;
        int mileage, stateNr;

        id = autoGenerateID();

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

        std::string expectedID = id, expectedModel = model, expectedLastStandPlace = lastStandPlace;
        domain::Date expectedDate = commissionDate;
        domain::State expectedState = state;
        int expectedMileage = mileage;

        domain::Scooter newScooter = domain::Scooter(id, model, commissionDate, mileage, lastStandPlace, state);
        assert(expectedID == newScooter.getID());
        assert(expectedModel == newScooter.getModel());
        assert(expectedLastStandPlace == newScooter.getLastStandPlace());
        assert(expectedMileage == newScooter.getMileage());
        assert(expectedDate.year == newScooter.getCommissionDate().year);
        assert(expectedDate.month == newScooter.getCommissionDate().month);
        assert(expectedDate.day == newScooter.getCommissionDate().day);
        assert(expectedState == newScooter.getState());

        repo->addScooter(newScooter);

        printDetailHeader();
        printScooter(newScooter);

        sortScootersByID();
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
        std::vector<domain::Scooter> scooters = repo->getScooters();
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
            repo->deleteScooter(scooterToDelete);
            saveDataToFile();
            std::cout << "Scooter deleted successfully!" << std::endl;
        }
    }

    void ProductController::editScooter() {
        std::string scooterID;
        std::cout << std::endl << "Enter the ID of the scooter to edit: ";
        std::cin >> scooterID;

        scooterID = scooterID.substr(0, 3);
        std::transform(scooterID.begin(), scooterID.end(), scooterID.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        int index = 0;


        for (const auto &scooter: repo->getScooters()) {
            if (scooter.getID() == scooterID) {
                break;
            }
            index++;
        }
        if (index == repo->getScooters().size()) {
            std::cout << "Scooter not found!" << std::endl;
        } else {

            std::string model, lastStandPlace, date;
            domain::Date commissionDate{2023, 01, 01};
            domain::State state;
            int stateNr, mileage;

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

            domain::Scooter updatedScooter = domain::Scooter(
                    repo->getScooters().at(index).getID(),
                    repo->getScooters().at(index).getModel(),
                    commissionDate, mileage, lastStandPlace, state);
            repo->updateScooter(updatedScooter);
            printDetailHeader();
            printScooter(repo->getScooters().at(index));

            saveDataToFile();
            std::cout << "Scooter edited successfully!" << std::endl;
        }
    }

    void ProductController::searchScooterByStandPlace() {
        std::string standPlace;
        std::cout << "Enter the stand place (or leave empty to show all scooters): ";
        std::cin.ignore(); // Ignore any previous newline character
        std::getline(std::cin, standPlace);

        std::transform(standPlace.begin(), standPlace.end(), standPlace.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        std::vector<domain::Scooter> scooters = repo->getScooters();
        bool found = false;
        for (const auto &scooter: scooters) {
            std::string lastStandPlace = scooter.getLastStandPlace();
            std::transform(lastStandPlace.begin(), lastStandPlace.end(), lastStandPlace.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (standPlace.empty() || lastStandPlace.find(standPlace) != std::string::npos) {
                printScooter(scooter);
                found = true;
            }
        }
        if (!found) {
            std::cout << "No scooters found with the specified stand place!" << std::endl;
        }
    }


    void ProductController::filterScooterByAge(bool lowerThan) {
        int age;
        std::string sortType;
        std::cout << "Enter the age: ";
        std::cin >> age;
        age = 2022 - age;
        bool printHeader = true;
        bool found = false;
        std::vector<domain::Scooter> scooters = repo->getScooters();

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
        std::string condition = "higher than -inclusive ";
        if (lowerThan) condition = "lower than ";
        bool printHeader = true;
        bool found = false;
        std::vector<domain::Scooter> scooters = repo->getScooters();

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
            std::cout << "No scooters found with a mileage " << condition << mileage << " miles!" << std::endl;
        }
    }

    void ProductController::listScooterByAge(bool ascending) {
        std::vector<domain::Scooter> scooters = repo->getScooters();
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


    void ProductController::reserveScooter() {
        printDetailHeader();
        for (auto &scooter: repo->getScooters()) {
            printScooter(scooter);
        }
        std::cout << "Here are the scooters listed.\nPlease enter an ID to reserve a scooter: ";
        std::string readID = readScooterID();
        bool found = false;
        int index = 0;
        for (auto &scooter: repo->getScooters()) {
            if (readID == scooter.getID()) {
                if (scooter.getState() == domain::INWAIT || scooter.getState() == domain::PARKED) {
                    found = true;
                    break;
                }
                std::cout << "\nSorry, the scooter with the ID " << readID << " is not parked or in wait.\n";
                return;
            }
            index++;
        }
        if (!found) {
            std::cout << "\nSorry, the scooter with the ID " << readID << " was not found.\n";
            return;
        }
        domain::Scooter reservedScooter = repo->getScooters().at(index);
        reservedScooter.setState(domain::RESERVED);
        repo->updateScooter(reservedScooter);

        printDetailHeader();
        printScooter(reservedScooter);

        std::cout << "\nThe scooter with the ID " << readID << " was reserved.\n";
    }

    void ProductController::useScooter() {
        std::cout << "\nPlease enter the ID of the scooter you reserved to use it: ";
        std::string readID = readScooterID();
        bool found = false;
        int index = 0;

        for (auto &scooter: repo->getScooters()) {
            if (readID == scooter.getID()) {
                if (scooter.getState() == domain::RESERVED) {
                    found = true;
                    break;
                }
                std::cout << "\nSorry, the scooter with the ID " << readID << " is not reserved\n";
                return;
            }
            index++;
        }

        if (!found) {
            std::cout << "\nSorry, the scooter with the ID " << readID << " was not found.\n";
            return;
        }

        domain::Scooter useScooter = repo->getScooters().at(index);
        useScooter.setState(domain::INUSE);
        repo->updateScooter(useScooter);

        printDetailHeader();
        printScooter(useScooter);

        std::cout << "\nYou can use the scooter with the ID " << readID << "\n";
    }


    void ProductController::parkScooter() {
        std::cout << "\nPlease enter the ID of the scooter you are using to stop useing it (to park it): ";
        std::string readID = readScooterID();
        bool found = false;
        int index = 0;

        for (auto &scooter: repo->getScooters()) {
            if (readID == scooter.getID()) {
                if (scooter.getState() == domain::INUSE) {
                    found = true;
                    break;
                }

                std::cout << "\nSorry, the scooter with the ID " << readID << " is not in use\n";
                return;
            }
            index++;
        }

        if (!found) {
            std::cout << "\nSorry, the scooter with the ID " << readID << " was not found.\n";
            return;
        }

        std::string location;
        std::cout << "Please enter your current location: ";
        std::getline(std::cin, location);


        domain::Scooter useScooter = repo->getScooters().at(index);
        useScooter.setState(domain::PARKED);
        useScooter.setLastStandPlace(location);
        useScooter.setMileage(useScooter.getMileage() + 20);
        repo->updateScooter(useScooter);
        std::cout << "\nYou can use the scooter with the ID " << readID << "\n";
    }

    // other helpful methods

    std::string ProductController::readScooterID() {
        std::string readID;
        std::cin >> readID;
        readID = readID.substr(0, 3);
        std::transform(readID.begin(), readID.end(), readID.begin(), [](unsigned char c) { return std::toupper(c); });
        return readID;
    }

    void ProductController::sortScootersByID() {
        std::vector<domain::Scooter> scooters = repo->getScooters();

        // Sort the scooters by age in ascending order
        std::sort(scooters.begin(), scooters.end(),
                  [](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                      return scooter1.getID() < scooter2.getID();
                  });

        //printScooterByID();
    }


    void ProductController::printDetailHeader() {
        std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Model" <<
                  std::setw(20) << "Commission Date" << std::setw(15) << "Mileage" <<
                  std::setw(30) << "Last Stand Place" << std::setw(15) << "State" << std::endl;
        for (int i = 0; i < 110; i++) std::cout << "-";
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


    void ProductController::printScooterByID() {
        std::cout << "List of scooters sorted by ID:" << std::endl;
        ProductController::printDetailHeader();
        for (const auto &scooter: repo->getScooters()) {
            printScooter(scooter);
        }
    }

    void ProductController::loadDataFromFile() {
        std::ifstream file("scootersData.txt");
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

        assert(this->repo->getScooters().empty());

        int repoSize = 0;

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

            this->repo->addScooter(scooter);
            repoSize++;
            assert(this->repo->getScooters().size() == repoSize);
        }
        file.close();
    }


    void ProductController::saveDataToFile() const {
        std::ofstream file("scootersDataSaved.txt");
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
        for (const auto &scooter: this->repo->getScooters()) {
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


    std::string ProductController::autoGenerateID() {
        std::string id = "AAA";

        if (!repo->getScooters().empty()) {
            std::set<std::string> existingIDs;

            for (const auto &scooter: repo->getScooters()) {
                existingIDs.insert(scooter.getID());
            }
            while (existingIDs.find(id) != existingIDs.end()) {
                if (id[2] == 'Z') {
                    id[2] = 'A';
                    if (id[1] == 'z') {
                        id[1] = 'A';

                        if (id[0] == 'Z') {
                            return "";
                        } else {
                            id[0]++;
                        }
                    } else {
                        id[1]++;
                    }
                } else {
                    id[2]++;
                }
            }
        }
        return id;
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

}