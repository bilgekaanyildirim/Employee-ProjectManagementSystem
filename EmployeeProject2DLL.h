//
// Created by Bilge Kaan Yildirim on 29.03.2024.
//

#ifndef HW3_EMPLOYEEPROJECT2DLL_H
#define HW3_EMPLOYEEPROJECT2DLL_H

#include <string>

using namespace std;

struct ProjectNode
{
    string projectName;
    int projectPriority;
    ProjectNode *next;
    ProjectNode *prev;

    // Default Constructor
    ProjectNode()
    {
        next = nullptr;
        prev = nullptr;
    }

    // Constructor with parameters
    ProjectNode(string projName, int projPriority, ProjectNode *n, ProjectNode *p)
    {
        projectName = projName;
        projectPriority = projPriority;
        next = n;
        prev = p;
    }
};

struct EmployeeNode
{
    string employeeName;
    ProjectNode *head;
    ProjectNode *tail;
    EmployeeNode *down;

    // Default Constructor
    EmployeeNode()
    {
        head = nullptr;
        tail = nullptr;
        down = nullptr;
    }

    // Constructor with parameters
    EmployeeNode(string empName, ProjectNode *h, ProjectNode *t, EmployeeNode *d)
    {
        employeeName = empName;
        head = h;
        tail = t;
        down = d;
    }
};

class EmployeeProject2DLL
{
private:
    EmployeeNode *head;
    bool assignProjectToEmployee(EmployeeNode *&node, const string &employeeName, const string &projectName, const int &projectPriority);
    void insertNewEmployeeWithProject(EmployeeNode *&ptr, const string &employeeName, const string &projectName, const int &projectPriority);
    void findEmployee(const string &employeeName, EmployeeNode *&empPtr);
    bool withdrawProjectFromEmployee(EmployeeNode *&node, const string &projectName, int &projectPriority);
    bool withdrawProjectFromEmployeeForUpdate(EmployeeNode *&node, const string &projectName, int &projectPriority);
    void withdrawEmployeeFromProjectForUpdate(const string &employeeName, const string &projectName, int &projectPriority);
    bool assignProjectToEmployeeForUpdate(EmployeeNode *&node, const string &employeeName, const string &projectName, const int &projectPriority);

public:
    EmployeeProject2DLL();
    bool isEmployeeAssignedToProject(const string &employeeName, const string &projectName);
    bool updateProjectPriority(const string &employeeName, const string &projectName, int &projectPriority);
    bool assignEmployeeToProject(const string &employeeName, const string &projectName, const int &projectPriority);
    void withdrawEmployeeFromProject(const string &employeeName, const string &projectName, int &projectPriority);
    void printTheEntireList() const;
    void printEmployeeProjects(const string &employeeName, const int &opt);
    void undo(const char &oprType, const string &employeeName, const string &projectName, int projectPriority);
    void clear();

};


#endif //HW3_EMPLOYEEPROJECT2DLL_H
