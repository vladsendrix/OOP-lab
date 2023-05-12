#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>

namespace domain {

    struct Date {
        int year, month, day;

        bool operator<(const Date& other) const {
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
        Date commissionDate{};
        int mileage;
        std::string lastStandPlace;
        State state;

    public:
        Scooter(const std::string& id, const std::string& model, const Date& commissionDate,
                int mileage, const std::string& lastStandPlace, const State& state);

        std::string getID() const;
        std::string getModel() const;
        Date getCommissionDate() const;
        int getMileage() const;
        std::string getLastStandPlace() const;
        State getState() const;
        void setID(const std::string& id);
        void setModel(const std::string& model);
        void setCommissionDate(const Date& commissionDate);
        void setMileage(int mileage);
        void setLastStandPlace(const std::string& lastStandPlace);
        void setState(const State& state);
    };

}

#endif // DOMAIN_H
