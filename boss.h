#pragma once
#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class Boss : public Worker
{
public:

    Boss(int id, string name, int depId);
    virtual void showInfo();
    virtual string getDeptName();
};