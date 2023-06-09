#include "Controller.h"

namespace controller {


    ProductController::ProductController(std::shared_ptr<repository::Repository> repo_)
            : repo(std::move(repo_)) {
        adminFile="ScootersData.csv";
        //userFile="UserData.csv";
    }

    void ProductController::setUserFile(const std::string &fileName) {
        userFile=fileName;
    }


    domain::Scooter
    ProductController::addScooter(const std::string &model, const std::string &date, const int &mileage_,
                                  const std::string &lastStandPlace, const int &stateNr_) {
        auto id = autoGenerateID();

        domain::Date commissionDate{2023, 01, 01};
        domain::State state;
        int mileage = mileage_;
        int year = std::stoi(date.substr(0, 4)),
                month = std::stoi(date.substr(5, 2)),
                day = std::stoi(date.substr(8, 2));

        if (!date.empty() && isValidDate(year, month, day)) {
            commissionDate.year = year;
            commissionDate.month = month;
            commissionDate.day = day;
        }

        switch (stateNr_) {
            case 2:
                state = domain::RESERVED;
                break;
            case 3:
                state = domain::INUSE;
                break;
            case 4:
                state = domain::INWAIT;
                break;
            case 5:
                state = domain::OUTOFSERVICE;
                break;
            default:
                state = domain::PARKED;
        }

        domain::Scooter newScooter = domain::Scooter(id, model, commissionDate, mileage, lastStandPlace, state);
        repo->addScooter(newScooter,adminFile);
        sortScooters(true,"ID");
        return newScooter;
    }

    int ProductController::position(const std::string &id_) {
        std::string id = transformID(id_);
        int index = 0;
        std::vector<domain::Scooter> scooters = repo->getScooters(adminFile);
        for (const auto &scooter: scooters) {
            if (scooter.getID() == id) {
                return index;
            }
            index++;
        }
        return index;
    }

    bool ProductController::exists(const int &index) const {
        return 0 <= index && index < repo->getScooters(adminFile).size();
    }

    bool ProductController::deleteScooter(const int &index) const {
        std::vector<domain::Scooter> scooters = repo->getScooters(adminFile);
        if (!exists(index)) {
            return false;
        }
        domain::Scooter scooterToDelete = scooters.at(index);
        repo->deleteScooter(scooterToDelete,adminFile);
        return true;
    }

    domain::Scooter ProductController::editScooter(const int &index, const std::string &date, const int &mileage,
                                                   const std::string &lastStandPlace, const int &stateNr) const {

        domain::Date commissionDate{2023, 01, 01};
        domain::State state;

        int year = std::stoi(date.substr(0, 4)),
                month = std::stoi(date.substr(5, 2)),
                day = std::stoi(date.substr(8, 2));

        if (!date.empty() && isValidDate(year, month, day)) {
            commissionDate.year = year;
            commissionDate.month = month;
            commissionDate.day = day;
        }

        switch (stateNr) {
            case 2:
                state = domain::RESERVED;
                break;
            case 3:
                state = domain::INUSE;
                break;
            case 4:
                state = domain::INWAIT;
                break;
            case 5:
                state = domain::OUTOFSERVICE;
                break;
            default:
                state = domain::PARKED;
        }
        std::cout << std::endl;

        domain::Scooter updatedScooter = domain::Scooter(
                repo->getScooters(adminFile).at(index).getID(),
                repo->getScooters(adminFile).at(index).getModel(),
                commissionDate, mileage, lastStandPlace, state);

        repo->updateScooter(updatedScooter,adminFile);
        return updatedScooter;
    }

