#include "Test.h"

Test::Test() {
    this->scooters = std::make_shared<repository::RepositoryInMemory>();
    assert(scooters->getScooters("dbAdmin").size() == 10);
}

void Test::TestRemove() {
    assert(scooters->getScooters("dbAdmin").size() == 10);
    domain::Scooter newScooter = domain::Scooter("AAE", "Kymco Agility", {2022, 02, 25}, 900, "Shopping Mall",
                                                 domain::State::PARKED);
    scooters->deleteScooter(newScooter, "dbAdmin");
    assert(scooters->getScooters("dbAdmin").size() == 9);
    newScooter = domain::Scooter("AAJ", "Triumph Trident", {2022, 01, 20}, 700, "Park",
                                 domain::State::PARKED);
    scooters->deleteScooter(newScooter, "dbAdmin");
    assert(scooters->getScooters("dbAdmin").size() == 8);

    newScooter = domain::Scooter("AAA", "Honda Activa", {2022, 01, 05}, 1200, "Central Station",
                                 domain::State::PARKED);
    scooters->deleteScooter(newScooter, "dbAdmin");
    assert(scooters->getScooters("dbAdmin").size() == 7);

    while (!scooters->getScooters("dbAdmin").empty()) {
        scooters->deleteScooter(scooters->getScooters("dbAdmin").at(0), "dbAdmin");
    }

    assert(scooters->getScooters("dbAdmin").empty());
}

void Test::TestAdd() {

    assert(scooters->getScooters("dbAdmin").empty());

    std::string expectedID = "AAA", expectedModel = "Honda Activa", expectedLastStandPlace = "Central Station";
    domain::Date expectedDate = {2022, 01, 05};
    domain::State expectedState = domain::PARKED;
    int expectedMileage = 1200;

    domain::Scooter newScooter = domain::Scooter("AAA", "Honda Activa", {2022, 01, 05}, 1200, "Central Station",
                                                 domain::PARKED);

    scooters->addScooter(newScooter, "dbAdmin");

    assert(expectedID == newScooter.getID());
    assert(expectedModel == newScooter.getModel());
    assert(expectedLastStandPlace == newScooter.getLastStandPlace());
    assert(expectedMileage == newScooter.getMileage());
    assert(expectedDate.year == newScooter.getCommissionDate().year);
    assert(expectedDate.month == newScooter.getCommissionDate().month);
    assert(expectedDate.day == newScooter.getCommissionDate().day);
    assert(expectedState == newScooter.getState());

    assert(scooters->getScooters("dbAdmin").size() == 1);

    expectedID = "AAB";
    expectedModel = "Vespa Primavera";
    expectedLastStandPlace = "Old Town Square";
    expectedDate = {2021, 11, 20};
    expectedState = domain::PARKED;
    expectedMileage = 800;

    newScooter = domain::Scooter("AAB", "Vespa Primavera", {2021, 11, 20}, 800, "Old Town Square", domain::PARKED);

    assert(expectedID == newScooter.getID());
    assert(expectedModel == newScooter.getModel());
    assert(expectedLastStandPlace == newScooter.getLastStandPlace());
    assert(expectedMileage == newScooter.getMileage());
    assert(expectedDate.year == newScooter.getCommissionDate().year);
    assert(expectedDate.month == newScooter.getCommissionDate().month);
    assert(expectedDate.day == newScooter.getCommissionDate().day);
    assert(expectedState == newScooter.getState());

    scooters->addScooter(newScooter, "dbAdmin");

    assert(scooters->getScooters("dbAdmin").size() == 2);
}

void Test::TestUpdate() {

    assert(scooters->getScooters("dbAdmin").size() == 2);
    domain::Scooter newScooter = domain::Scooter("AAA", "Suzuki C 650 GT", {2023, 05, 17}, 1000, "Kaufland",
                                                 domain::PARKED);

    std::string expectedID = "AAA", expectedModel = "Suzuki C 650 GT", expectedLastStandPlace = "Kaufland";
    domain::Date expectedDate = {2023, 05, 17};
    domain::State expectedState = domain::PARKED;
    int expectedMileage = 1000;

    scooters->updateScooter(newScooter);

    assert(scooters->getScooters("dbAdmin").size() == 2);

    domain::Scooter result = scooters->getScooters("dbAdmin").at(0);

    assert(expectedID == result.getID());
    assert(expectedModel == result.getModel());
    assert(expectedLastStandPlace == result.getLastStandPlace());
    assert(expectedMileage == result.getMileage());
    assert(expectedDate.year == result.getCommissionDate().year);
    assert(expectedDate.month == result.getCommissionDate().month);
    assert(expectedDate.day == result.getCommissionDate().day);
    assert(expectedState == result.getState());
}

void Test::TestAll() {
    TestRemove();
    TestAdd();
    TestUpdate();
    std::cout << "Tests successfully passed!\n" << std::endl;
}
