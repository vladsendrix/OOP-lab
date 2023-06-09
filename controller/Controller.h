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
#include <memory>
#include <iomanip>

namespace controller {
    class ProductController {
    private:
        std::shared_ptr<repository::Repository> repo;  // Update to shared_ptr
        std::string adminFile;
        std::string userFile;

    public:

        void setUserFile(const std::string &fileName);

        explicit ProductController(std::shared_ptr<repository::Repository> repo);  // Update parameter type


        domain::Scooter addScooter(const std::string &model, const std::string &date, const int &mileage,
                                   const std::string &lastStandPlace, const int &stateNr);

        int position(const std::string &id_);

        bool exists(const int &index) const;

        bool deleteScooter(const int &index) const;

        domain::Scooter editScooter(const int &index, const std::string &date, const int &mileage,
                                    const std::string &lastStandPlace, const int &stateNr) const;

        std::vector<domain::Scooter> searchScooterByStandPlace(std::string &standPlace);

        std::vector<domain::Scooter> filterScooterByAge(bool condition, const int &age);

        std::vector<domain::Scooter> filterScooterByMileage(bool lowerThan, const int &mileage);




        std::vector<domain::Scooter> sortScooters(bool condition, const std::string& sortBy);

        std::vector<domain::Scooter> userReservedScooters();

        bool reserveScooter(const int &index);

        bool useScooter(const int &index_);

        bool parkScooter(const int &index, const std::string &location);




        // other helpful methods
        bool is_inwait_parked(const int &index);

        bool is_reserved(const int &index);

        bool is_inuse(const int &index_);

        static std::string transformID(std::string id);



        std::string autoGenerateID();

        static bool isValidDate(const int &year, const int &month, const int &day);

    };
}

#endif