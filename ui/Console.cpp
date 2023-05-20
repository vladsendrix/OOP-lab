#include "Console.h"
#include <iostream>


namespace ui {

    Console::Console(std::shared_ptr<controller::ProductController> scooterController_) {
        this->ctrl = std::move(scooterController_);
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
                         "5.  Filter by age (younger than -inclusive)\n"
                         "6.  Filter by age (older than)\n"
                         "7.  Filter by mileage (km)(lower than) \n"
                         "8.  Filter by mileage (km)(higher than -inclusive) \n"
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

                    std::string model, lastStandPlace, date;
                    domain::Date commissionDate{2023, 01, 01};
                    domain::State state;
                    int mileage, stateNr;


                    std::cout << std::endl << "Enter the scooter details:\nModel: ";
                    std::getline(std::cin >> std::ws, model);

                    std::cout << std::endl << "Commission Date (yyyy-mm-dd): ";
                    std::getline(std::cin >> std::ws, date);
                    if (!date.empty()) {
                        commissionDate.year = std::stoi(date.substr(0, 4));
                        commissionDate.month = std::stoi(date.substr(5, 2));
                        commissionDate.day = std::stoi(date.substr(8, 2));
                    }

                    std::cout << std::endl << "Mileage: ";
                    std::cin >> mileage;

                    std::cout << std::endl << "Last Stand Place: ";
                    std::getline(std::cin >> std::ws, lastStandPlace);

                    std::cout << std::endl
                              << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT | 5. OUT OF SERVICE)\nChoose one (1-5): ";
                    std::cin >> stateNr;
                    switch (stateNr) {
                        case 2:
                            state = domain::RESERVED;
                            break;
                        case 3:
                            state = domain::INUSE;
                            break;
                        case 4:
                            state = domain::INWAIT;
                            break;
                        case 5:
                            state = domain::OUTOFSERVICE;
                            break;
                        default:
                            state = domain::PARKED;
                    }
                    std::cout << std::endl;
                    ctrl->addScooter(model, commissionDate, mileage, lastStandPlace, state);
                    std::cout << std::endl;
                    std::cout << "\nScooter added successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    std::string scooterID;
                    std::cout << "Enter the ID of the scooter to delete: ";
                    std::cin >> scooterID;
                    if (ctrl->deleteScooter(ctrl->findById(scooterID))) {
                        std::cout << "Scooter deleted successfully!" << std::endl;
                    } else {
                        std::cout << "Scooter not found!" << std::endl;
                    }
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    ctrl->editScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }

                case 4: {
                    ctrl->searchScooterByStandPlace();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    ctrl->filterScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 6: {

                    ctrl->filterScooterByAge(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 7: {
                    ctrl->filterScooterByMileage(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 8: {
                    ctrl->filterScooterByMileage(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 9: {
                    ctrl->listScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 10: {
                    ctrl->listScooterByAge(false);
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
                         "1. Search by stand place\n"
                         "2. Filter by age (younger than -inclusive)\n"
                         "3. Filter by age (older than)\n"
                         "4. Filter by mileage (km)(lower than) \n"
                         "5. Filter by mileage (km)(higher than -inclusive) \n"
                         "6. Reserve one\n"
                         "7. Use one\n"
                         "8. Quit useage (park it)\n"
                         "Enter option (0-8): ";
            int option;
            std::cin >> option;
            switch (option) {
                case 0 : {
                    std::cout << std::endl << "Goodbye!" << std::endl;
                    return;
                }
                case 1: {
                    ctrl->searchScooterByStandPlace();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    ctrl->filterScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    ctrl->filterScooterByAge(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 4: {
                    ctrl->filterScooterByMileage(true);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    ctrl->filterScooterByMileage(false);
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 6: {
                    ctrl->reserveScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 7: {
                    ctrl->useScooter();
                    std::cout << std::endl;
                    system("pause");
                    break;
                }
                case 8: {
                    ctrl->parkScooter();
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
        ctrl->loadDataFromFile();
        ctrl->printScooterByID();
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


}
