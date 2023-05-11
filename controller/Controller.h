#include "../repository/Repository.h"

namespace controller {
    class ProductController {
    private:
    public:
        void addScooter();
        void deleteScooter();
        void editScooter();
        void searchScooterByStandPlace();
        void filterScooterByAge();
        void filterScooterByMileage();
        void listScooterByAge();
    };
};