//
// Created by Bilge Kaan Yildirim on 29.03.2024.
//

#ifndef HW3_UNDOSTACK_H
#define HW3_UNDOSTACK_H

#include <string>

using namespace std;

struct StackNode
{
    char operation;
    string employeeName;
    string projectName;
    int projectPriority;
    StackNode *next;

    // Default constructor
    StackNode()
    {}

    // Constructor with parameters
    StackNode(char opr, string empName, string projName, int projPriority, StackNode *n)
    {
        operation = opr;
        employeeName = empName;
        projectName = projName;
        projectPriority = projPriority;
        next = n;
    }
};

class UndoStack
{
private:
    StackNode *head;

public:
    UndoStack();
    void push(const char & operation, const string &employeeName, const string &projectName, const int &projectPriority);
    void pop(char &operation, string &employeeName, string &projectName, int &projectPriority);
    bool isEmpty();
    void clear();
};


#endif //HW3_UNDOSTACK_H
