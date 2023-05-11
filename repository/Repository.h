
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "../domain/Domain.h"
#include <vector>
#include <string>

namespace repository {
    class Repository {
    private:
        std::vector<domain::Scooter> scooters;
    public:
        explicit Repository(std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>());

        void addScooter(const domain::Scooter& scooter);

        void deleteScooter(const domain::Scooter& scooter);

        void editScooter(const domain::Scooter& scooter);

        static std::vector<domain::Scooter> searchScooterByStandPlace(const std::string& standPlace);

        static std::vector<domain::Scooter> filterScooterByAge(int age);

        std::vector<domain::Scooter> filterScooterByMileage(int mileage);

        std::vector<domain::Scooter> listScooterByAge();
    };
};
#endif