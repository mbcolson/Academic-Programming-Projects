#include <iostream>
using namespace std;

#ifndef _STRING_H_DEF_
#define _STRING_H_DEF_

/* class invariant: (size == 0 and st == NULL) or size == number of allocated 
                    bytes pointed to by st */

class STRING
{
     unsigned size;
     char* st;
public:
     
     /* Function: Default constructor which produces the empty STRING.
        Post: size = 0; AND st = NULL;    */
     STRING();
     
     /* Function: Constructor thats takes a char* and uses it to initialize the STRING. 
        Post: size contains the number of characters in the char* string and 
              enough space is allocated to store st.  Also, st[size] = '\0'. */
     STRING(const char* c);
     
     /* Function: Constructor thats takes a char and uses it to initialize the STRING. 
        Post: size = 1, st has enough space allocated to hold one character 
              and st[0] = c.      */
     STRING(const char);  
     
     /* Function: Copy constructor, takes a STRING and uses it to initialize the STRING. 
        Pre: Argument is of type STRING.
        Post: A copy of the STRING passed into the function is made with 
              the same size and same characters.     */
     STRING(const STRING&);
     
     /* Function: Destructor
        Post: all memory is deallocated */
     ~STRING();
     
     /* Function: Finds the length of a string 
        Post: Returns the length of the string */
     unsigned length() const;
     
     /* Function: Assigns the contents of the rhs to the lhs. 
        Pre: Argument is of type STRING.
        Post: The contents of the left hand operand contain the contents of the
              right hand operand.
        Parameter #1 : in    */
     STRING& operator= (const STRING&);
     
     /* Function: Appends a STRING to end the left hand operand and stores it 
                  in the left hand operand. 
        Pre: Argument is of type STRING.
        Post: The contents of the left hand operand contains its own contents 
              plus the contents of the right hand operand.
        Parameter #1 : in    */
     STRING& operator+= (const STRING&);
     
     /* Function: Appends the contents of the char* string to end the left hand 
                  operand and stores it in the left hand operand.
        Pre: Argument is a char* string.
        Post: The contents of the left hand operand contains its own contents 
              plus the contents of the right hand operand.
        Parameter #1 : in    */
     STRING& operator+= (const char*);
     
     /* Function: Appends the contents of the character to end the left hand 
                  operand and stores it in the left hand operand.
        Pre: Argument is a character.
        Post: The contents of the left hand operand contains its own contents 
              plus the contents of the right hand operand.
        Parameter #1 : in    */
     STRING& operator+= (const char);
     
     /* Function: Overloads the array subscript operator to work with our 
                  STRING.  Returns one character through indexing. (Const 
                  version)
        Pre: Operand is of type STRING and argument is an unsigned integer.
        Post: Returns one character of the operand of type STRING through 
              indexing.
        Parameter #1 : in    */
     char operator[](const unsigned) const;
     
     /* Function: Overloads the array subscript operator to work with our 
                  STRING.  Returns one character through indexing. (Non-const 
                  version)
        Pre: Operand is of type STRING and argument is an unsigned integer.
        Post: Returns one character of the operand of type STRING through 
              indexing.
        Parameter #1 : in    */
     char& operator[](const unsigned);
     
     /* Function: Casts our STRING to a char* string.
        Pre: The operand must be of type STRING.
        Post: The operand is converted to a char* string.  */
     operator char*() const;
     
     /* Function: Casts our STRING to a integer.
        Pre: The operand must be of type STRING.
        Post: The operand is converted to an int.  */
     operator int() const;
     
     /* Function: Casts our STRING to a float.
        Pre: The operand must be of type STRING.
        Post: The operand is converted to a float.  */
     operator float() const;
     
     /* Function: Returns the position of a character c in the STRING as an int.
                  Returns -1 if the character is not in the STRING.
        Pre: Argument is of type char.
        Post: Returns the position of the character c in the STRING as an int.
              Returns -1 if the character is not in the STRING.
        Parameter #1 : in    */
     int position(const char c) const;
     
