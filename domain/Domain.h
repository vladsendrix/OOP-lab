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
            Date commision_date;
            int mileage;
            std:: string lastStandPlace;
            State state;
        public:
        string get_id();
        string get_model();
        


    };
}