#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../domain/Domain.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <cassert>
#include <memory>
#include <iomanip>


namespace repository {
    class Repository {
    private:
        std::vector<domain::Scooter> scooters;

    public:
        explicit Repository(const std::string &fileName_);

        void addScooter(const domain::Scooter &scooter);

        void deleteScooter(const domain::Scooter &scooter);

        void updateScooter(const domain::Scooter &scooter);

        std::vector<domain::Scooter> getScooters() const;

        void saveDataToFile(const std::string &fileName, const std::vector<domain::Scooter> &data);

        static std::vector<domain::Scooter> loadDataFromFile(const std::string &fileName);
    };

}
#endif
