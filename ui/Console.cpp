#include "Console.h"
#include <iostream>

namespace ui {

    Console::Console(std::shared_ptr<controller::ProductController> scooterController_) {
        this->ctrl = std::move(scooterController_);
    }

    void Console::adminMethods() {
        printArrayOfScooters(ctrl->sortScooters(true,"ID"));
        while (true) {
            printMessage("\nAdmin Menu\n"
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
                         "Enter option (0-10): ");
            int option = readNumber();
            switch (option) {
                case 0 : {
                    printMessage("Goodbye!");
                    return;
                }
                case 1: {
                    printMessage("Enter the scooter details:\nModel: ");
                    std::string model = readString();

                    printMessage("Commission Date (yyyy-mm-dd): ");
                    std::string date = readString();

                    printMessage("Mileage: ");
                    int mileage = readNumber();

                    printMessage("Last Stand Place: ");
                    std::string lastStandPlace = readString();

                    printMessage(
                            "State:(1.PARKED | 2.RESERVED | 3.IN USE | 4.IN WAIT | 5.OUT OF SERVICE)\nChoose one (1-5):");
                    int stateNr = readNumber();

                    Console::printDetailHeader();
                    Console::printScooter(ctrl->addScooter(model, date, mileage, lastStandPlace, stateNr));
                    printMessage("\nScooter added successfully!");

                    preventMenuPopUp();
                    break;
                }
                case 2: {
                    printMessage("Enter the ID of the scooter to delete: ");
                    std::string scooterID = readString();
                    int index = ctrl->position(scooterID);
                    if (index != -1) {
                        if (ctrl->deleteScooter(index)) {
                            printMessage("Scooter deleted successfully!");
                        } else {
                            printMessage("Error deleting scooter!");
                        }
                    } else printMessage("Scooter not found!");

                    preventMenuPopUp();
                    break;
                }
                case 3: {
                    printMessage("Enter the ID of the scooter to edit: ");
                    std::string scooterID = readString();
                    int position = ctrl->position(scooterID);

                    if (position == -1) {
                        printMessage("Scooter not found!");
                    } else {
                        printMessage("Enter new commission Date (yyyy-mm-dd): ");
                        std::string date = readString();

                        printMessage("Mileage: ");
                        int mileage = readNumber();

                        printMessage("Last Stand Place: ");
                        std::string lastStandPlace = readString();

                        printMessage(
                                "State: (1.PARKED | 2.RESERVED | 3.IN USE | 4.IN WAIT | 5.OUT OF SERVICE)\nChoose one (1-5): ");
                        int stateNr = readNumber();
                        printMessage("");

                        printDetailHeader();
                        domain::Scooter editedScooter = ctrl->editScooter(position, date, mileage, lastStandPlace,
                                                                          stateNr);
                        printScooter(editedScooter);

                        printMessage("Scooter edited successfully!");
                    }
                    preventMenuPopUp();
                    break;

                }

                case 4: {
                    printMessage("Enter the stand place (or leave empty to show all scooters): ");
                    std::string standPlace = readString();
                    std::vector<domain::Scooter> scooters = ctrl->searchScooterByStandPlace(standPlace);

                    if (scooters.empty()) {
                        printMessage("No scooters found with the specified stand place!");
                    } else {
                        printArrayOfScooters(scooters);
                    }
                    preventMenuPopUp();
                    break;
                }
                case 5: {
                    printMessage("Enter the age: ");
                    int age = readNumber();
                    bool inclusive = true;

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByAge(inclusive, age);

                    if (filteredScooters.empty()) {
                        printMessage(
                                "No scooters younger than or equal to " + std::to_string(age) + " years were found!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }
                    preventMenuPopUp();
                    break;
                }
                case 6: {
                    printMessage("Enter the age: ");
                    int age = readNumber();
                    bool inclusive = false;

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByAge(inclusive, age);

                    if (filteredScooters.empty()) {
                        printMessage("No scooters older than " + std::to_string(age) + " years were found!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }

                    preventMenuPopUp();
                    break;
                }
                case 7: {
                    printMessage("Enter the mileage: ");
                    int mileage = readNumber();
                    bool lessThan = true;

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByMileage(lessThan, mileage);

                    if (filteredScooters.empty()) {
                        printMessage(
                                "No scooters found with a mileage lower than " + std::to_string(mileage) + " miles!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }
                    preventMenuPopUp();
                    break;
                }
                case 8: {
                    printMessage("Enter the mileage: ");
                    int mileage = readNumber();
                    bool lessThan = false;

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByMileage(lessThan, mileage);

                    if (filteredScooters.empty()) {
                        printMessage(
                                "No scooters found with a mileage higher than " + std::to_string(mileage) + " miles!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }
                    preventMenuPopUp();
                    break;
                }
                case 9: {
                    printMessage("\nList of scooters sorted by eage (ascending):");
                    printArrayOfScooters(ctrl->sortScooters(true,"Age"));
                    preventMenuPopUp();
                    break;
                }
                case 10: {
                    printMessage("\nList of scooters sorted by eage (ascending):");
                    printArrayOfScooters(ctrl->sortScooters(false,"Age"));
                    preventMenuPopUp();
                    break;
                }
                default: {
                    printMessage("Invalid option, please try again.");
                    preventMenuPopUp();
                    break;
                }
            }
        }
    }

    void Console::userMethods() {
        while (true) {
            printMessage("\nUser Menu\n"
                         "0. EXIT\n"
                         "Scooter Options:\n"
                         "1. Search by stand place\n"
                         "2. Filter by age (younger than -inclusive)\n"
                         "3. Filter by age (older than)\n"
                         "4. Filter by mileage (km)(lower than) \n"
                         "5. Filter by mileage (km)(higher than -inclusive) \n"
                         "6. Reserve one\n"
                         "7. Use one\n"
                         "8. Quit usage (park it)\n"
                         "9. View list of reserved scooters\n"
                         "Enter option (0-9): ");
            int option = readNumber();
            switch (option) {
                case 0 : {
                    printMessage("Goodbye!");
                    return;
                }
                case 1: {
                    printMessage("Enter the stand place (or leave empty to show all scooters): ");
                    std::string standPlace = readString();
                    std::vector<domain::Scooter> scooters = ctrl->searchScooterByStandPlace(standPlace);

                    if (scooters.empty()) {
                        printMessage("No scooters found with the specified stand place!");
                    } else {
                        printDetailHeader();
                        for (const auto &scooter: scooters) {
                            printScooter(scooter);
                        }
                    }
                    preventMenuPopUp();
                    break;
                }
                case 2: {
                    printMessage("Enter the age: ");
                    int age = readNumber();

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByAge(true, age);

                    if (filteredScooters.empty()) {
                        printMessage(
                                "No scooters younger than or equal to " + std::to_string(age) + " years were found!");
                    } else {
                        printDetailHeader();
                        for (const auto &scooter: filteredScooters) {
                            printScooter(scooter);
                        }
                    }

                    preventMenuPopUp();
                    break;

                }
                case 3: {
                    printMessage("Enter the age: ");
                    int age = readNumber();

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByAge(false, age);

                    if (filteredScooters.empty()) {
                        printMessage("No scooters older than " + std::to_string(age) + " years were found!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }

                    preventMenuPopUp();
                    break;

                }
                case 4: {
                    printMessage("Enter the mileage: ");
                    int mileage = readNumber();

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByMileage(true, mileage);

                    if (filteredScooters.empty()) {
                        printMessage(
                                "No scooters found with a mileage lower than or equal to " + std::to_string(mileage) +
                                " miles!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }

                    preventMenuPopUp();
                    break;

                }
                case 5: {
                    printMessage("Enter the mileage: ");
                    int mileage = readNumber();
                    bool lessThan = false;

                    std::vector<domain::Scooter> filteredScooters = ctrl->filterScooterByMileage(lessThan, mileage);

                    if (filteredScooters.empty()) {
                        printMessage(
                                "No scooters found with a mileage higher than or equal to " + std::to_string(mileage) +
                                " miles!");
                    } else {
                        printArrayOfScooters(filteredScooters);
                    }
                    preventMenuPopUp();
                    break;
                }
                case 6: {
                    printArrayOfScooters(ctrl->sortScooters(true,"ID"));

                    printMessage("Here are the scooters listed.\nPlease enter an ID to reserve a scooter: ");
                    std::string readID = readString();
                    printMessage("");

                    int position = ctrl->position(readID);

                    if (position == -1) {
                        printMessage("\nSorry, the scooter with the ID " + readID + " was not found.\n");
                    } else if (ctrl->reserveScooter(position)) {
                        printMessage("\nThe scooter with the ID " + readID + " was reserved.\n");
                    } else {
                        printMessage(
                                "\nSorry, the scooter with the ID " + readID + " is not available for reservation.\n");
                    }

                    preventMenuPopUp();
                    break;
                }
                case 7: {
                    printMessage("\nPlease enter the ID of the scooter you reserved to use it: ");
                    std::string readID = readString();

                    int position = ctrl->position(readID);

                    if (position == -1) {
                        printMessage("\nSorry, the scooter with the ID " + readID + " was not found.\n");
                    } else if (ctrl->useScooter(position)) {
                        printMessage("\nYou can use the scooter with the ID " + readID + "\n");
                    } else {
                        printMessage("\nSorry, the scooter with the ID " + readID + " is not reserved\n");
                    }

                    preventMenuPopUp();
                    break;
                }
                case 8: {
                    printMessage("\nPlease enter the ID of the scooter you are using to stop using it (to park it): ");
                    std::string readID = readString();

                    printMessage("Please enter your current location: ");
                    std::string location = readString();

                    int position = ctrl->position(readID);

                    if (position == -1) {
                        printMessage("\nSorry, the scooter with the ID " + readID + " was not found.\n");
                    } else if (ctrl->parkScooter(position, location)) {
                        printMessage("\nThe scooter with the ID " + readID +
                                     " is parked now.\n\nThank you for using our service!\n");
                    } else {
                        printMessage("\nSorry, the scooter with the ID " + readID + " is not in use.\n");
                    }

                    preventMenuPopUp();
                    break;
                }
                case 9: {
                    printMessage("Here are your reserved scooters:\n");
                    printArrayOfScooters(ctrl->userReservedScooters());
                    break;
                }
                default: {
                    printMessage("Invalid option, please try again.");
                    preventMenuPopUp();
                    break;
                }
            }
        }
    }

    void Console::printMessage(const std::string &message) {
        std::cout << std::endl << message << "\n";
    }

    void Console::run() {
        Console::printMessage("\n\n@authors: Sendroiu Vlad, Rapolti Zsolt, Stelli Janos\n\n");
        while (true) {
            Console::printMessage("\nPlease choose:\n"
                                  "0. EXIT\n"
                                  "1. Admin\n"
                                  "2. User\n"
                                  "Enter option:");
            int role = Console::readNumber();
            if (role == 0) {
                Console::printMessage("\n\nGoodbye!");
                break;
            } else if (role == 1) {
                adminMethods();
            } else if (role == 2) {
                userMethods();
            }
            Console::printMessage("\nInvalid option, please try again.");
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
                  << std::setw(15);

        switch (scooter.getState()) {
            case domain::State::PARKED:
                std::cout << "PARKED" << std::endl;
                break;
            case domain::State::RESERVED:
                std::cout << "RESERVED" << std::endl;
                break;
            case domain::State::INUSE:
                std::cout << "IN USE" << std::endl;
                break;
            case domain::State::INWAIT:
                std::cout << "IN WAIT" << std::endl;
                break;
            case domain::State::OUTOFSERVICE:
                std::cout << "OUT OF SERVICE" << std::endl;
                break;
            default:
                std::cout << "PARKED" << std::endl;
        }
    }

    void Console::printArrayOfScooters(const std::vector<domain::Scooter> &scooters) {
        printDetailHeader();
        for (const auto &scooter: scooters) {
            printScooter(scooter);
        }
    }


    int Console::readNumber() {
        int value;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> value;
        return value;
    }

    std::string Console::readString() {
        std::string value;
        std::getline(std::cin, value);
        return value;
    }

    void Console::preventMenuPopUp() {
        printMessage("\nPress any key and ENTER to continue: ");
        std::string preventMenuPopup = readString();
    }
}