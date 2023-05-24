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

    public:
        virtual void addScooter(const domain::Scooter &scooter, const std::string &dbName) = 0;

        virtual void deleteScooter(const domain::Scooter &scooter, const std::string &dbName) = 0;

        virtual void updateScooter(const domain::Scooter &scooter) = 0;

        virtual std::vector<domain::Scooter> getScooters(const std::string &dbName) const = 0;

    };

    class RepositoryInMemory : public Repository {
    private:
        std::vector<domain::Scooter> scooters;
        std::vector<domain::Scooter> userScooters;
    public:
        RepositoryInMemory();

        void addScooter(const domain::Scooter &scooter, const std::string &dbName) override;

        void deleteScooter(const domain::Scooter &scooter, const std::string &dbName) override;

        void updateScooter(const domain::Scooter &scooter) override;

        std::vector<domain::Scooter> getScooters(const std::string &dbName) const override;

    };

    class RepositoryInFile : public Repository {
    private:
        std::string adminFile;
        std::string userFile;
    public:
        explicit RepositoryInFile();

        void addScooter(const domain::Scooter &scooter, const std::string &dbName) override;

        void deleteScooter(const domain::Scooter &scooter, const std::string &dbName) override;

        void updateScooter(const domain::Scooter &scooter) override;

        std::vector<domain::Scooter> getScooters(const std::string &dbName) const override;

        static std::vector<domain::Scooter> loadDataFromFile(const std::string &fileName);

        static void saveDataToFile(const std::string &fileName, const std::vector<domain::Scooter> &data);
    };
}
#endif
