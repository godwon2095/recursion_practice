#include "listrec.h"
#include <iostream>
#include <assert.h>
#include <stack>

using namespace std;

//--------------------------------------------------------------------

template < class LE >
ListNode<LE>::ListNode(const LE &elem, ListNode *nextPtr)
: element(elem),
next(nextPtr)
{}


template<class LE>
List<LE>::List(int ignored)
{
    cursor = 0;
    head = 0;
    listSize = 0;
    writeCount = 0;
}


template<class LE>
List<LE>::~List()
{
    this->clear();
}


template<class LE>
void List<LE>::insert(const LE &newData)
{
    if (head == NULL)
    {
        ListNode<LE>* location = new ListNode<LE>(newData, NULL);
        head = location;
        cursor = location;
        listSize++;
    }
    else
    {
        ListNode<LE>* location = new ListNode<LE>(newData, cursor->next);
        cursor->next = location;
        cursor = location;
        listSize++;
    }
}

template<class LE>
void List<LE>::remove()
{
    if (this->isEmpty())
    {
        cout << "Empty List!" << endl;
    }
    else {
        if (cursor != head)
        {
            ListNode<LE>* saveCursor = cursor->next;
            ListNode<LE>* deleteCursor = cursor;
            
            this->gotoPrior();
            cursor->next = saveCursor;
            
            delete deleteCursor;
            listSize--;
        }
        else
        {
            ListNode<LE>* saveCursor = cursor->next;
            ListNode<LE>* deleteCrusor = cursor;
            
            List<LE>::gotoNext();
            head = saveCursor;
            
            delete deleteCrusor;
            listSize--;
        }
    }
}


template<class LE>
void List<LE>::replace(const LE &newData)
{
    if (this->isEmpty())
    {
        cout << "Empty List!" << endl;
    }
    else
    {
        ListNode<LE> *location = cursor;
        location->element = newData;
    }
}


template<class LE>
bool List<LE>::gotoBeginning()
{
    if (this->isEmpty())
    {
        cout << "Empty List!" << endl;
    }
    else
    {
        cursor = head;
    }
    return false;
}


template<class LE>
bool List<LE>::gotoEnd()
{
    if (this->isEmpty())
    {
        cout << "Empty List!" << endl;
        return false;
    }
    else
    {
        this->gotoBeginning();
        do
        {
            this->gotoNext();
        } while (cursor->next != NULL);
        return true;
    }
}


template<class LE>
bool List<LE>::gotoNext()
{
    if (this->isEmpty())
    {
        cout << "Empty List!" << endl;
        return false;
    }
    else if (cursor->next == NULL)
    {
        return false;
    }
    else
    {
        cursor = cursor->next;
        return true;
    }
    
    return false;
}


template<class LE>
bool List<LE>::gotoPrior()
{
    if (this->isEmpty())
    {
        cout << "Empty Stack!" << endl;
        return false;
    }
    else
    {
        if (cursor == head) return false;
        else
        {
            int count = 1;
            int retrieve = 0;
            
            while (gotoNext())
            {
                count++;
            }
            retrieve = listSize - count;
            gotoBeginning();
            while (retrieve > 1)
            {
                gotoNext();
                retrieve--;
            }
        }
    }
    return true;
}


template<class LE>
void List<LE>::clear()
{
    if (this->isEmpty())
    {
        cout << "Empty List!" << endl;
    }
    else
    {
        int count = listSize;
        this->gotoEnd();
        do
        {
            this->remove();
            count--;
        } while (count != 0);
    }
}


template<class LE>
bool List<LE>::isEmpty()
{
    if (head == 0)
        return true;
    else
        return false;
}


template<class LE>
void List<LE>::showStructure() const
{
    if (head == 0)
    {
        cout << "Empty List" << endl;
    }
    else
    {
        for (ListNode<LE>* temp = head; temp != 0; temp = temp->next)
        {
            cout << " " << temp->element;
        }
        cout << " " << endl;
    }
}


