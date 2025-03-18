//
// Created by Bilge Kaan Yildirim on 29.03.2024.
//

#include "EmployeeProject2DLL.h"

#include <iostream>


EmployeeProject2DLL::EmployeeProject2DLL()
{
    head = nullptr;
}

bool EmployeeProject2DLL::isEmployeeAssignedToProject(const string &employeeName, const string &projectName)
{
    if (head == nullptr)
    {
        return false;
    }
    else
    {
        EmployeeNode *empPtr = head;

        while (empPtr != nullptr)
        {
            if (empPtr->employeeName == employeeName)
            {
                ProjectNode *projPtr = empPtr->head;

                while (projPtr != nullptr)
                {
                    if (projPtr->projectName == projectName)
                    {
                        return true;
                    }
                    projPtr = projPtr->next;
                }
                return false;
            }
            empPtr = empPtr->down;
        }
    }
    return false;
}

bool EmployeeProject2DLL::updateProjectPriority(const string &employeeName, const string &projectName, int &projectPriority)
{
    EmployeeNode *empPtr;

    findEmployee(employeeName, empPtr);

    if(assignProjectToEmployeeForUpdate(empPtr, employeeName, projectName, projectPriority))
    {
        withdrawEmployeeFromProjectForUpdate(employeeName, projectName, projectPriority);
        return true;
    }
    else
    {
        return false;
    }
}

bool EmployeeProject2DLL::assignEmployeeToProject(const string &employeeName, const string &projectName, const int &projectPriority)
{
    bool check;

    if (head == nullptr)
    {
        insertNewEmployeeWithProject(head, employeeName, projectName, projectPriority);
        return true;
    }
    else
    {
        // If the first employee name is bigger than param employee name
        if (head->employeeName > employeeName)
        {
            insertNewEmployeeWithProject(head, employeeName, projectName, projectPriority);
            return true;
        }
        // If the first employee name equal to param employee name
        else if (head->employeeName == employeeName)
        {
            check = assignProjectToEmployee(head, employeeName, projectName, projectPriority);
            if (!check)
            {
                cout << "The project has not been added because there is another project with the same priority." << endl;
            }
            return check;
        }
        // Look other nodes
        else
        {
            EmployeeNode *empPtr = head;

            while (empPtr->down != nullptr)
            {
                // If next employee name equal to param one
                if (empPtr->down->employeeName == employeeName)
                {
                    check = assignProjectToEmployee(empPtr->down, employeeName, projectName, projectPriority);
                    if (!check)
                    {
                        cout << "The project has not been added because there is another project with the same priority." << endl;
                    }
                    return check;
                }
                // If next employee name smaller than param one
                else if (empPtr->down->employeeName > employeeName)
                {
                    insertNewEmployeeWithProject(empPtr->down, employeeName, projectName, projectPriority);
                    return true;
                }
                empPtr = empPtr->down;
            }
            // Insert it as the last one
            insertNewEmployeeWithProject(empPtr->down, employeeName, projectName, projectPriority);
            return true;
        }
    }
}

void EmployeeProject2DLL::withdrawEmployeeFromProject(const string &employeeName, const string &projectName, int &projectPriority)
{
    // If the employee is in the beginning
    if (head->employeeName == employeeName)
    {
        if (!withdrawProjectFromEmployee(head, projectName, projectPriority))
        {
            EmployeeNode *temp = head;
            head = head->down;
            delete temp;
        }
    }
    else
    {
        EmployeeNode *empPtr = head;

        while (empPtr->down != nullptr)
        {
            if (empPtr->down->employeeName == employeeName)
            {
                if (!withdrawProjectFromEmployee(empPtr->down, projectName, projectPriority))
                {
                    EmployeeNode *temp = empPtr->down;
                    empPtr->down = empPtr->down->down;
                    delete temp;
                    return;
                }
                return;
            }
            empPtr = empPtr->down;
        }
        if (!withdrawProjectFromEmployee(empPtr, projectName, projectPriority))
        {
            delete empPtr->down;
            empPtr->down = nullptr;
        }
    }
}

void EmployeeProject2DLL::printTheEntireList() const
{
    if (head != nullptr)
    {
        EmployeeNode *empPtr = head;

        while (empPtr != nullptr)
        {
            cout << empPtr->employeeName << ": ";

            ProjectNode *projPtr = empPtr->head;

            while (projPtr != nullptr)
            {
                cout << "(" << projPtr->projectName << ", " << projPtr->projectPriority << ") ";
                projPtr = projPtr->next;
            }
            cout << endl;

            empPtr = empPtr->down;
        }
    }
    else
    {
        cout << "The list is empty." << endl;
    }
}

