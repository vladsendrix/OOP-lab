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
#include <iomanip>
#include <cassert>

namespace controller {
    class ProductController {
    private:
        repository::Repository repo;
    public:
        explicit ProductController(const repository::Repository &scooterRepo = repository::Repository());

        void addScooter();

        void deleteScooter();

        void editScooter();

        void searchScooterByStandPlace();

        void filterScooterByAge();

        void filterScooterByMileage();

        void listScooterByMileage();

        void sortScootersByID();

        void reserveScooter();

        void useScooter();

        static std::string generateID(const std::string &id_);

        void printScooter(const domain::Scooter &scooter);

        void loadDataFromFile();

        void saveDataToFile() const;

        void printDetailHeader();

        static bool isValidDate(int year, int month, int day);

    };
};

#endif