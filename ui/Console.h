#include "../controller/Controller.h"
using namespace controller;
namespace ui
{
    class Console {
        private:
        controller::ProductController controller;
        public:
            Console(const controller::ProductController& controller);
            void run();    
            void adminMethods();  
            void userMethods();      
    };
}