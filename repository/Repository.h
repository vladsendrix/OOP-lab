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

        virtual void addScooter(const domain::Scooter &scooter) = 0;

        virtual void deleteScooter(const domain::Scooter &scooter) = 0;

        virtual void updateScooter(const domain::Scooter &scooter) = 0;

        virtual std::vector<domain::Scooter> getScooters() const = 0;

    };

    class RepositoryInMemory : public Repository {
    public:
        explicit RepositoryInMemory(std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>()) : Repository(
                scooters_) {}

        void addScooter(const domain::Scooter &scooter) override;

        void deleteScooter(const domain::Scooter &scooter) override;

        void updateScooter(const domain::Scooter &scooter) override;

        std::vector<domain::Scooter> getScooters() const override;
    };

    class RepositoryInFile : public Repository {
    private:
        std::string filename;
    public:
        explicit RepositoryInFile(std::string filename_, std::vector<domain::Scooter> scooters_ = std::vector<domain::Scooter>()) : Repository(
                scooters_), filename(std::move(filename_)) {}

        void addScooter(const domain::Scooter &scooter) override;

        void deleteScooter(const domain::Scooter &scooter) override;

        void updateScooter(const domain::Scooter &scooter) override;

        std::vector<domain::Scooter> getScooters() const override;
    };
};
#endif