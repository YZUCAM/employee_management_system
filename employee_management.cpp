#include <iostream>
#include "workerManager.h"
// #include "worker.h"
// #include "employee.h"
// #include "manager.h"
// #include "boss.h"
using namespace std;

int main(){

    // // test code
    // Worker* worker = NULL;
    // worker = new Employee(1, "James", 1);
    // worker->showInfo(); 
    // delete worker;

    // worker = new Manager(2, "Bob", 2);
    // worker->showInfo(); 
    // delete worker;

    // worker = new Boss(3, "Yi", 3    );
    // worker->showInfo(); 
    // delete worker;

    WorkerManager wm;

    int choice = 0;

    while (true)
    {
        wm.showMenu();
        cin >> choice;

        switch(choice)
        {
            case 0:     // exit system
                wm.exitSystem();
                break;
            case 1:     // add employee 
                wm.add_Emp();
                break;
            case 2:     // list employee
                wm.show_emp();
                break;
            case 3:     // search Employee
                wm.find_emp();
                break;
            case 4:     // remove Employee
                wm.del_emp();
                break;
            case 5:     // update Employee Info
                wm.update_emp();
                break;
            case 6:     // sort Employee
                wm.sort_emp();
                break;
            case 7:     // clear Employee
                wm.clear_emp();
                break;
            default:
                system("clear");
        }

    }
    
    cin.ignore();   
    return 0;
}



