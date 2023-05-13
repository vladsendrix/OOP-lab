#include "Domain.h"

namespace domain {
    Scooter::Scooter(const std::string &id, const std::string &model, const Date &commissionDate,
                     int mileage, const std::string &lastStandPlace, const State &state) {
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

    void Scooter::setID(const std::string &id_) {
        this->id = id_;
    }


    void Scooter::setModel(const std::string &model_) {
        this->model = model_;
    }

    void Scooter::setCommissionDate(const Date &commissionDate_) {
        this->commissionDate = commissionDate_;
    }

    void Scooter::setMileage(int mileage_) {
        this->mileage = mileage_;
    }

    void Scooter::setLastStandPlace(const std::string &lastStandPlace_) {
        this->lastStandPlace = lastStandPlace_;
    }

    void Scooter::setState(const State &state_) {
        this->state = state_;
    }
}