     /* Function: Changes all alphabetic characters to uppercase
        Post: STRING has the case of all alphabetic characters changed to 
              uppercase.     */
     void upcase();
     
     /* Function: Changes all alphabetic characters to lowercase
        Post: STRING has the case of all alphabetic characters changed to 
              lowercase.     */
     void downcase();
     
     /* Function: Changes the case of all alphabetic characters 
        Post: STRING has the case of all alphabetic characters changed. */
     void togglecase();
     
     /* Function: Overloads the << operator to work with our STRING.  Returns an
                  ostream.
        Post: Returns an ostream.
        Parameter #1 : out       
        Parameter #2 : in    */
     friend ostream& operator<< (ostream& , const STRING&);
     
     /* Function: Overloads the >> operator to work with our STRING.  Returns an
                  istream.
        Post: Returns an istream.
        Parameter #1 : out      
        Parameter #2 : out   */
     friend istream& operator>> (istream& , STRING&);
     
    /* Function: Compares two STRINGS to see if they contain the same characters
                 or not.
        Post: Returns true if lhs is equal to rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator== (const STRING&, const STRING&);
     
     /* Function: Compares a STRING and a char* string to see if they contain 
                  the same characters or not.
        Post: Returns true if STRING is equal to char* and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator== (const STRING&, const char* );
     
     /* Function: Compares a STRING and a char* string to see if they contain 
                  the same characters or not.
        Post: Returns true if char* is equal to STRING and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator== (const char*, const STRING&);
     
     /* Function: Compares a character and a STRING to see if they contain 
                  the same character or not.
        Post: Returns true if char is equal to STRING and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator== (const char, const STRING&);
     
     /* Function: Compares a STRING and a character to see if they contain 
                  the same character or not.
        Post: Returns true if STRING is equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator== (const STRING&, const char);
     
     /* Function: Compares two STRINGS to see if they contain the same 
                  characters or not.
        Post: Returns true if lhs is not equal to rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator!= (const STRING&, const STRING&);
     
     /* Function: Compares a STRING and a char* string to see if they contain 
                  the same characters or not.
        Post: Returns true if lhs is not equal to char* and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator!= (const STRING&, const char* );
     
     /* Function: Compares a STRING and a char* string to see if they contain 
                  the same characters or not.
        Post: Returns true if char* is not equal to rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator!= (const char*, const STRING&);
     
     /* Function: Compares a character and a STRING to see if they contain 
                  the same character or not.
        Post: Returns true if char is not equal to rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator!= (const char, const STRING&);
     
     /* Function: Compares a STRING and a character to see if they contain 
                  the same character or not.
        Post: Returns true if lhs is not equal to char and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator!= (const STRING&, const char);
     
     /* Function: Compares two STRINGS and tests whether the lhs is greater than
                  the rhs.
        Post: Returns true if lhs is greater than rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator> (const STRING&, const STRING&);
     
     /* Function: Compares a STRING and a char* string and tests whether the 
                  STRING is greater than the char* string.
        Post: Returns true if lhs is greater than char* and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator> (const STRING&, const char* );
     
     /* Function: Compares a char* string and a STRING and tests whether the 
                  char* string is greater than the STRING.
        Post: Returns true if lhs is greater than char* and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator> (const char*, const STRING&);
     
     /* Function: Compares a character and a STRING and tests whether the 
                  character is greater than the STRING.
        Post: Returns true if char* is greater than rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator> (const char, const STRING&);
     
    /* Function: Compares a STRING and a character and tests whether the STRING 
                 is greater than the character.
        Post: Returns true if char is greater than or equal to rhs and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator> (const STRING&, const char);
     
     /* Function: Compares two STRINGS and tests whether the lhs is less than
                  the rhs.
        Post: Returns true if lhs is greater than rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator< (const STRING&, const STRING&);
     
     /* Function: Compares a STRING and a char* string and tests whether the 
                  STRING is less than the char* string.
        Post: Returns true if lhs is less than char* and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator< (const STRING&, const char* );
     
     /* Function: Compares a char* string and a STRING and tests whether the 
                  char* string is less than the STRING.
        Post: Returns true if char* is less than rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator< (const char*, const STRING&);
     
     /* Function: Compares a character and a STRING and tests whether the 
                  character is less than the STRING.
        Post: Returns true if char* is less than rhs and false otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator< (const char, const STRING&);
     
     /* Function: Compares a STRING and a character and tests whether the STRING 
                  is less than the character.
        Post: Returns true if STRING is less than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator< (const STRING&, const char);
     
     /* Function: Compares two STRINGS and tests whether the lhs is less than or 
                  equal to the rhs.
        Post: Returns true if STRING is less than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator<= (const STRING&, const STRING&);
     
     /* Function: Compares a STRING and a char* string and tests whether the 
                  STRING is less than or equal to the char* string.
        Post: Returns true if STRING is less than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator<= (const STRING&, const char* );
     
     /* Function: Compares a char* string and a STRING and tests whether the 
                  char* string is less than or equal to the STRING.
        Post: Returns true if STRING is less than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator<= (const char*, const STRING&);
     
     /* Function: Compares a character and a STRING and tests whether the 
                  character is less than or equal to the STRING.
        Post: Returns true if STRING is less than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator<= (const char, const STRING&);
     
    /* Function: Compares a STRING and a character and tests whether the STRING 
                 is less than or equal to the character.
        Post: Returns true if STRING is less than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator<= (const STRING&, const char);
     
     /* Function: Compares two STRINGS and tests whether the lhs is less 
                  than or equal to the rhs.
        Post: Returns true if lhs is greater than or equal to rhs and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator>= (const STRING&, const STRING&);
     
     /* Function: Compares a STRING and a char* string and tests whether the 
                  STRING is greater than or equal to the char* string.
        Post: Returns true if STRING is greater than or equal to char* and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator>= (const STRING&, const char* );
     
     /* Function: Compares a char* string and a STRING and tests whether the 
                  char* string is greater than or equal to the STRING.
        Post: Returns true if char* is greater than or equal to STRING and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator>= (const char*, const STRING&);
     
     /* Function: Compares a character and a STRING and tests whether the 
                  character is greater than or equal to the STRING.
        Post: Returns true if char is greater than or equal to STRING and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator>= (const char, const STRING&);
     
     /* Function: Compares a STRING and a character and tests whether the STRING 
                  is greater than or equal to the character.
        Post: Returns true if STRING is greater than or equal to char and false
              otherwise.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend bool operator>= (const STRING&, const char);
     
     /* Function: Appends the contents of the rhs to the end of the lhs.
        Post: lhs is assigned lhs with rhs appended to it.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend STRING operator+ (const STRING&, const STRING&);
     
     /* Function: Appends the contents of the rhs to the end of the char* 
                  string.
        Post: char* is assigned char* with STRING appended to it
        Parameter #1 : in      
        Parameter #2 : in    */
     friend STRING operator+ (const char*, const STRING&);
     
     /* Function: Appends the contents of the char* string to the end of the 
                  lhs.
        Post: STRING is assigned STRING with char* appended to it
        Parameter #1 : in      
        Parameter #2 : in    */
     friend STRING operator+ (const STRING&, const char*);
     
     /* Function: appends the contents of the rhs to the end of the character.
        Post: c is assigned c with the contents of STRING appended to it
        Parameter #1 : in      
        Parameter #2 : in    */
     friend STRING operator+ (const char, const STRING&);
     
     /* Function: Appends the contents of the character to the end of lhs.
        Post: STRING is assigned STRING with c appended to it.
        Parameter #1 : in      
        Parameter #2 : in    */
     friend STRING operator+ (const STRING&, const char);
};

     /* Function: Checks if a character is an alpha character or not.
        Post: Returns true if the character is an alpha character and false 
              if it is not an alpha character.
        Parameter #1 : in    */
     bool IsAlpha(const char);

     /* Function: Checks if a character is numeric or not.
        Post: Returns true if the character is a number and false if it is not a 
              number.
        Parameter #1 : in    */
     bool IsNumeric(const char);

#endif
