#include "List.h"
using namespace std;

//Post: an empty List is created && EndOfLIst()
List::List(void)
{
     head = cur = NULL;     
}

//Post: A List is destroyed.
List::~List(void)
{
     Reset();
                 
     while(!IsEmpty())
          Delete();
}

//Post: FCTVEL == The List is empty
bool List::IsEmpty(void) const
{
     return head == NULL;     
}
    
//Pre: !IsEmpty()
//Post: List cursor is at the front of the list
void List::Reset(void)
{
     cur = head;           
}
     
//Post: FUCTVAL == The List cursor is beyond the last item
bool List::EndOfList(void) const
{
     return cur == NULL;           
}
     
//Pre: !IsEmpty() && !EndOfList()
//Post: List cursor is advanced to the next item
void List::Advance(void)
{
     cur = cur->next;
}

//Pre: !IsEmpty() && !EndOfList()
//Post: FCTVAL == Item at List cursor     
ItemType List::CurrentItem(void)
{
     return cur->It;          
}
    
//Pre: !IsEmpty() && !EndOfList()
/*Post: Item at List cursor is deleted && the List cursor points
        to the successor of deleted item */
void List::Delete()
{
     node *temp = new node;
     temp = head;
     
     if(head == cur)
     {
          head = head->next;
          delete cur;
          cur = head;
     }
     else 
     {
          while(temp->next != cur)
               temp = temp->next;
          temp->next = cur->next;
          delete cur;
          cur = temp->next;
     }
}

/*Post: If the list was empty then Inserted is the only item in
        the list. Other wise, Inserted is the predecessor of the item
        that was current when the function was called and Inserted is
        the new current item. */
void List::Insert(const ItemType& Inserted)
{
     node* temp = new node;
     temp->It = Inserted;
     temp->next = cur;
     if(head==cur)
     {
          head = temp;
          cur = head;
     } else {
          cur = head;
          while(cur->next != temp->next)
               cur = cur->next;
          cur->next = temp;
          cur = cur->next;
     }
}

/*Post: List is displayed to standard out. This is used for
        debugging only. */     
void List::Display(void) const
{
     node *temp;
     temp = head;
     cout << "cur->It is: " << cur->It << endl;
     while(temp != NULL)
     {
          cout << temp->It << " -> ";
          temp = temp->next;
     }
     cout << "NULL" << endl;
}
