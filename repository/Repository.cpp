#include "Repository.h"
#include <fstream>
#include <algorithm>

namespace repository {
    Repository::Repository(std::vector<domain::Scooter> scooters_) {
        this->scooters = std::move(scooters_);
    }

    void Repository::addScooter(const domain::Scooter& scooter) {
        scooters.push_back(scooter);
        saveDataToFile();
    }

    void Repository::deleteScooter(const domain::Scooter& scooter) {
        auto it = std::find(scooters.begin(), scooters.end(), scooter);
        if (it != scooters.end()) {
            scooters.erase(it);
            saveDataToFile();
        }
    }

    void Repository::editScooter(const domain::Scooter& scooter) {
        for (auto& s : scooters) {
            if (s.getID() == scooter.getID()) {
                s.setModel(scooter.getModel());
                s.setCommissionDate(scooter.getCommissionDate());
                s.setMileage(scooter.getMileage());
                s.setLastStandPlace(scooter.getLastStandPlace());
                s.setState(scooter.getState());
                break;
            }
        }
        saveDataToFile();
    }

    std::vector<domain::Scooter> Repository::getScooters() const {
        return scooters;
    }

    void Repository::saveDataToFile() {
        std::ofstream file("scooters.txt");
        if (!file.is_open()) {
            std::cout << "Error opening file: scooters.txt" << std::endl;
            return;
        }

        for (const auto& scooter : scooters) {
            file << scooter.getID() << ","
                 << scooter.getModel() << ","
                 << scooter.getCommissionDate().year << ","
                 << scooter.getCommissionDate().month << ","
                 << scooter.getCommissionDate().day << ","
                 << scooter.getMileage() << ","
                 << scooter.getLastStandPlace() << ","
                 << scooter.getState() << "\n";
        }

        file.close();
    }

    void Repository::loadDataFromFile() {
        std::ifstream file("scooters.txt");
        if (!file.is_open()) {
            std::cout << "Error opening file: scooters.txt" << std::endl;
            return;
        }

        scooters.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, model, lastStandPlace;
            int year, month, day, mileage, state;

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
            ss >> state;

            domain::Date commissionDate{ year, month, day };
            domain::State scooterState = static_cast<domain::State>(state);
            domain::Scooter scooter(id, model, commissionDate, mileage, lastStandPlace, scooterState);
            scooters.push_back(scooter);
        }

        file.close();
    }
};
