#ifndef DOMAIN_H
#define DOMAIN_H
#include <string>

namespace domain {

    struct Date {
        int year, month, day;

        bool operator<(const Date &other) const {
            if (year != other.year) return year < other.year;
            if (month != other.month) return month < other.month;
            return day < other.day;
        }
    };

    enum State {
        PARKED,
        RESERVED,
        INUSE,
        INWAIT,
        OUTOFSERVICE
    };

    class Scooter {
    private:
        std::string id;
        std::string model;
        Date commision_date;
        int mileage;
        std::string lastStandPlace;
        State state;
    public:
        Scooter(std::string &id_, std::string &model_, Date &commision_date_, int &mileage_,
                std::string &lastStandPlace_, State &state_);

        std::string getID();
        std::string getModel();
        Date ComissionDate();
        int getMileage();
        std::string getLastStandPlace();
        State getState();
        void setID(std::string& id);
        void setModel();
        void setComissionDate();
        int setMileage();
        void setLastStandPlace();
        void setState();
    };
};

#endif
