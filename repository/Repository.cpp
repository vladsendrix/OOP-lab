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

    std::vector<domain::Scooter> Repository::getScooters() const {
        return scooters;
    }
};