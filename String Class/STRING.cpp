#include "STRING.h"
#include <string.h>
#include <iostream>
#include <conio.h>
using namespace std;

STRING::STRING()
{
     size = 0;
     st = NULL;
}

STRING::STRING(const char* c)
{
     size = 0;
     while(c[size] != '\0')
          size++;
     if(size == 0)
          st = NULL;
     else
     {
          st = new char[size];
          for(unsigned i = 0; i < size; i++)
               st[i] = c[i];
          st[size] = '\0';
     }                     
}

STRING::STRING(const char c)
{
     size = 1;
     st = new char[1];
     st[0] = c;                 
} 

STRING::STRING(const STRING& s)
{
     size = s.size;
     st = new char[size];
     for(unsigned i = 0; i < size; i++)
          st[i] = s.st[i];
}

STRING::~STRING()
{
     if (size > 0)
          delete [ ] st;         
}

unsigned STRING::length() const
{
     return size;         
}

STRING& STRING::operator= (const STRING& s)
{
     if(this == &s) 
          return *this;
     if(size > 0)
          delete [ ] st;
     size = s.size;     
     st = new char[size];
     for(unsigned i = 0; i < size; i++)
          st[i] = s.st[i];
     return *this;
}

char STRING::operator[] (const unsigned i) const
{
     if(i >= size)
     {
          cout << "Error: index out of range" << endl;
          cout << "char STRING::operator[] (unsigned i) const" << endl;
          char cc;
          cin >> cc;
     }
     return st[i]; 
}

char& STRING::operator[] (const unsigned i)
{
     if(i >= size)
     {
          cout << "Error: index out of range" << endl;
          cout << "char& STRING::operator[] (unsigned i)" << endl;
          char cc;
          cin >> cc;
     }
     return st[i]; 
}

bool IsNumeric(const char c) 
{
     return((c >= '0') && (c <= '9'));
}

STRING::operator char*() const
{
     return (char*)st;
}

STRING::operator int() const
{
     int int_val = 0;
     bool is_str_neg;
     
     for(int i = 0; i < size; i++)
     {
          if(st[i] == '-') {
		          is_str_neg = true;
		          break;
          } 
          else
		          is_str_neg = false;
     }
     
     for(int i = 0; i < size; i++)
     {
          if(IsNumeric(st[i])) 
              int_val = 10 * int_val + (st[i] - '0');
     }
     
     if(is_str_neg) 
         int_val = -int_val;
     
     return int_val;
}

STRING::operator float() const
{
     float float_val = 0, j = 1;
     int i, k; 
     bool is_str_neg = false, decimal = false;
     
     for(i = 0; i < size; i++)
     {
         if(st[i] == '-') 
		         is_str_neg = true;
		     else if(st[i] == '.') 
         {
             k = i;         
             decimal = true;
         }
     }
     
     if(!decimal)
     {
          for(int p = 0; p < size; i++)
          {
               if(IsNumeric(st[p])) 
                    float_val = 10 * float_val + (st[p] - '0');
          }
     }
     
     if(decimal) 
     {
          for(int r = 0; r < size && r != k; r++)
          {
               if(IsNumeric(st[r]))
                    float_val = 10 * float_val + (st[r] - '0');
               else if(st[r] == '.')
                    break;     
               else if(st[r] != '-')
                    r++;
          }
          for(k = k + 1; k < size ; k++) 
          { 
               if(IsNumeric(st[k])) 
               {
                    float_val = float_val + 
                         ((float)(st[k] - '0')/(float)(10 * j));
                    j *= 10;
               } else 
                    break;
          }
     }
     
     if(is_str_neg) 
          float_val = -float_val;
     
     return float_val;
}

int STRING::position(const char c) const
{
     for(unsigned i = 0; i < size; i++)
     {
          if(st[i] == c)
               return i;
     }
     return -1;
}

STRING& STRING::operator+= (const STRING& s)
{
     char* temp = new char[size + s.size];
     for(unsigned i = 0; i < size; i++)
          temp[i] = st[i];
     for(unsigned i = size; i < size + s.size; i++)
          temp[i] = s.st[i - size];
     if(size > 0)
          delete [ ] st;
     size += s.size;
     st = new char[size];
     st = temp;
     return *this;
}

STRING& STRING::operator+= (const char* c)
{
     char* temp = new char[size + STRING(c).size];
     for(unsigned i = 0; i < size; i++)
          temp[i] = st[i];
     for(unsigned i = size; i < size + STRING(c).size; i++)
          temp[i] = STRING(c).st[i - size];
     if(size > 0)
          delete [ ] st;
     size += STRING(c).size;
     st = new char[size];
     st = temp;
     return *this;
}

STRING& STRING::operator+= (const char c)
{
     char* temp = new char[size + STRING(c).size];
     for(unsigned i = 0; i < size; i++)
          temp[i] = st[i];
     for(unsigned i = size; i < size + STRING(c).size; i++)
          temp[i] = STRING(c).st[i - size];
     if(size > 0)
          delete [ ] st;
     size += STRING(c).size;
     st = new char[size];
     st = temp;
     return *this;
}

bool IsAlpha(const char c)
{
     return(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));
}

void STRING::upcase()
{
     for(int i = 0; i < size; i++)
         if(IsAlpha(st[i]))
             st[i] &= 223; 
}

