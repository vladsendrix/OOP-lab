#include "Console.h"
#include <iostream>

namespace ui {
    Console::Console(const controller::ProductController& controller_) {
        controller=controller_;
    } 

    void Console::adminMethods() {
        std::cout<<"Menu\n"
                    "0. EXIT\n"
                    "1. Add scooter\n"
                    "2. Delete scooter\n"
                    "3. Edit scooter\n"
                    "4. Search scooter by stand place\n"
                    "5. Filter scooter by age\n"
                    "6. Filter scooter by mileage\n"
                    "7. List scooter by age (ascending)\n"
                    "Enter option: ";
        int option;
        std::cin>>option;
        switch (option) {
            case 0 : {
                std::cout<<"Goodbye!"<<std::endl;
                return;
            }
            case 1: {
                controller.addScooter();
                break;
            }
            case 2: {
                controller.deleteScooter();
                break;
            }
            case 3: {
                controller.editScooter();
                break;
            }

            case 4: {
                controller.searchScooterByStandPlace();
                break;
            }

            case 5: {
                controller.filterScooterByAge();
                break;
            }
            case 6: {
                controller.filterScooterByMileage();
                break;
            }
            case 7: {
                controller.listScooterByAge();
                break;
            }
            default: {
                std::cout<<"Invalid option, please try again." << std::endl;
            }
        }
    }

    void Console::userMethods() {

        std::cout<<"Menu\n"
                    "0. EXIT\n"
                    "1. Reservation of scooter\n"
                    "2. Use scooter\n"
                    "3. Search scooter by stand place"
                    "4. Filter scooter by age\n"
                    "5. Filter scooter by mileage\n"
                    "6. Reserve a scooter\n"
                    "7. Use a scooter\n"
                    "Enter option: ";
        int option;
        std::cin>>option;
        switch (option) {
            case 0 : {
                std::cout<<"Goodbye!"<<std::endl;
                return;
            }
            case 1: {
                // controller.reserveScooter();
                break;
            }
            case 2: {
                // useScooter();
                break;
            }
            case 3: {
                controller.searchScooterByStandPlace();
                break;
            }

            case 4: {
                controller.filterScooterByAge();
                break;
            }

            case 5: {
                controller.filterScooterByMileage();
                break;
            }

            case 6: {
                // controller.reserveScooter();
                break;
            }

            case 7: {
                // controller.useScooter();
                break;
            }
            default: {
                std::cout<<"Invalid option, please try again." << std::endl;
            }
        }
    }
    void Console::run() {
        int option;

        while (true)
        {
            int role{-1};
            while(role!=0 || role != 1 || role != 2){
                std::cout<<"Please choose:\n"
                            "0.EXIT\n"
                            "1. Admin\n"
                            "2. User\n"
                            "Enter option:";
                std::cin>>role;
            }

            if (role==0) {
                break;
            } else if (role == 1) {
                adminMethods();
            } else {
                userMethods();
            } 
        }  
    }
};