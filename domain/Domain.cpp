#include "Domain.h"

namespace domain {
    Scooter::Scooter(const std::string& id, const std::string& model, const Date& commissionDate,
                     int mileage, const std::string& lastStandPlace, const State& state) {
        this->id = id;
        this->model = model;
        this->commissionDate = commissionDate;
        this->mileage = mileage;
        this->lastStandPlace = lastStandPlace;
        this->state = state;
    }

    std::string Scooter::getID() const {
        return this->id;
    }

    std::string Scooter::getModel() const {
        return this->model;
    }

    Date Scooter::getCommissionDate() const {
        return this->commissionDate;
    }

    int Scooter::getMileage() const {
        return this->mileage;
    }

    std::string Scooter::getLastStandPlace() const {
        return this->lastStandPlace;
    }

    State Scooter::getState() const {
        return this->state;
    }

    // Setter methods

    void Scooter::setID(const std::string& id) {
        this->id = id;
    }

    void Scooter::setModel(const std::string& model) {
        this->model = model;
    }

    void Scooter::setCommissionDate(const Date& commissionDate) {
        this->commissionDate = commissionDate;
    }

    void Scooter::setMileage(int mileage) {
        this->mileage = mileage;
    }

    void Scooter::setLastStandPlace(const std::string& lastStandPlace) {
        this->lastStandPlace = lastStandPlace;
    }

    void Scooter::setState(const State& state) {
        this->state = state;
    }
}
