#include "Repository.h"

namespace repository {

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

    std::vector<domain::Scooter> Repository::getScooters() const {
        return scooters;
    }

    std::vector<domain::Scooter> Repository::loadDataFromFile(const std::string &fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening file:" <<fileName <<std::endl;
            return {};
        }
        const std::unordered_map<std::string, domain::State> stateMap{
                {"PARKED",       domain::State::PARKED},
                {"RESERVED",     domain::State::RESERVED},
                {"INUSE",        domain::State::INUSE},
                {"INWAIT",       domain::State::INWAIT},
                {"OUTOFSERVICE", domain::State::OUTOFSERVICE}
        };

        std::vector<domain::Scooter> scooters;

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

            domain::Date commissionDate{year, month, day};

            domain::State state = domain::State::PARKED;
            auto stateIt = stateMap.find(stateString);
            if (stateIt != stateMap.end()) {
                state = stateIt->second;
            }
            domain::Scooter scooter(id, model, commissionDate, mileage, lastStandPlace, state);
            scooters.push_back(scooter);
        }
        file.close();

        return scooters;
    }

    void Repository::saveDataToFile(const std::string &fileName, const std::vector<domain::Scooter> &data) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening file: scootersData.csv!" << std::endl;
            return;
        }

        const std::unordered_map<domain::State, std::string> stateMap{
                {domain::State::PARKED,       "PARKED"},
                {domain::State::RESERVED,     "RESERVED"},
                {domain::State::INUSE,        "INUSE"},
                {domain::State::INWAIT,       "INWAIT"},
                {domain::State::OUTOFSERVICE, "OUTOFSERVICE"}
        };
        for (const auto &scooter: data) {
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

    Repository::Repository() {
        scooters= loadDataFromFile("ScootersData.csv");
    }
}
