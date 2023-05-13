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

        void listScooterByAge();

        void reserveScooter();

        void useScooter();

        static std::string generateID(const std::string &id_);

        static void printScooter(const domain::Scooter &scooter);

        void loadDataFromFile();

        static void printDetailHeader();

        static bool isValidDate(int year, int month, int day);

    };
};

#endif