#include "Domain.h"

namespace domain
{
    Scooter::Scooter(std::string &id, std::string &model, Date &commision_date, int &mileage, std::string &lastStandPlace, State &sate)
    {
        this->id = id;
        this->model = model;
        this->commision_date = commision_date;
        this->mileage = mileage;
        this->lastStandPlace = lastStandPlace;
        this->state = state;
    }

    std::string Scooter::get_id()
    {
        return this->id;
    }
    std::string Scooter::get_model()
    {
        return this->model;
    }

};