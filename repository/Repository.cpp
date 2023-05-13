#include "Repository.h"
#include <fstream>
#include <algorithm>

namespace repository {
    Repository::Repository(std::vector<domain::Scooter> scooters_) {
        this->scooters = std::move(scooters_);
    }

    void Repository::addScooter(const domain::Scooter &scooter) {
        scooters.push_back(scooter);
        saveDataToFile();
    }

    void Repository::deleteScooter(const domain::Scooter &scooter_) {
        auto it = std::remove_if(scooters.begin(), scooters.end(), [&scooter_](const domain::Scooter &scooter) {
            return scooter.getID() == scooter_.getID();
        });
        if (it != scooters.end()) {
            scooters.erase(it, scooters.end());
            saveDataToFile();
        }
    }

    void Repository::editScooter(const domain::Scooter &scooter) {
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

        for (const auto &scooter: scooters) {
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


};
