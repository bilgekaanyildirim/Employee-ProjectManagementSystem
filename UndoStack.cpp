//
// Created by Bilge Kaan Yildirim on 29.03.2024.
//

#include "UndoStack.h"
#include <iostream>

using namespace std;

UndoStack::UndoStack()
{
    head = nullptr;
}

void UndoStack::push(const char &operation, const string &employeeName, const string &projectName, const int &projectPriority)
{
    StackNode *ptr = new StackNode(operation, employeeName, projectName, projectPriority, nullptr);

    ptr->next = head;
    head = ptr;
}

void UndoStack::pop(char &operation, string &employeeName, string &projectName, int &projectPriority)
{
    if (isEmpty())
    {
        cout << "The undo stack is empty." << endl;
    }
    else
    {
        operation = head->operation;
        employeeName = head->employeeName;
        projectName = head->projectName;
        projectPriority = head->projectPriority;

        StackNode *temp = head;
        head = head->next;
        delete temp;
    }
}

bool UndoStack::isEmpty()
{
    if (head == nullptr)
        return true;
    return false;
}

void UndoStack::clear()
{
    StackNode *ptr;

    while (head != nullptr)
    {
        ptr = head;
        head = head->next;
        delete ptr;
    }
}
