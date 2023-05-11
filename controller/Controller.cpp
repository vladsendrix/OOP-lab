#include "Controller.h"

namespace controller
{
    ProductController::ProductController(repository::Repository &scooterRepo)
    {
        this->repo=scooterRepo;
    }

    void ProductController::addScooter()
    {

    }

    void ProductController::deleteScooter() {
    }

    void ProductController::editScooter() {
    }

    void ProductController::searchScooterByStandPlace() {
    }

    void ProductController::filterScooterByAge() {
    }

    void ProductController::filterScooterByMileage() {
    }

    void ProductController::listScooterByAge() {
    }
};