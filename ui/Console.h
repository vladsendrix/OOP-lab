#include "../controller/Controller.h"
namespace ui
{
    class Console {
        private:
        controller::ProductController ctrl;
        public:
            Console(const controller::ProductController& scooterController);
            void run();
            void adminMethods();
            void userMethods();
    };
};