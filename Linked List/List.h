#ifndef LIST_H
#define LIST_H

#include <bits/stdc++.h>

typedef int ItemType;

class List
{
     struct node 
     {
          ItemType It;
          node* next;       
     };
       
     node* head;
     node* cur; 
public:      
     
     //Post: an empty List is created && EndOfLIst()
     List(void);
     
     //Post: A List is destroyed.
     ~List(void);
     
     //Post: FCTVEL == The List is empty
     bool IsEmpty(void) const;
     
     //Pre: !IsEmpty()
     //Post: List cursor is at the front of the list
     void Reset(void);
     
     //Post: FUCTVAL == The List cursor is beyond the last item
     bool EndOfList(void) const;
     
     //Pre: !IsEmpty() && !EndOfList()
     //Post: List cursor is advanced to the next item
     void Advance(void);
     
     //Pre: !IsEmpty() && !EndOfList()
     //Post: FCTVAL == Item at List cursor
     ItemType CurrentItem(void);
     
     //Pre: !IsEmpty() && !EndOfList()
     /*Post: Item at List cursor is deleted && the List cursor points
             to the successor of deleted item */
     void Delete(void);
     
     /*Post: If the list was empty then Inserted is the only item in
             the list. Other wise, Inserted is the predecessor of the item
             that was current when the function was called and Inserted is
             the new current item. */
     void Insert(/*in*/ const ItemType& Inserted);
     
     /*Post: List is displayed to standard out. This is used for
             debugging only. */
     void Display(void) const;
};

#endif
