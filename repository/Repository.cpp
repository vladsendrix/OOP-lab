#include "Repository.h"

namespace repository {
    Repository::Repository(std::vector<domain::Scooter> scooters_) {
        this->scooters = std::move(scooters_);
    }

    void Repository::addScooter(const domain::Scooter &scooter) {
        scooters.push_back(scooter);
    }

    void Repository::deleteScooter(const domain::Scooter &scooter_) {
        auto it = std::remove_if(scooters.begin(), scooters.end(), [&scooter_](const domain::Scooter &scooter) {
            return scooter.getID() == scooter_.getID();
        });
        if (it != scooters.end()) {
            scooters.erase(it, scooters.end());
        }
    }

    void Repository::updateScooter(const domain::Scooter &scooter) {
        for (auto &s: scooters) {
            if (s.getID() == scooter.getID()) {
                s.setModel(scooter.getModel());
                s.setCommissionDate(scooter.getCommissionDate());
                s.setMileage(scooter.getMileage());
                s.setLastStandPlace(scooter.getLastStandPlace());
                s.setState(scooter.getState());
                break;
            }
        }
    }

    void RepositoryInFile::updateScooter(const domain::Scooter &scooter) {
        Repository::updateScooter(scooter);
        saveDataToFile();
    }

    std::vector<domain::Scooter> Repository::getScooters() const {
        return scooters;
    }

    void Repository::loadDataFromFile() {
        std::ifstream file("scootersData.txt");
        if (!file.is_open()) {
            std::cout << "Error opening file: scooters.txt" << std::endl;
            return;
        }
        const std::unordered_map<std::string, domain::State> stateMap{
                {"PARKED",       domain::State::PARKED},
                {"RESERVED",     domain::State::RESERVED},
                {"INUSE",        domain::State::INUSE},
                {"INWAIT",       domain::State::INWAIT},
                {"OUTOFSERVICE", domain::State::OUTOFSERVICE}
        };

        assert(getScooters().empty());

        int repoSize = 0;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, model, lastStandPlace, stateString;
            int year, month, day, mileage;

            std::string expectedID, expectedModel, expectedLastStandPlace;
            domain::State expectedState = domain::State::PARKED;
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

            domain::State state = domain::State::PARKED;
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

            addScooter(scooter);
            repoSize++;
        }
        file.close();
    }


    void RepositoryInFile::saveDataToFile() const {
        std::ofstream file("scootersDataSaved.txt");
        if (!file.is_open()) {
            std::cout << "Error opening file: scootersData.txt" << std::endl;
            return;
        }

        const std::unordered_map<domain::State, std::string> stateMap{
                {domain::State::PARKED,       "PARKED"},
                {domain::State::RESERVED,     "RESERVED"},
                {domain::State::INUSE,        "INUSE"},
                {domain::State::INWAIT,       "INWAIT"},
                {domain::State::OUTOFSERVICE, "OUTOFSERVICE"}
        };
        for (const auto &scooter: getScooters()) {
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
};