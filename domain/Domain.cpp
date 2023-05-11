#include "Domain.h"

namespace domain {
    Scooter::Scooter(std::string &id, std::string &model, Date &commision_date, int &mileage,
                     std::string &lastStandPlace, State &state) {
        this->id = id;
        this->model = model;
        this->commision_date = commision_date;
        this->mileage = mileage;
        this->lastStandPlace = lastStandPlace;
        this->state = state;
    }

    std::string Scooter::getID() {
        return this->id;
    }

    std::string Scooter::getModel() {
        return this->model;
    }

    Date Scooter::ComissionDate() {
        return this->commision_date;
    }

    int Scooter::getMileage() {
        return this->mileage;
    }

    std::string Scooter::getLastStandPlace() {
        return this->lastStandPlace;
    }

    State Scooter::getState() {
        return this->state;
    }

    // setter methods

    void Scooter::setID(std::string& id) {
        return this->id;
    }

    void Scooter::setModel() {
        return this->model;
    }

    void Scooter::setComissionDate() {
        return this->commision_date;
    }

    void Scooter::setMileage(int& mileage) {
        return this->mileage;
    }

    void Scooter::setLastStandPlace() {
        return this->lastStandPlace;
    }

    void Scooter::setState(State& state) {
        return this->state;
    }
};