
#include "../controller/Controller.h"
namespace ui
{
    class Console {
        private:
        controller::ProductController ctrl;
        public:
            Console(controller::ProductController &scooterController);
            void run();
            void adminMethods();
            void userMethods();
    };
};