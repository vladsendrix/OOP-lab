#pragma once
#include "../domain/Domain.h"
#include <vector>
#include <string>

namespace repository {
    class Repository {
        private:
            std::vector<domain::Scooter> scooters;
        public:
            explicit Repository(std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>());
            
            void addScooter(domain::Scooter scooter);
            void deleteScooter(domain::Scooter scooter);
            void editScooter(domain::Scooter scooter);
            std::vector<domain::Scooter> searchScooterByStandPlace(std::string standPlace);
            std::vector<domain::Scooter> filterScooterByAge(int age);
            std::vector<domain::Scooter> filterScooterByMileage(int mileage);
            std::vector<domain::Scooter> listScooterByAge();
    };
};