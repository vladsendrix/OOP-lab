#include "Console.h"
#include <iostream>


namespace ui {
    Console::Console(controller::ProductController &scooterController) {
        this->ctrl = scooterController;
    }

    void Console::adminMethods() {

        while (true) {
            std::cout << "\nAdmin Menu\n"
                         "0. EXIT\n"
                         "Scooter options:\n"
                         "1.  Add one\n"
                         "2.  Delete one\n"
                         "3.  Edit one\n"
                         "4.  Search by stand place\n"
                         "5.  Filter by age (younger than)\n"
                         "6.  Filter by age (older than inclusive)\n"
                         "7.  Filter by mileage (km)(lower than) \n"
                         "8.  Filter by mileage (km)(higher than inclusive) \n"
                         "9.  List by age (ascending)\n"
                         "10. List by age (descending)\n"
                         "Enter option (0-10): ";
            int option;
            std::cin >> option;
            switch (option) {
                case 0 : {
                    std::cout << std::endl << "Goodbye!" << std::endl;
                    return;
                }
                case 1: {
                    ctrl.addScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    ctrl.deleteScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    ctrl.editScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }

                case 4: {
                    ctrl.searchScooterByStandPlace();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    ctrl.filterScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 6: {
                    ctrl.filterScooterByAge(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 7: {
                    ctrl.filterScooterByMileage(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 8: {
                    ctrl.filterScooterByMileage(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 9: {
                    ctrl.listScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 10: {
                    ctrl.listScooterByAge(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                default: {
                    std::cout << "Invalid option, please try again." << std::endl;
                }
            }
        }
    }

    void Console::userMethods() {
        while (true) {
            std::cout << "\nUser Menu\n"
                         "0. EXIT\n"
                         "Scooter Options:\n"
                         "1. Search by stand place"
                         "2. Filter by age (younger than)\n"
                         "3. Filter by age (older than inclusive)\n"
                         "4. Filter by mileage (km)(lower than) \n"
                         "5. Filter by mileage (km)(higher than inclusive) \n"
                         "6. Reserve one\n"
                         "7. Use one\n"
                         "Enter option (0-7): ";
            int option;
            std::cin >> option;
            switch (option) {
                case 0 : {
                    std::cout << std::endl << "Goodbye!" << std::endl;
                    return;
                }
                case 1: {
                    ctrl.searchScooterByStandPlace();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    ctrl.filterScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    ctrl.filterScooterByAge(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 4: {
                    ctrl.filterScooterByMileage(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    ctrl.filterScooterByMileage(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 6: {
                    ctrl.reserveScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 7: {
                    ctrl.useScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                default: {
                    std::cout << "Invalid option, please try again." << std::endl;
                }
            }
        }
    }


    void Console::run() {
        ctrl.loadDataFromFile();
        ctrl.printScooterByID();
        ctrl.saveDataToFile();
        std::cout << "\n\n";
        std::cout << "@authors: Sendroiu Vlad, Rapolti Zsolt, Stelli Janos\n\n";
        while (true) {
            int role{-1};
            std::cout << "\nPlease choose:\n"
                         "0. EXIT\n"
                         "1. Admin\n"
                         "2. User\n"
                         "Enter option:";
            std::cin >> role;
            if (role == 0) {
                std::cout << "\n\nGoodbye!";
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