    std::vector<domain::Scooter> ProductController::searchScooterByStandPlace(std::string &standPlace) {

        std::transform(standPlace.begin(), standPlace.end(), standPlace.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        std::vector<domain::Scooter> result, scooters;
        scooters = repo->getScooters(adminFile);

        for (const auto &scooter: scooters) {
            std::string lastStandPlace = scooter.getLastStandPlace();
            std::transform(lastStandPlace.begin(), lastStandPlace.end(), lastStandPlace.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (standPlace.empty() || lastStandPlace.find(standPlace) != std::string::npos) {
                result.push_back(scooter);
            }
        }
        return result;
    }

    std::vector<domain::Scooter> ProductController::filterScooterByAge(bool lowerThan, const int &age) {

        std::vector<domain::Scooter> result, scooters;
        scooters = repo->getScooters(adminFile);

        if (lowerThan) {
            for (const auto &scooter: scooters)
                if (scooter.getCommissionDate().year > 2022 - age)
                    result.push_back(scooter);
            return result;
        }

        for (const auto &scooter: scooters)
            if (scooter.getCommissionDate().year <= 2022 - age)
                result.push_back(scooter);
        return result;
    }


    std::vector<domain::Scooter> ProductController::filterScooterByMileage(bool lowerThan, const int &mileage) {

        std::vector<domain::Scooter> result, scooters = repo->getScooters(adminFile);
        if (lowerThan) {
            for (const auto &scooter: scooters)
                if (scooter.getMileage() < mileage)
                    result.push_back(scooter);
            return result;
        }
        for (const auto &scooter: scooters)
            if (scooter.getMileage() >= mileage)
                result.push_back(scooter);
        return result;
    }


    bool ProductController::is_inwait_parked(const int &index_) {
        int index = index_;
        if (!exists(index)) return false;
        const domain::Scooter scooter = repo->getScooters(adminFile).at(index);
        if (scooter.getState() == domain::State::INWAIT || scooter.getState() == domain::State::PARKED) {
            return true;
        }
        return false;
    }


    bool ProductController::is_reserved(const int &index_) {
        int index = index_;
        if (!exists(index)) return false;
        const domain::Scooter scooter = repo->getScooters(adminFile).at(index);
        if (scooter.getState() == domain::State::RESERVED) {
            return true;
        }
        return false;
    }

    bool ProductController::is_inuse(const int &index_) {
        int index = index_;
        if (!exists(index)) return false;
        const domain::Scooter scooter = repo->getScooters(adminFile).at(index);
        if (scooter.getState() == domain::State::INUSE) {
            return true;
        }
        return false;
    }

    bool ProductController::reserveScooter(const int &index_) {
        int index = index_;
        if (is_inwait_parked(index)) {
            domain::Scooter reservedScooter = repo->getScooters(adminFile).at(index);
            reservedScooter.setState(domain::State::RESERVED);
            repo->updateScooter(reservedScooter,adminFile);
            repo->addScooter(reservedScooter,userFile);
            return true;
        }
        return false;
    }


    bool ProductController::useScooter(const int &index_) {
        int index = index_;
        if (is_reserved(index)) {
            domain::Scooter useScooter = repo->getScooters(adminFile).at(index);
            useScooter.setState(domain::State::INUSE);
            repo->updateScooter(useScooter,adminFile);
            return true;
        }
        return false;
    }

    bool ProductController::parkScooter(const int &index_, const std::string &location_) {
        int index = index_;
        const std::string &location = location_;
        if (is_inuse(index)) {
            domain::Scooter useScooter = repo->getScooters(adminFile).at(index);
            useScooter.setState(domain::State::PARKED);
            useScooter.setLastStandPlace(location);
            useScooter.setMileage(useScooter.getMileage() + 20);
            repo->updateScooter(useScooter,adminFile);
            return true;
        }
        return false;
    }


    // all the sortings
    std::vector<domain::Scooter> ProductController::sortScooters(bool ascending, const std::string &sortBy) {
        std::vector<domain::Scooter> scooters = repo->getScooters(adminFile);

        if (sortBy == "ID") {
            std::sort(scooters.begin(), scooters.end(),
                      [ascending](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return ascending ? scooter1.getID() < scooter2.getID() : scooter1.getID() > scooter2.getID();
                      });
        } else if (sortBy == "Model") {
            std::sort(scooters.begin(), scooters.end(),
                      [ascending](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return ascending ? scooter1.getModel() < scooter2.getModel() : scooter1.getModel() >
                                                                                         scooter2.getModel();
                      });
        } else if (sortBy == "Age") {
            std::sort(scooters.begin(), scooters.end(),
                      [ascending](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return ascending ? scooter1.getCommissionDate() < scooter2.getCommissionDate() :
                                 scooter2.getCommissionDate() < scooter1.getCommissionDate();
                      });
        } else if (sortBy == "Mileage") {
            std::sort(scooters.begin(), scooters.end(),
                      [ascending](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return ascending ? scooter1.getMileage() < scooter2.getMileage() : scooter1.getMileage() >
                                                                                             scooter2.getMileage();
                      });
        } else if (sortBy == "LastStandPlace") {
            std::sort(scooters.begin(), scooters.end(),
                      [ascending](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return ascending ? scooter1.getLastStandPlace() < scooter2.getLastStandPlace() :
                                 scooter1.getLastStandPlace() > scooter2.getLastStandPlace();
                      });
        } else if (sortBy == "State") {
            std::sort(scooters.begin(), scooters.end(),
                      [ascending](const domain::Scooter &scooter1, const domain::Scooter &scooter2) {
                          return ascending ? scooter1.getState() < scooter2.getState() : scooter1.getState() >
                                                                                         scooter2.getState();
                      });
        }
        return scooters;
    }

    // END all sortings

    // other helpful methods

    std::string ProductController::transformID(std::string id) {
        id = id.substr(0, 3);
        std::transform(id.begin(), id.end(), id.begin(), [](unsigned char c) { return std::toupper(c); });
        return id;
    }


    std::string ProductController::autoGenerateID() {
        std::string id = "AAA";

        if (!repo->getScooters(adminFile).empty()) {
            std::set<std::string> existingIDs;

            for (const auto &scooter: repo->getScooters(adminFile)) {
                existingIDs.insert(scooter.getID());
            }
            while (existingIDs.find(id) != existingIDs.end()) {
                if (id[2] == 'Z') {
                    id[2] = 'A';
                    if (id[1] == 'z') {
                        id[1] = 'A';

                        if (id[0] == 'Z') {
                            return "";
                        } else {
                            id[0]++;
                        }
                    } else {
                        id[1]++;
                    }
                } else {
                    id[2]++;
                }
            }
        }
        return id;
    }

    bool ProductController::isValidDate(const int &year, const int &month, const int &day) {
        if (month < 1 || month > 12) {
            return false;
        }
        if (day < 1 || day > 31) {
            return false;
        }
        if (month == 2) {
            if (year % 4 == 0) {
                if (year % 100 == 0 && year % 400 != 0) {
                    if (day > 28) {
                        return false;
                    }
                } else {
                    if (day > 29) {
                        return false;
                    }
                }
            } else {
                if (day > 28) {
                    return false;
                }
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) {
                return false;
            }
        }
        return true;
    }

    std::vector<domain::Scooter> ProductController::userReservedScooters() {
        std::vector<domain::Scooter> scooters = repo->getScooters(userFile);
        std::vector<domain::Scooter> reservedScooters;
        for (const auto &scooter: scooters) {
            if (scooter.getState() == domain::State::RESERVED) {
                reservedScooters.push_back(scooter);
            }
        }
        return reservedScooters;
    }
}