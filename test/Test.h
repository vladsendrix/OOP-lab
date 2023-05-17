#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "../controller/Controller.h"
#include "../repository/Repository.h"
#include "../domain/Domain.h"


class Test {
private:
    std::shared_ptr<repository::Repository> scooters;
    std::shared_ptr<controller::ProductController> controller;
public:
    Test();

    void TestAdd();

    void TestRemove();

    void TestUpdate();

    void TestAll();
};
