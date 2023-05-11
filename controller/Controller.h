#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../repository/Repository.h"
#include <vector>
namespace controller {
    class ProductController {
    private:
        repository::Repository repo;
    public:
        explicit ProductController(const repository::Repository &scooterRepo);
        void addScooter();
        void deleteScooter();
        void editScooter();
        void searchScooterByStandPlace();
        void filterScooterByAge();
        void filterScooterByMileage();
        void listScooterByAge();
    };
};

#endif