void STRING::downcase()
{
     for(int i = 0; i < size; i++)
         if(IsAlpha(st[i]))
             st[i] |= 32;
}

void STRING::togglecase()
{
     for(int i = 0; i < size; i++)
         if(IsAlpha(st[i]))
             st[i] ^= 32;
}

ostream& operator<< (ostream& os, const STRING& s)
{
     for(unsigned i = 0; i < s.size; i++)
          os << s.st[i];
     return os;
}

istream& operator>> (istream& is, STRING& s)
{
     char ch;
     STRING inS;
     
     while(true) {
          ch = getche();
          if(ch == 13) 
               break;
          else
               inS += ch;
     }
     s = inS;
     return is;
}

bool operator== (const STRING& lhs, const STRING& rhs)
{
     if(lhs.size != rhs.size)
          return false;
     for(unsigned i = 0; i < lhs.size; i++)
     {
          if(lhs.st[i] != rhs.st[i])
               return false;
     }
     return true;
}

bool operator== (const STRING& lhs, const char* c)
{
     return(lhs == STRING(c));
}

bool operator== (const char* c, const STRING& rhs)
{
     return(STRING(c) == rhs);
}

bool operator== (const char c, const STRING& rhs)
{
     return(STRING(c) == rhs);
}

bool operator== (const STRING& lhs, const char c)
{
     return(lhs == STRING(c));
}

bool operator!= (const STRING& lhs, const STRING& rhs)
{
     return(!(lhs == rhs));
}

bool operator!= (const STRING& lhs, const char* c)
{
     return(!(lhs == STRING(c)));
}

bool operator!= (const char* c, const STRING& rhs)
{
     return(!(STRING(c) == rhs));
}

bool operator!= (const char c, const STRING& rhs)
{
     return(!(STRING(c) == rhs));
}

bool operator!= (const STRING& lhs, const char c)
{
     return(!(lhs == STRING(c)));
}

bool operator> (const STRING& lhs, const STRING& rhs)
{
     for(unsigned i = 0; i < lhs.size; i++)
     {    
         if(lhs.st[i] <= rhs.st[i]) 
              return false;
         else 
              return true;
     }
}

bool operator> (const STRING& lhs, const char* c)
{
     return(lhs > STRING(c));
}

bool operator> (const char* c, const STRING& rhs)
{
     return(STRING(c) > rhs);
}

bool operator> (const char c, const STRING& rhs)
{
     return(STRING(c) > rhs);
}

bool operator> (const STRING& lhs, const char c)
{
     return(lhs > STRING(c));
}

bool operator< (const STRING& lhs, const STRING& rhs)
{
     for(unsigned i = 0; i < lhs.size; i++)
     {    
         if(lhs.st[i] >= rhs.st[i]) 
              return false;
         else 
              return true;
     }
}

bool operator< (const STRING& lhs, char* c)
{
     return(lhs < STRING(c));
}

bool operator< (const char* c, const STRING& rhs)
{
     return(STRING(c) < rhs);
}

bool operator< (const char c, const STRING& rhs)
{
     return(STRING(c) < rhs);
}

bool operator< (const STRING& lhs, const char c)
{
     return(lhs < STRING(c));
}

bool operator<= (const STRING& lhs, const STRING& rhs)
{
     return((lhs < rhs) || (lhs == rhs));
}

bool operator<= (const STRING& lhs, const char* c)
{
     return((lhs < STRING(c)) || (lhs == STRING(c)));
}

bool operator<= (const char* c, const STRING& rhs)
{
     return((STRING(c) < rhs) || (STRING(c) == rhs));
}

bool operator<= (const char c, const STRING& rhs)
{
     return((STRING(c) < rhs) || (STRING(c) == rhs));
}

bool operator<= (const STRING& lhs, const char c)
{
     return((lhs < STRING(c)) || (lhs == STRING(c)));
}

bool operator>= (const STRING& lhs, const STRING& rhs)
{
     return((lhs < rhs) || (lhs == rhs));
}

bool operator>= (const STRING& lhs, const char* c)
{
     return((lhs > STRING(c)) || (lhs == STRING(c)));
}

bool operator>= (const char* c, const STRING& rhs)
{
     return(((STRING(c) > rhs) || (STRING(c) == rhs)));
}

bool operator>= (const char c, const STRING& rhs)
{
     return(((STRING(c) > rhs) || (STRING(c) == rhs)));
}

bool operator>= (const STRING& lhs, const char c)
{
     return (lhs > STRING(c) || lhs == STRING(c));
}

STRING operator+ (const STRING& lhs, const STRING& rhs) 
{      
     STRING temp = lhs; 
     temp += rhs;
     return temp;    
}
   
STRING operator+ (const char* c, const STRING& rhs)
{
     STRING temp = STRING(c);
     temp += rhs;
     return temp;
}

STRING operator+ (const STRING& lhs, const char* c)
{
     STRING temp = lhs; 
     temp += STRING(c);
     return temp;
}

STRING operator+ (const char c, const STRING& rhs)
{
     STRING temp = STRING(c);
     temp += rhs;
     return temp;
}

STRING operator+ (const STRING& lhs, const char c)
{
     STRING temp = lhs; 
     temp += STRING(c);
     return temp;
}
