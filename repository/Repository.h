
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../domain/Domain.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace repository {
    class Repository {
    private:
        std::vector<domain::Scooter> scooters;
    public:
        explicit Repository(std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>());

        void addScooter(const domain::Scooter &scooter);

        void deleteScooter(const domain::Scooter &scooter);

        void updateScooter(const domain::Scooter &scooter);

        std::vector<domain::Scooter> getScooters() const;

    };
};
#endif