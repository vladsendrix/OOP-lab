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

    std::string Scooter::get_id() {
        return this->id;
    }

    std::string Scooter::get_model() {
        return this->model;
    }

    Date Scooter::get_commision_date() {
        return this->commision_date;
    }

    int Scooter::get_mileage() {
        return this->mileage;
    }

    std::string Scooter::get_lastStandPlace() {
        return this->lastStandPlace;
    }

    State Scooter::get_state() {
        return this->state;
    }

    // setter methods

    std::string Scooter::set_id() {
        return this->id;
    }

    std::string Scooter::set_model() {
        return this->model;
    }

    Date Scooter::set_commision_date() {
        return this->commision_date;
    }

    int Scooter::set_mileage() {
        return this->mileage;
    }

    std::string Scooter::set_lastStandPlace() {
        return this->lastStandPlace;
    }

    State Scooter::set_state() {
        return this->state;
    }
};