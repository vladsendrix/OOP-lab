#include "Console.h"
#include <iostream>


namespace ui {
    Console::Console(controller::ProductController &scooterController) {
        this->ctrl = scooterController;
    }

    void Console::adminMethods() {
        std::cout << "\nMenu\n"
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
        std::cin >> option;
        switch (option) {
            case 0 : {
                std::cout << "Goodbye!" << std::endl;
                return;
            }
            case 1: {
                ctrl.addScooter();
                break;
            }
            case 2: {
                ctrl.deleteScooter();
                break;
            }
            case 3: {
                ctrl.editScooter();
                break;
            }

            case 4: {
                ctrl.searchScooterByStandPlace();
                break;
            }

            case 5: {
                ctrl.filterScooterByAge();
                break;
            }
            case 6: {
                ctrl.filterScooterByMileage();
                break;
            }
            case 7: {
                ctrl.listScooterByAge();
                break;
            }
            default: {
                std::cout << "Invalid option, please try again." << std::endl;
            }
        }
    }

    void Console::userMethods() {

        std::cout << "\nMenu\n"
                     "0. EXIT\n"
                     "1. Search scooter by stand place"
                     "2. Filter scooter by age\n"
                     "3. Filter scooter by mileage\n"
                     "4. Reserve a scooter\n"
                     "5. Use a scooter\n"
                     "Enter option: ";
        int option;
        std::cin >> option;
        switch (option) {
            case 0 : {
                std::cout << "Goodbye!" << std::endl;
                return;
            }

            case 1: {
                ctrl.searchScooterByStandPlace();
                break;
            }

            case 2: {
                ctrl.filterScooterByAge();
                break;
            }

            case 3: {
                ctrl.filterScooterByMileage();
                break;
            }

            case 4: {
                ctrl.reserveScooter();
                break;
            }

            case 5: {
                ctrl.useScooter();
                break;
            }

            default: {
                std::cout << "Invalid option, please try again." << std::endl;
            }
        }
    }


    void Console::run() {
        int option;
        std::cout<<"@authors: Sendroiu Vlad, Rapolti Zsolt, Stelli Janos\n\n";
        while (true) {
            int role{-1};
            std::cout <<"\nPlease choose:\n"
                        "0. EXIT\n"
                        "1. Admin\n"
                        "2. User\n"
                        "Enter option:";
            std::cin >> role;
            if (role == 0) {
                std::cout<<"\n\nGoodbye!";
                break;
            } else if (role == 1) {
                adminMethods();
            } else if (role == 2) {
                userMethods();
            }
            std::cout << "\nInvalid option, please try again." << std::endl;
        }
    }
};

