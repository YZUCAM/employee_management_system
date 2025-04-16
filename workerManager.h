#pragma once
#include <iostream>
#include <string>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
using namespace std;

#define FILENAME "empFile.txt"

class WorkerManager
{
public:

    WorkerManager();

    void showMenu();
    void exitSystem();

    // record member number
    int m_empNum;
    Worker** m_pptrArray;
    bool m_FileIsEmpty;

    void add_Emp();
    void save();
    int get_empNum();
    void init_emp();

    ~WorkerManager();
};