void EmployeeProject2DLL::printEmployeeProjects(const string &employeeName, const int &opt)
{
    if (head == nullptr)
    {
        cout << "There are no employees in the list." << endl;
        return;
    }

    EmployeeNode *empPtr;

    findEmployee(employeeName, empPtr);

    if (empPtr == nullptr)
    {
        cout << "The employee is not in the list." << endl;
        return;
    }

    if (opt == 1)
    {
        ProjectNode *projPtr = empPtr->head;

        while (projPtr != nullptr)
        {
            cout << "(" << projPtr->projectName << ", " << projPtr->projectPriority << ") ";
            projPtr = projPtr->next;
        }
        cout << endl;
    }
    else if (opt == 0)
    {
        ProjectNode *projPtr = empPtr->tail;

        while (projPtr != nullptr)
        {
            cout << "(" << projPtr->projectName << ", " << projPtr->projectPriority << ") ";
            projPtr = projPtr->prev;
        }
        cout << endl;
    }
}

void EmployeeProject2DLL::undo(const char &oprType, const string &employeeName, const string &projectName, int projectPriority)
{
    if (oprType == 'a')
    {
        cout << "Undoing the assignment of a project." << endl;
        withdrawEmployeeFromProject(employeeName, projectName, projectPriority);
    }
    else if (oprType == 'w')
    {
        cout << "Undoing the withdrawal of a project." << endl;
        assignEmployeeToProject(employeeName, projectName, projectPriority);
    }
    else if (oprType == 'u')
    {
        cout << "Undoing the update of a project priority." << endl;

        updateProjectPriority(employeeName, projectName, projectPriority);
    }
}

void EmployeeProject2DLL::clear()
{
    EmployeeNode *empTemp;
    ProjectNode *projTemp;

    while (head != nullptr)
    {
        while (head->head != nullptr)
        {
            projTemp = head->head;
            head->head = head->head->next;
            delete projTemp;
        }
        empTemp = head;
        head = head->down;
        delete empTemp;
    }
}

bool EmployeeProject2DLL::assignProjectToEmployee(EmployeeNode *&node, const string &employeeName, const string &projectName, const int &projectPriority)
{
    ProjectNode *projPtr = node->head;

    if (projPtr->projectPriority > projectPriority)
    {
        ProjectNode *temp = new ProjectNode(projectName, projectPriority, projPtr, nullptr);
        node->head = temp;
        projPtr->prev = temp;
        return true;
    }
    else if (projPtr->projectPriority == projectPriority)
    {
        return false;
    }
    else
    {
        while (projPtr->next != nullptr)
        {
            if (projPtr->next->projectPriority > projectPriority)
            {
                ProjectNode *temp = new ProjectNode(projectName, projectPriority, projPtr->next, projPtr);
                projPtr->next->prev = temp;
                projPtr->next = temp;
                return true;
            }
            else if (projPtr->next->projectPriority == projectPriority)
            {
                return false;
            }
            projPtr = projPtr->next;
        }
        // Insert it as the last one
        projPtr->next = new ProjectNode(projectName, projectPriority, nullptr, projPtr);
        node->tail = projPtr->next;
        return true;
    }
}

void EmployeeProject2DLL::insertNewEmployeeWithProject(EmployeeNode *&ptr, const string &employeeName, const string &projectName, const int &projectPriority)
{
    EmployeeNode *temp = ptr;
    ptr = new EmployeeNode(employeeName, nullptr, nullptr, temp);
    ptr->head = new ProjectNode(projectName, projectPriority, nullptr, nullptr);
    ptr->tail = ptr->head;
}

void EmployeeProject2DLL::findEmployee(const string &employeeName, EmployeeNode *&empPtr)
{
    empPtr = head;

    while (empPtr != nullptr && empPtr->employeeName != employeeName)
    {
        empPtr = empPtr->down;
    }
}

// delete the project node if it is not the only project and returns true else false
bool EmployeeProject2DLL::withdrawProjectFromEmployee(EmployeeNode *&node, const string &projectName, int &projectPriority)
{
    ProjectNode *projPtr = node->head;

    // If the project that is withdrawn is not the only project
    if (projPtr->next != nullptr)
    {
        // If the project that withdrawn is in the beginning
        if (projPtr->projectName == projectName)
        {
            projPtr->next->prev = nullptr;
            projectPriority = projPtr->projectPriority;
            node->head = projPtr->next;
            delete projPtr;
        }
        // If the project that is withdrawn is not in the beginning
        else
        {
            while (projPtr->next->next != nullptr)
            {
                if (projPtr->next->projectName == projectName)
                {
                    ProjectNode *temp = projPtr->next;
                    projectPriority = projPtr->next->projectPriority;
                    projPtr->next = projPtr->next->next;
                    projPtr->next->prev = projPtr;
                    delete temp;
                    return true;
                }
                projPtr = projPtr->next;
            }
            ProjectNode *temp = projPtr->next;
            projectPriority = projPtr->next->projectPriority;
            projPtr->next = projPtr->next->next;
            node->tail = projPtr;
            delete temp;
            return true;
        }
        return true;
    }
    // If the project that is withdrawn is the only project
    else
    {
        projectPriority = projPtr->projectPriority;
        delete projPtr;
        return false;
    }
}

