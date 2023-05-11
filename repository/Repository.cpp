#include "Repository.h"
#include <utility>

namespace repository {
    Repository::Repository(std::vector<domain::Scooter> scooters_) {
        this->scooters = std::move(scooters_);
    }

    void Repository::addScooter(const domain::Scooter& scooter) {
        this->scooters.push_back(scooter);
    }

    void Repository::deleteScooter(const domain::Scooter& scooter) {

    }

    void Repository::editScooter(const domain::Scooter& scooter) {

    }

    std::vector<domain::Scooter> Repository::searchScooterByStandPlace(const std::string& standPlace) {

        return {};
    }

    std::vector<domain::Scooter> Repository::filterScooterByAge(int age) {

        return {};
    }

    std::vector<domain::Scooter> Repository::filterScooterByMileage(int mileage) {
        return std::vector<domain::Scooter>();
    }

    std::vector<domain::Scooter> Repository::listScooterByAge() {
        return std::vector<domain::Scooter>();
    }
};