#include "../repository/Repository.h"

namespace controller {
    class ProductController {
    private:
        repository::Repository repo;
    public:
        ProductController(repository::Repository & scooterRepo);
        void addScooter();
        void deleteScooter();
        void editScooter();
        void searchScooterByStandPlace();
        void filterScooterByAge();
        void filterScooterByMileage();
        void listScooterByAge();
    };
};