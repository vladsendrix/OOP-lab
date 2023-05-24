//#include "Test.h"
//
//
//
//Test::Test() {
//    //this->scooters = std::make_shared<repository::Repository>();
//  //  this->scooters = std::make_shared<repository::Repository>();
//  //  this->controller = std::make_shared<controller::ProductController>();
//}
//
//
//void Test::TestAdd() {
//
//
//    assert(scooters->getScooters().empty());
//
//    std::string expectedID = "AAA", expectedModel = "Honda Activa", expectedLastStandPlace = "Central Station";
//    domain::Date expectedDate = {2022, 01, 05};
//    domain::State expectedState = domain::INWAIT;
//    int expectedMileage = 1200;
//
//    domain::Scooter newScooter = domain::Scooter("AAA", "Honda Activa", {2022, 01, 05}, 1200, "Central Station",
//                                                 domain::INWAIT);
//
//    scooters->addScooter(newScooter);
//
//    assert(expectedID == newScooter.getID());
//    assert(expectedModel == newScooter.getModel());
//    assert(expectedLastStandPlace == newScooter.getLastStandPlace());
//    assert(expectedMileage == newScooter.getMileage());
//    assert(expectedDate.year == newScooter.getCommissionDate().year);
//    assert(expectedDate.month == newScooter.getCommissionDate().month);
//    assert(expectedDate.day == newScooter.getCommissionDate().day);
//    assert(expectedState == newScooter.getState());
//
//
//    assert(scooters->getScooters().size() == 1);
//
//    expectedID = "AAB";
//    expectedModel = "BMW C 650 GT";
//    expectedLastStandPlace = "Train Station";
//    expectedDate = {2021, 10, 15};
//    expectedState = domain::INWAIT;
//    expectedMileage = 500;
//
//    newScooter = domain::Scooter("AAB", "BMW C 650 GT", {2021, 10, 15}, 500, "Train Station", domain::INWAIT);
//
//
//    assert(expectedID == newScooter.getID());
//    assert(expectedModel == newScooter.getModel());
//    assert(expectedLastStandPlace == newScooter.getLastStandPlace());
//    assert(expectedMileage == newScooter.getMileage());
//    assert(expectedDate.year == newScooter.getCommissionDate().year);
//    assert(expectedDate.month == newScooter.getCommissionDate().month);
//    assert(expectedDate.day == newScooter.getCommissionDate().day);
//    assert(expectedState == newScooter.getState());
//
//    scooters->addScooter(newScooter);
//
//    assert(scooters->getScooters().size() == 2);
//
//}
//
//
//void Test::TestRemove() {
//    assert(scooters->getScooters().size() == 2);
//    domain::Scooter newScooter = domain::Scooter("AAC", "Suzuki C 650 GT", {2021, 10, 15}, 500, "Train Station",
//                                                 domain::INWAIT);
//    scooters->deleteScooter(newScooter);
//    assert(scooters->getScooters().size() == 2);
//    newScooter = domain::Scooter("AAB", "BMW C 650 GT", {2021, 10, 15}, 500, "Train Station", domain::INWAIT);
//    scooters->deleteScooter(newScooter);
//    assert(scooters->getScooters().size() == 1);
//}
//
//void Test::TestUpdate() {
//    assert(scooters->getScooters().size() == 1);
//    domain::Scooter newScooter = domain::Scooter("AAA", "Suzuki C 650 GT", {2023, 05, 17}, 1000, "Kaufland",
//                                                 domain::PARKED);
//
//    std::string expectedID = "AAA", expectedModel = "Suzuki C 650 GT", expectedLastStandPlace = "Kaufland";
//    domain::Date expectedDate = {2023, 05, 17};
//    domain::State expectedState = domain::PARKED;
//    int expectedMileage = 1000;
//
//    scooters->updateScooter(newScooter);
//
//    assert(scooters->getScooters().size() == 1);
//
//    domain::Scooter result = scooters->getScooters().at(0);
//
//    assert(expectedID == result.getID());
//    assert(expectedModel == result.getModel());
//    assert(expectedLastStandPlace == result.getLastStandPlace());
//    assert(expectedMileage == result.getMileage());
//    assert(expectedDate.year == result.getCommissionDate().year);
//    assert(expectedDate.month == result.getCommissionDate().month);
//    assert(expectedDate.day == result.getCommissionDate().day);
//    assert(expectedState == result.getState());
//
//
//}
//
//void Test::TestAll() {
//    TestAdd();
//    TestRemove();
//    TestUpdate();
//    std::cout << "Tests successfully passed!\n" << std::endl;
//}
