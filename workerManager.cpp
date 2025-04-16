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

void WorkerManager::show_emp()
{
    //check file if empty
    if (this->m_FileIsEmpty)
    {
        cout << "No employee records." << endl; 
    } 
    else
    {
        for (int i = 0; i < this->m_empNum; i++)
        {
            // use polymorphism of each type of employee
            this->m_pptrArray[i]->showInfo();
        }
    }   
    cout << "Press Enter to continue" << endl;
    cin.ignore(1, '\n');
    cin.get();
    system("clear");    
}

int WorkerManager::isExist(int id)
{
    int idx = -1;
    for (int i=0; i<this->m_empNum; i++)
    {
        if (this->m_pptrArray[i]->m_ID == id)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

void WorkerManager::del_emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "No records exist." << endl;
    }
    else
    {
        int id = 0;
        cout << "Please enter the employee ID to delete: " << endl;
        cin >> id;

        int idx = this->isExist(id);
        if (idx != -1)
        {
            // logical delete, data move backwards
            for (int i = idx; i < this->m_empNum-1; i++)
            {
                this->m_pptrArray[i] = this->m_pptrArray[i+1];
            }
            this->m_empNum--;
            this->save();
            cout << "Delete success." << endl;
        } 
        else
        {
            cout << "Delete failed, the employee is not found." << endl;
        }
    }
    cout << "Press Enter to continue" << endl;
    cin.ignore(1, '\n');
    cin.get();
    system("clear");   
}

void WorkerManager::update_emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "No records exist." << endl;
    }
    else
    {
        int id = 0;
        cout << "Please enter the employee ID to update : " << endl;
        cin >> id;

        int idx = this->isExist(id);
        if (idx != -1)
        {
            delete this->m_pptrArray[idx];
            
            int new_id = 0;
            string new_name = "";
            int new_depID = 0;

            cout << "Record has been found for id: " << id << endl;
            cout << "Please enter the employee new id: " << endl;
            cin >> new_id;
            cout << "Please enter the employee new name: " << endl;
            cin >> new_name;
            cout << "Please select the employee new department: " << endl;
            cout << "1. Employee. " << endl;
            cout << "2. Manager. " << endl;
            cout << "3. Boss.    " << endl;
            cin >> new_depID;  

            Worker* worker = NULL;
            switch(new_depID)
            {
            case 1:
                worker = new Employee(new_id, new_name, 1);
                break;
            case 2:
                worker = new Manager(new_id, new_name, 2);
                break;
            case 3:
                worker = new Boss(new_id, new_name, 3);
                break;
            default:
                break; 
            } 
            this->m_pptrArray[idx] = worker;
             
            cout << "Update  success." << endl;
            this->save(); 
        } 
        else
        {
            cout << "Update failed, the employee is not found." << endl;
        }
    } 
    cout << "Press Enter to continue" << endl;
    cin.ignore(1, '\n');
    cin.get();
    system("clear");   
}

void WorkerManager::find_emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "No records exist." << endl;
    }
    else
    {
         cout << "Select by ID, input 1" << endl;
         cout << "Select by name, input 2" << endl;
         int select = 0;
         cin >> select;
         
         if (select == 1)
         {
            // by ID
            int id;
            cout << "Please input search ID: " << endl;
            cin >> id;
            
            int idx = this->isExist(id);

            if (idx != -1)
            {
                cout << "Search success, the info is listed below: " << endl;
                this->m_pptrArray[idx]->showInfo();  
            }
            else
            {
                cout << "Search failed" << endl;
            }
 
         }
         else if (select ==2)
         {
            // by name
            string name;
            cout << "Please input search name: " << endl;
            cin >> name;

            bool flag = false;

            for (int i=0; i<this->m_empNum; i++)
            {
                if (this->m_pptrArray[i]->m_Name == name)
                {
                    cout << "Search success, the info of employee ID: " << this->m_pptrArray[i]->m_ID
                    << " listed below: " << endl;
                    this->m_pptrArray[i]->showInfo();
                    flag =true;
                }
                if (!flag)
                {
                    cout << "Search failed" << endl;
                }
            }
         }
         else
         {
            cout << "Invalid input" << endl;
         }
    }
    cout << "Press Enter to continue" << endl;
    cin.ignore(1, '\n');
    cin.get();
    system("clear"); 
}

void WorkerManager::sort_emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "No records exist." << endl;
        cout << "Press Enter to continue" << endl;
        cin.ignore(1, '\n');
        cin.get();
        system("clear"); 
    }
    else
    {
        cout << "Sort by ID ascend, input 1" << endl;
        cout << "Select by ID descend, input 2" << endl;
        int select = 0;
        cin >> select;

        for (int i = 0; i < this->m_empNum; i++)
        {
            int minormax = i;
            for (int j = i+1; j < this->m_empNum; j++)
            {
                 if (select == 1) //ascend
                 {
                    if (this->m_pptrArray[minormax]->m_ID > this->m_pptrArray[j]->m_ID)
                    {
                        minormax = j;
                    }
                }
                else //descend  
                {
                    if (this->m_pptrArray[minormax]->m_ID < this->m_pptrArray[j]->m_ID)
                    {
                        minormax = j;
                    }
                } 
            }
            if (minormax != i)
            {
                 Worker* temp = this->m_pptrArray[i];
                 this->m_pptrArray[i] = this->m_pptrArray[minormax]; 
                 this->m_pptrArray[minormax] = temp;
            }
        }

        this->save(); 
        cout << "Sort success, the sorted results: " << endl;
        this->show_emp(); 
    }
}

void WorkerManager::clear_emp()
{
    cout << "clear record confirm?" << endl;
    cout << "1. confirm." << endl;
    cout << "2. Decline." << endl;
    int select =  0;
    cin >> select;

    if (select == 1)
    {
        //clear
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc); //clear and recreate
        ofs.close(); 

        if (this->m_pptrArray != NULL)
        {
            for (int i = 0; i < this->m_empNum; i++)
            {
                delete this->m_pptrArray[i];
                this->m_pptrArray[i] = NULL; 
            }
            delete [] this->m_pptrArray;
            this->m_pptrArray = NULL;
            this->m_empNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "clear records success, all records deleted." << endl;  
    }
    cin.ignore(1, '\n');
    cin.get();
    system("clear"); 
}

WorkerManager::~WorkerManager()
{
    if (this->m_pptrArray != NULL)
    {
        for (int i = 0; i < this->m_empNum; i++)
            {
                delete this->m_pptrArray[i];
                this->m_pptrArray[i] = NULL; 
            }
        delete [] this->m_pptrArray;
        this->m_pptrArray = NULL;
    }
}