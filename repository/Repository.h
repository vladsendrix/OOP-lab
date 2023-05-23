#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../domain/Domain.h"
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
    protected:
        std::vector<domain::Scooter> scooters;
    public:
        explicit Repository(std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>());

        virtual void addScooter(const domain::Scooter &scooter);

        virtual void deleteScooter(const domain::Scooter &scooter);

        virtual void updateScooter(const domain::Scooter &scooter) = 0;

        virtual std::vector<domain::Scooter> getScooters() const;

        virtual void loadDataFromFile();

    };

    class RepositoryInMemory : public Repository {
    public:
        explicit RepositoryInMemory(std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>())
                : Repository(
                scooters_) {}
    };

    class RepositoryInFile : public Repository {
    private:
        std::string filename;
    public:
        explicit RepositoryInFile(std::string filename_,
                                  std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>()) : Repository(
                scooters_), filename(std::move(filename_)) {}

        void updateScooter(const domain::Scooter &scooter) override;

        void saveDataToFile() const;
    };
};
#endif