template<class LE>
void List<LE>::write() const
{
    writeSub(head);
    cout << endl;
}


template<class LE>
void List<LE>::writeSub(ListNode<LE> *p) const
{
    if (p != 0)
    {
        cout << p->element;
        writeSub(p->next);
    }
}


template<class LE>
void List<LE>::insertEnd(const LE &newElement)
{
    insertEndSub(head, newElement);
}

template<class LE>
void List<LE>::insertEndSub(ListNode<LE> *&p, const LE &newElement)
{
    if (p != 0)
        insertEndSub(p->next, newElement);
    else
    {
        p = new ListNode<LE>(newElement, 0);
        cursor = p;
    }
}


template < class LE >
void List<LE>::reverse()
{
    reverseSub(0, head);
}

template<class LE>
void List<LE>::reverseSub(ListNode<LE> *p, ListNode<LE> *nextPtr)
{
    if (nextPtr != 0)
    {
        reverseSub(nextPtr, nextPtr->next);
        nextPtr->next = p;
    }
    else
        head = p;
}


template<class LE>
void List<LE>::writeMirror()
{
    writeMirrorSub(head);
    cout << endl;
}


template<class LE>
void List<LE>::writeMirrorSub(ListNode<LE> *p) const
{
    if (p != 0)
    {
        cout << p->element;
        writeMirrorSub(p->next);
        cout << p->element;
    }
}


template<class LE>
void List<LE>::deleteEnd()
{
    deleteEndSub(head);
    cursor = head;
}


template<class LE>
void List<LE>::deleteEndSub(ListNode<LE> *&p)
{
    if (p->next != 0)
        deleteEndSub(p->next);
    else
    {
        delete p;
        p = 0;
    }
}


template<class LE>
int List<LE>::length() const
{
    return lengthSub(head);
}

template<class LE>
int List<LE>::lengthSub(ListNode<LE> *p) const
{
    int result;
    
    if (p == 0)
        result = 0;
    else
        result = (lengthSub(p->next) + 1);
    
    return result;
}


template<class LE>
void List<LE>::iterReverse()
{
    if (head == NULL)
        cout << "Empty List!!" << endl;
    else
    {
        char tempAry[length()];
        int i(0), j(length()-1);
        for (ListNode<LE> *tempPtr = head; tempPtr != 0; tempPtr = tempPtr->next)
        {
            tempAry[i] = tempPtr->element;
            i++;
        }
        for (ListNode<LE> *tempPtr = head; tempPtr != 0; tempPtr = tempPtr->next)
        {
            tempPtr->element = tempAry[j];
            j--;
        }
    }
}


template<class LE>
void List<LE>::stackWriteMirror()
{
    stack<char> tempStack;
    
    for (ListNode<LE> *tempPtr = head; tempPtr != 0; tempPtr = tempPtr->next)
    {
        tempStack.push(tempPtr->element);
        cout << tempStack.top();
    }
    
    while(!tempStack.empty())
    {
        cout << tempStack.top();
        tempStack.pop();
    }
    
    cout << endl;
}


template<class LE>
void List<LE>::unknown1() const
{
    unknown1Sub(head);
    cout << endl;
}


template<class LE>
void Lost<LE>::unknown1Sub(ListNode<LE> *p) const
{
    if (p != 0)
    {
        cout << p->element;
        if (p->next != 0)
        {
            unknown1Sub(p->next->next);
            cout << p->next->element;
        }
    }
}


template<class LE>
void List<LE>::unknown2()
{
    unknown2Sub(head);
}

template<class LE>
void List<LE>::unknown2Sub(ListNode<LE> *&p)
{
    ListNode<LE> *q;
    
    if(p!=0 && p->next != 0)
    {
        q = p;
        p = p->next;
        q->next = p->next;
        p->next = q;
        unknown2Sub(q->next);
    }
}
