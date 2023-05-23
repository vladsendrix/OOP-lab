#include "Repository.h"

namespace repository {

    RepositoryInMemory::RepositoryInMemory() {
            domain::Scooter scooter1=domain::Scooter("AAA","Honda Activa",{2022,01,05},1200,"Central Station",domain::State::PARKED);
            domain::Scooter scooter2=domain::Scooter("AAB","Vespa Primavera",{2021,11,20},800,"Old Town Square",domain::State::PARKED);
            domain::Scooter scooter3=domain::Scooter("AAC","Yamaha Nmax",{2022,03,15}, 1500,"City Hall",domain::State::PARKED);
            domain::Scooter scooter4=domain::Scooter("AAD","Piaggio Liberty",{2021,12,01},1000,"Main Street",domain::State::PARKED);
            domain::Scooter scooter5=domain::Scooter("AAE","Kymco Agility",{2022,02,25},900,"Shopping Mall",domain::State::PARKED);
            domain::Scooter scooter6=domain::Scooter("AAF","Suzuki Burgman",{2022,04,10},2000,"Airport",domain::State::PARKED);
            domain::Scooter scooter7=domain::Scooter("AAG","BMW C 650 GT",{2021,10,15},500,"Train Station",domain::State::PARKED);
            domain::Scooter scooter8=domain::Scooter("AAH","Aprilia SR Motard",{2022,05,05},300,"University Campus",domain::State::PARKED);
            domain::Scooter scooter9=domain::Scooter("AAI","SYM Jet",{2022,03,20},1200,"Beach",domain::State::PARKED);
            domain::Scooter scooter10=domain::Scooter("AAJ","Triumph Trident",{2022,01,20},700,"Park",domain::State::PARKED);
            scooters.push_back(scooter1);
            scooters.push_back(scooter2);
            scooters.push_back(scooter3);
            scooters.push_back(scooter4);
            scooters.push_back(scooter5);
            scooters.push_back(scooter6);
            scooters.push_back(scooter7);
            scooters.push_back(scooter8);
            scooters.push_back(scooter9);
            scooters.push_back(scooter10);
        }

    void RepositoryInMemory::addScooter(const domain::Scooter &scooter) {
        scooters.push_back(scooter);
    }

    void RepositoryInMemory::deleteScooter(const domain::Scooter &scooter_) {
        auto it = std::remove_if(scooters.begin(), scooters.end(), [&scooter_](const domain::Scooter &scooter) {
            return scooter.getID() == scooter_.getID();
        });
        if (it != scooters.end()) {
            scooters.erase(it, scooters.end());
        }
    }

    void RepositoryInMemory::updateScooter(const domain::Scooter &scooter) {
        for (auto &s: scooters) {
            if (s.getID() == scooter.getID()) {
                s.setModel(scooter.getModel());
                s.setCommissionDate(scooter.getCommissionDate());
                s.setMileage(scooter.getMileage());
                s.setLastStandPlace(scooter.getLastStandPlace());
                s.setState(scooter.getState());
                break;
            }
        }
    }

    std::vector<domain::Scooter> RepositoryInMemory::getScooters() const {
        return scooters;
    }

    RepositoryInFile::RepositoryInFile() {
        loadDataFromFile("scootersData.csv");
    }


    void RepositoryInFile::updateScooter(const domain::Scooter &scooter) {
        saveDataToFile("scootersData.csv");
    }



    void RepositoryInFile::addScooter(const domain::Scooter &scooter) {

    }

    std::vector<domain::Scooter> RepositoryInFile::getScooters() const {
        return loadDataFromFile("scootersData.csv");
    }

    void RepositoryInFile::deleteScooter(const domain::Scooter &scooter_) {
        std::vector<domain::Scooter> scooters= loadDataFromFile("scootersData.csv");
        auto it = std::remove_if(scooters.begin(), scooters.end(), [&scooter_](const domain::Scooter &scooter) {
            return scooter.getID() == scooter_.getID();
        });
        if (it != scooters.end()) {
            scooters.erase(it, scooters.end());
        }

    }


    std::vector<domain::Scooter> RepositoryInFile::loadDataFromFile(const std::string &fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening file: scootersData.csv" << std::endl;
            return {};
        }
        const std::unordered_map<std::string, domain::State> stateMap{
                {"PARKED",       domain::State::PARKED},
                {"RESERVED",     domain::State::RESERVED},
                {"INUSE",        domain::State::INUSE},
                {"INWAIT",       domain::State::INWAIT},
                {"OUTOFSERVICE", domain::State::OUTOFSERVICE}
        };

        std::vector<domain::Scooter> scooters;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, model, lastStandPlace, stateString;
            int year, month, day, mileage;

            std::getline(ss, id, ',');
            std::getline(ss, model, ',');
            ss >> year;
            ss.ignore();
            ss >> month;
            ss.ignore();
            ss >> day;
            ss.ignore();
            ss >> mileage;
            ss.ignore();
            std::getline(ss, lastStandPlace, ',');
            std::getline(ss, stateString, ',');

            domain::Date commissionDate{year, month, day};

            domain::State state = domain::State::PARKED;
            auto stateIt = stateMap.find(stateString);
            if (stateIt != stateMap.end()) {
                state = stateIt->second;
            }
            domain::Scooter scooter(id, model, commissionDate, mileage, lastStandPlace, state);
            scooters.push_back(scooter);
        }
        file.close();

        return scooters;
    }


    void RepositoryInFile::saveDataToFile(const std::string &fileName) const {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening file: scootersData.csv!"<< std::endl;
            return;
        }

        const std::unordered_map<domain::State, std::string> stateMap{
                {domain::State::PARKED,       "PARKED"},
                {domain::State::RESERVED,     "RESERVED"},
                {domain::State::INUSE,        "INUSE"},
                {domain::State::INWAIT,       "INWAIT"},
                {domain::State::OUTOFSERVICE, "OUTOFSERVICE"}
        };
        for (const auto &scooter: getScooters()) {
            file << scooter.getID() << "," << scooter.getModel() << ","
                 << std::setfill('0') << scooter.getCommissionDate().year << ","
                 << std::setfill('0') << scooter.getCommissionDate().month << ","
                 << std::setfill('0') << scooter.getCommissionDate().day << ","
                 << scooter.getMileage() << ","
                 << scooter.getLastStandPlace() << ","
                 << stateMap.at(scooter.getState()) << std::endl;
        }
        file.close();
    }

}












