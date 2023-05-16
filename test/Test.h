#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../controller/Controller.h"
#include "../repository/Repository.h"
#include "../domain/Domain.h"


class Test {
    public:
        void TestAdd();
        void TestRemove();
        void TestUpdate();
        void TestGet();
        void TestGetAll();
        void TestGetAllBy();
        void TestAll();
};
