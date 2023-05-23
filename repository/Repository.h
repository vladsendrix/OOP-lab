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
        virtual void addScooter(const domain::Scooter &scooter) = 0;

        virtual void deleteScooter(const domain::Scooter &scooter) = 0;

        virtual void updateScooter(const domain::Scooter &scooter) = 0;

        virtual std::vector<domain::Scooter> getScooters() const = 0;

        //virtual void loadDataFromFile() = 0;

        //virtual void saveDataToFile() =0;

    };

    class RepositoryInMemory : public Repository {
    private:
        std::vector<domain::Scooter> scooters;
    public:
        RepositoryInMemory();

        void addScooter(const domain::Scooter& scooter) override;

        void deleteScooter(const domain::Scooter& scooter) override;

        void updateScooter(const domain::Scooter& scooter) override;

        std::vector<domain::Scooter> getScooters() const override ;


    };

    class RepositoryInFile : public Repository {
    private:
        std::string filename;
    public:
        explicit RepositoryInFile();

        void addScooter(const domain::Scooter& scooter) override;

        void deleteScooter(const domain::Scooter& scooter) override;

        void updateScooter(const domain::Scooter& scooter) override ;

        std::vector<domain::Scooter> getScooters() const override;

        static std::vector<domain::Scooter> loadDataFromFile(const std::string &fileName) ;

        static void saveDataToFile(const std::string &fileName,const std::vector<domain::Scooter> &data) ;
    };
}
#endif
