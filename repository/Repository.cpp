#include "Repository.h"

namespace repository {
    Repository::Repository(std::vector<domain::Scooter> scooters_)
    {
        this->scooters=scooters_;
    }

    void Repository::addScooter(domain::Scooter scooter)
    {
         this->scooters.push_back(scooter);
    }
    void Repository::deleteScooter(domain::Scooter scooter)
    {
        
    }

    void Repository::editScooter(domain::Scooter scooter)
    {

    }

    std::vector<domain::Scooter> Repository::searchScooterByStandPlace(std::string standPlace)
    {

        return std::vector<domain::Scooter>();
    }

    std::vector<domain::Scooter> Repository::filterScooterByAge(int age)
    {

        return std::vector<domain::Scooter>();
    }

    std::vector<domain::Scooter> Repository::filterScooterByMileage(int mileage)
    {
        return std::vector<domain::Scooter>();
    }

    std::vector<domain::Scooter> Repository::listScooterByAge()
    {
        return std::vector<domain::Scooter>();
    }
};