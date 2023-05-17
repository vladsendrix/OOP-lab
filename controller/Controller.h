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
#include <iomanip>
#include <cassert>

namespace controller {
    class ProductController {
    private:
        std::unique_ptr<repository::Repository> repo;
    public:
        explicit ProductController(
                std::unique_ptr<repository::Repository> scooterRepo = std::make_unique<repository::Repository>());

        void addScooter();

        void deleteScooter();

        void editScooter();

        void searchScooterByStandPlace();

        void filterScooterByAge(bool condition);

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

        static bool isValidDate(int year, int month, int day);

    };
}

#endif