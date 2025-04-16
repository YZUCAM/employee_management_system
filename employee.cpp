#include "employee.h"

Employee::Employee(int id, string name, int depId)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = depId;
}
 
void Employee::showInfo()
{
    cout << "Employee ID: " << this->m_ID
        << " \t Employee Name: " << this->m_Name
        << " \t Department: " << this->getDeptName() << endl; 
}


string Employee::getDeptName()
{
    return string("Employee");
}