bool EmployeeProject2DLL::withdrawProjectFromEmployeeForUpdate(EmployeeNode *&node, const string &projectName, int &projectPriority)
{
    ProjectNode *projPtr = node->head;

    // If the project that is withdrawn is not the only project
    if (projPtr->next != nullptr)
    {
        // If the project that withdrawn is in the beginning
        if (projPtr->projectName == projectName && projPtr->projectPriority != projectPriority)
        {
            projPtr->next->prev = nullptr;
            projectPriority = projPtr->projectPriority;
            node->head = projPtr->next;
            delete projPtr;
        }
            // If the project that is withdrawn is not in the beginning
        else
        {
            while (projPtr->next->next != nullptr)
            {
                if (projPtr->next->projectName == projectName && projPtr->next->projectPriority != projectPriority)
                {
                    ProjectNode *temp = projPtr->next;
                    projectPriority = projPtr->next->projectPriority;
                    projPtr->next = projPtr->next->next;
                    projPtr->next->prev = projPtr;
                    delete temp;
                    return true;
                }
                projPtr = projPtr->next;
            }
            ProjectNode *temp = projPtr->next;
            projectPriority = projPtr->next->projectPriority;
            projPtr->next = projPtr->next->next;
            node->tail = projPtr;
            delete temp;
            return true;
        }
        return true;
    }
        // If the project that is withdrawn is the only project
    else
    {
        delete projPtr;
        return false;
    }
}

void EmployeeProject2DLL::withdrawEmployeeFromProjectForUpdate(const string &employeeName, const string &projectName, int &projectPriority)
{
    // If the employee is in the beginning
    if (head->employeeName == employeeName)
    {
        if (!withdrawProjectFromEmployeeForUpdate(head, projectName, projectPriority))
        {
            EmployeeNode *temp = head;
            head = head->down;
            delete temp;
        }
    }
    else
    {
        EmployeeNode *empPtr = head;

        while (empPtr->down != nullptr)
        {
            if (empPtr->down->employeeName == employeeName)
            {
                if (!withdrawProjectFromEmployeeForUpdate(empPtr->down, projectName, projectPriority))
                {
                    EmployeeNode *temp = empPtr->down;
                    empPtr->down = empPtr->down->down;
                    delete temp;
                    return;
                }
                return;
            }
            empPtr = empPtr->down;
        }
        if (!withdrawProjectFromEmployeeForUpdate(empPtr, projectName, projectPriority))
        {
            delete empPtr->down;
            empPtr->down = nullptr;
        }
    }
}

bool EmployeeProject2DLL::assignProjectToEmployeeForUpdate(EmployeeNode *&node, const string &employeeName, const string &projectName, const int &projectPriority)
{
    ProjectNode *projPtr = node->head;

    if (projPtr->projectPriority > projectPriority)
    {
        ProjectNode *temp = new ProjectNode(projectName, projectPriority, projPtr, nullptr);
        node->head = temp;
        projPtr->prev = temp;
        return true;
    }
    else if (projPtr->projectPriority == projectPriority)
    {
        if (projPtr->projectName == projectName)
        {
            cout << "The project priority is already the same as the new priority." << endl;
        }
        else
        {
            cout << "The project priority has not been updated because there is another project with the same priority." << endl;
        }
        return false;
    }
    else
    {
        while (projPtr->next != nullptr)
        {
            if (projPtr->next->projectPriority > projectPriority)
            {
                ProjectNode *temp = new ProjectNode(projectName, projectPriority, projPtr->next, projPtr);
                projPtr->next->prev = temp;
                projPtr->next = temp;
                return true;
            }
            else if (projPtr->next->projectPriority == projectPriority)
            {
                if (projPtr->next->projectName == projectName)
                {
                    cout << "The project priority is already the same as the new priority." << endl;
                }
                else
                {
                    cout << "The project priority has not been updated because there is another project with the same priority." << endl;
                }
                return false;
            }
            projPtr = projPtr->next;
        }
        // Insert it as the last one
        projPtr->next = new ProjectNode(projectName, projectPriority, nullptr, projPtr);
        node->tail = projPtr->next;
        return true;
    }
}
