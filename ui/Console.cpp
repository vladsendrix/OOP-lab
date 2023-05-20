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
                    int mileage, stateNr;

                    std::cout << std::endl << "Enter the scooter details:\nModel: ";
                    std::getline(std::cin >> std::ws, model);

                    std::cout << std::endl << "Commission Date (yyyy-mm-dd): ";
                    std::getline(std::cin >> std::ws, date);

                    std::cout << std::endl << "Mileage: ";
                    std::cin >> mileage;

                    std::cout << std::endl << "Last Stand Place: ";
                    std::getline(std::cin >> std::ws, lastStandPlace);

                    std::cout << std::endl
                              << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT | 5. OUT OF SERVICE)\nChoose one (1-5): ";
                    std::cin >> stateNr;

                    std::cout << std::endl;

                    Console::printDetailHeader();
                    Console::printScooter(ctrl->addScooter(model, date, mileage, lastStandPlace, stateNr));
                    std::cout << "\nScooter added successfully!" << std::endl;
                    std::cin >> model; // prevent the menu pop-up
                    break;
                }
                case 2: {
                    std::string scooterID;
                    std::cout << "Enter the ID of the scooter to delete: ";
                    std::cin >> scooterID;
                    if (ctrl->deleteScooter(ctrl->exists(ctrl->position(scooterID)))) {
                        std::cout << "Scooter deleted successfully!" << std::endl;
                    } else {
                        std::cout << "Scooter not found!" << std::endl;
                    }
                    std::cout << std::endl;
                    std::cin >> scooterID; // prevent the menu pop-up
                    break;
                }
                case 3: {
                    std::string scooterID;
                    std::cout << std::endl << "Enter the ID of the scooter to edit: ";
                    std::cin >> scooterID;
                    if (!ctrl->exists(ctrl->position(scooterID))) {
                        std::cout << "Scooter not found!" << std::endl;
                    } else {
                        std::string model, lastStandPlace, date;
                        int stateNr, mileage;

                        std::cout << std::endl << "Enter new commission Date (yyyy-mm-dd): ";
                        std::getline(std::cin >> std::ws, date);

                        std::cout << std::endl << "Mileage: ";
                        std::cin >> mileage;

                        std::cout << std::endl << "Last Stand Place: ";
                        std::getline(std::cin >> std::ws, lastStandPlace);

                        std::cout << std::endl
                                  << "State:(1. PARKED | 2. RESERVED | 3. IN USE | 4. IN WAIT | 5. OUT OF SERVICE)\nChoose one (1-5): ";
                        std::cin >> stateNr;
                        std::cout << std::endl;


                        printDetailHeader();
                        printScooter(
                                ctrl->editScooter(ctrl->position(scooterID), date, mileage, lastStandPlace, stateNr));

                        std::cout << "Scooter edited successfully!" << std::endl;
                    }
                    std::cout << std::endl;
                    std::cin >> scooterID; // prevent the menu pop-up
                    break;
                }

                case 4: {
                    std::string standPlace;
                    std::cout << "Enter the stand place (or leave empty to show all scooters): ";
                    std::cin.ignore();
                    std::getline(std::cin, standPlace);
                    if (ctrl->searchScooterByStandPlace(standPlace).empty()) {
                        std::cout << "No scooters found with the specified stand place!" << std::endl;
                    } else {
                        printDetailHeader();
                        for (const auto &scooter: ctrl->searchScooterByStandPlace(standPlace)) {
                            printScooter(scooter);
                        }
                    }
                    std::cout << std::endl;
                    std::cin >> standPlace; // prevent the menu pop-up
                    break;
                }
                case 5: {
                    ctrl->filterScooterByAge(true);
                    std::cout << std::endl;
                    system("pause");
                    std::cout << "No scooters found with an age greater than " << age << " years!" << std::endl;
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
                    std::string standPlace;
                    std::cout << "Enter the stand place (or leave empty to show all scooters): ";
                    std::cin.ignore();
                    std::getline(std::cin, standPlace);
                    if (ctrl->searchScooterByStandPlace(standPlace).empty()) {
                        std::cout << "No scooters found with the specified stand place!" << std::endl;
                    } else {
                        printDetailHeader();
                        for (const auto &scooter: ctrl->searchScooterByStandPlace(standPlace)) {
                            printScooter(scooter);
                        }
                    }
                    std::cout << std::endl;
                    std::cin >> standPlace; // prevent the menu pop-up
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


    void Console::printDetailHeader() {
        std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Model" <<
                  std::setw(20) << "Commission Date" << std::setw(15) << "Mileage" <<
                  std::setw(30) << "Last Stand Place" << std::setw(15) << "State" << std::endl;
        for (int i = 0; i < 110; i++) std::cout << "-";
        std::cout << std::endl;
    }

    void Console::printScooter(const domain::Scooter &scooter) {

        const domain::Date date = scooter.getCommissionDate();
        const std::string dateToString = std::to_string(date.year) + "." + std::to_string(date.month) +
                                         "." + std::to_string(date.day);

        std::cout << std::left << std::setw(5) << scooter.getID()
                  << std::setw(30) << scooter.getModel()
                  << std::setw(20) << dateToString
                  << std::setw(15) << scooter.getMileage()
                  << std::setw(30) << scooter.getLastStandPlace()
                  << std::setw(15) << std::left;

        switch (scooter.getState()) {
            case domain::PARKED:
                std::cout << "PARKED" << std::endl;
                break;
            case domain::RESERVED:
                std::cout << "RESERVED" << std::endl;
                break;
            case domain::INUSE:
                std::cout << "IN USE" << std::endl;
                break;
            case domain::INWAIT:
                std::cout << "IN WAIT" << std::endl;
                break;
            case domain::OUTOFSERVICE:
                std::cout << "OUT OF SERVICE" << std::endl;
                break;
            default:
                std::cout << "PARKED" << std::endl;
        }
    }


}
