#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../repository/Repository.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <cassert>

namespace controller {
    class ProductController {
    private:
        std::unique_ptr<repository::Repository> repo;
    public:
        explicit ProductController(
                std::unique_ptr<repository::Repository> scooterRepo = std::make_unique<repository::Repository>());

        domain::Scooter addScooter(const std::string &model, const std::string &date, const int &mileage,
                        const std::string &lastStandPlace, const int &stateNr);

        int position(const std::string &id_);

        bool exists(const int &index);

        bool deleteScooter(const int &index) const;

        domain::Scooter editScooter(const int &index, const std::string &date, const int &mileage,
                         const std::string &lastStandPlace,const int &stateNr) const;

        std::vector<domain::Scooter> searchScooterByStandPlace(std::string &standPlace);

        std::vector<domain::Scooter> filterScooterByAge(bool condition);

        void filterScooterByMileage(bool condition);

        void listScooterByAge(bool condition);

        void reserveScooter();

        void useScooter();

        void parkScooter();


        // other helpful methods

        static std::string readScooterID();

        void sortScootersByID();

        static void printDetailHeader();

        static void printScooter(const domain::Scooter &scooter);

        void printScooterByID();

        void loadDataFromFile();

        void saveDataToFile() const;

        std::string autoGenerateID();

        static bool isValidDate(const int &year, const int &month, const int &day) ;

    };
}

#endif