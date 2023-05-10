#include "Console.h"
#include <iostream>

namespace ui
{
    Console::Console(const controller::ProductController& controller) : controller_(controller) {}

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
                //std::cout<<"Goodbye!"<<std::endl;
                return;
            }
            case 1: {
                addScooter();
                break;
            }
            case 2: {
                deleteScooter();
                break;
            }
            case 3: {
                //editScooter();
                break;
            }

            case 4: {
                break;
            }

            case 5: {
                filterScooterByAge();
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            default: {
                std::cout<<"Invalid option, please try again." << endl;
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
                
                break;
            }
            case 2: {

                break;
            }
            case 3: {
                searchScooterByStandPlace();
                break;
            }

            case 4: {
                break;
            }

            case 5: {
                break;
            }

            case 6: {
                break;
            }

            case 7: {
                break;
            }
            default: {
                std::cout<<"Invalid option, please try again." << endl;
            }
        }
    void Console::run()
    {
        int option;

        while (true)
        {
            int role{0};
            while(role != 1 && role != 2)
            {
                std::cout<<"Please choose: \n"
                            "1. Admin\n"
                            "2. User\n"
                            "Enter option:";
                std::cin>>role;
            }
            
            if (role == 1) {
                adminMethods();
            } else {
                userMethods();
            } 

            std::cout << "Menu:" << std::endl;
            std::cout << "1. Add product" << std::endl;
            std::cout << "2. Delete product" << std::endl;
            std::cout << "3. Get products by name" << std::endl;
            std::cout << "4. Get short supply products" << std::endl;
            std::cout << "5. Get all products by expiry date" << std::endl;
            std::cout << "6. Exit" << std::endl;
            std::cout << "Enter option: ";

            std::cin >> option;

            switch (option)
            {
            case 1:
            {
                domain::Product product;
                std::cout << "Enter product name: ";
                std::cin >> product.name;
                std::cout << "Enter product origin: ";
                std::cin >> product.origin;
                std::cout << "Enter product expiry date (year month day): ";
                std::cin >> product.expiry_date.year >> product.expiry_date.month >> product.expiry_date.day;
                std::cout << "Enter product quantity: ";
                std::cin >> product.quantity;
                std::cout << "Enter product price: ";
                std::cin >> product.price;

                controller_.addProduct(product);
                break;
            }
            case 2:
            {
                std::string name;
                std::cout << "Enter product name: ";
                std::cin >> name;

                controller_.deleteProduct(name);
                break;
            }
            case 3:
            {
                std::string name;
                std::cout << "Enter product name: ";
                std::cin >> name;

                auto products = controller_.getProductsByName(name);
                for (const auto& product : products)
                {
                    std::cout << product.getName() << std::endl;
                }
                break;
            }
            case 4:
            {
                int threshold;
                std::cout << "Enter short supply threshold: ";
                std::cin >> threshold;

                auto products = controller_.getShortSupplyProducts(threshold);
                for (const auto& product : products)
                {
                    std::cout << product.getName() << std::endl;
                }
                break;
            }
            case 5:
            {
                auto products = controller_.getAllProductsByExpiryDate();
                for (const auto& product : products)
                {
                    std::cout << product.getName() << std::endl;
                }
                break;
            }
            case 6:
            {
                std::cout << "Goodbye!" << std::endl;
                return;
            }
            default:
                std::cout << "Invalid option, please try again." << std::endl;
            }
        }
    }
}
}