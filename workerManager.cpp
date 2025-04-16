#include "workerManager.h"

WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        //cout << "File doesn't exist." << endl;
        this->m_empNum = 0; 
        this->m_pptrArray = NULL; 
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // confirm file exist but it is empty
        //cout << "File exist but it is empty." << endl;
        this->m_empNum = 0; 
        this->m_pptrArray = NULL; 
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    int num = this->get_empNum();
    //cout << "Empolyee number is " << num << endl;
    this->m_empNum = num;
    this->m_pptrArray = new Worker* [this->m_empNum];
    this->init_emp();

    // for (int i = 0; i < this->m_empNum; i++)
    // {
    //     cout << "ID: " << this->m_pptrArray[i]->m_ID << " " 
    //         << "Name: " << this->m_pptrArray[i]->m_Name << " "
    //         <<"Dep: " << this->m_pptrArray[i]->m_DeptID << " " << endl;
    // }
}

void WorkerManager::showMenu()
{
    cout << "******************************************" << endl;
    cout << "*           Employee Manager             *" << endl;
    cout << "******************************************" << endl;
    cout << "*    1. Add Employee                     *" << endl;
    cout << "*    2. List Employees                   *" << endl;
    cout << "*    3. Search Employee by ID            *" << endl;
    cout << "*    4. Remove Employee                  *" << endl;
    cout << "*    5. Update Employee Info             *" << endl;
    cout << "*    6. Sort Employees by Index          *" << endl;
    cout << "*    7. Clear All Record                 *" << endl;
    cout << "*    0. Exit                             *" << endl;
    cout << "******************************************" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

void WorkerManager::exitSystem()
{
    cout << "System closed." << endl;
    cout << "Press Enter to continue...";
    cin.ignore(1, '\n');
    cin.get();
    exit(0);
}

void WorkerManager::add_Emp()
{
   cout << "Please enter number of employee need to be added: " << endl;
   int addNum = 0;
   cin >> addNum;

   if (addNum > 0)
   {
        // add
        // record new size 
        int newSize = this->m_empNum + addNum;
        Worker** newSpace = new Worker* [newSize];

        // pass old data to new space if it is
        if (this->m_empNum != 0)
        {
            for (int i=0; i<this->m_empNum; i++)
            {
                newSpace[i] = this->m_pptrArray[i];
            }
        }

        // batch add new records
        for (int i=0; i<addNum; i++)
        {
            int id;
            string name;
            int selectDep;
            cout << "Please enter " << i+1 << "-th employee id: " << endl;
            cin >> id;
            cout << "Please enter " << i+1 << "-th employee name: " << endl;
            cin >> name;
            cout << "Please select this employee department: " << endl;
            cout << "1. Employee. " << endl;
            cout << "2. Manager. " << endl;
            cout << "3. Boss.    " << endl;
            cin >> selectDep;
            
            Worker* worker = NULL;
            switch(selectDep)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break; 
            }
            newSpace[this->m_empNum + i] = worker;
        }
        // release original heap space
        delete [] this->m_pptrArray;
        this->m_pptrArray = newSpace;

        // update new employee number
        this->m_empNum = newSize;
        this->m_FileIsEmpty = false;
        cout << "Add success. Adding " << addNum << " employees" << endl;
        this->save();
    }
    else
    {
        cout << "Enter value error" << endl;
    }
    // clear screen and back to previous menu
    cout << "Press Enter to continue" << endl;
    cin.ignore(1, '\n');
    cin.get();
    system("clear");
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_empNum; i++)
    {
        ofs << this->m_pptrArray[i]->m_ID << " " 
            << this->m_pptrArray[i]->m_Name << " "
            << this->m_pptrArray[i]->m_DeptID << " " << endl;
    }
    ofs.close();
}

int WorkerManager::get_empNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int depID;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> depID)
    {
        num++;
    }
    return num;

}

void WorkerManager::init_emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int depID;
    int num = 0;
    int idx = 0;
    while (ifs >> id && ifs >> name && ifs >> depID)
    {
        Worker* worker = NULL;
        if (depID == 1)
        {
            worker = new Employee(id, name, depID);
        }
        else if(depID == 2)
        {
            worker = new Manager(id, name, depID);
        }
        else if(depID == 3)
        {
            worker = new Boss(id, name, depID);
        }
        this->m_pptrArray[idx] = worker;
        idx++;
    }
    ifs.close();
}

WorkerManager::~WorkerManager()
{
    if (this->m_pptrArray != NULL)
    {
        delete [] this->m_pptrArray;
        this->m_pptrArray = NULL;
    }
}