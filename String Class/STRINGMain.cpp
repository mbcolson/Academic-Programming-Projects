#include "STRING.h"
#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

int main()
{
     char c, c1 = 'e';    
     STRING s1("hello"), s2("bob");
     STRING s3("wHaT's uP?"), s4("-86492"), s5("-8.767"), s6("world");
     STRING s7("John"), s8(" says"), s9(" to stay inside"), s10(""), s11("");
     STRING s12(""), s13("park"), s14("park");
     STRING s15("HeLLo SiR");
     cout << "s1 is: " << s1 << endl;
     cout << "s2 is: " << s2 << endl;
     cout << "s3 is: " << s3 << endl;
     cout << "s4 is: " << s4 << endl;
     cout << "s5 is: " << s5 << endl;
     cout << "s6 is: " << s6 << endl;
     cout << "s7 is: " << s7 << endl;
     cout << "s8 is: " << s8 << endl;
     cout << "s9 is: " << s9 << endl;
     cout << "s10 is: " << s10 << endl;
     cout << "s11 is: " << s11 << endl;
     cout << "s12 is: " << s12 << endl;
     cout << "s13 is: " << s13 << endl;
     cout << "s14 is: " << s14 << endl;
     cout << "Enter a string: ";
     cin >> s11;
     cout << endl << endl << "you entered the string: " << s11 << endl;
     cout << "s8 + c1 is: " << s8 + c1 << endl;
     cout << endl << "Enter a character to find in string s1: ";
     cin >> c;
     cout << endl << "The position of the character '" << c << "' is: "
          << s1.position(c) << endl << endl;
     s10 = s7;
     cout << "Does s3 come before s7 alphabetically? " 
          << ((s3 < s7) ? "yes" : "no") << endl;
     cout << "Does s2 come before s1 alphabetically? " 
          << ((s2 < s1) ? "yes" : "no") << endl;
     cout << "Strings s2 and s6 are: " << ((s2 != s6) ? "not the same" 
          : "the same") << endl << endl;
     cout << "s10 = s7; " << endl;
     cout << "s10 is: " << s10 << endl;
     cout << "Strings s1 and s2 are: " << ((s1 == s2) ? "the same" 
          : "not the same") << endl << endl;
     cout << "Strings s13 and s14 are: " << ((s13 == s14) ? "the same" 
          : "not the same") << endl << endl;
     cout << "s10 is: " << s10 << endl;
     s10 += s8;
     cout << "s10 += s8;" << endl;
     cout <<"s10 is: " << s10 << endl;
     s11 = s7 + s8 + s9;
     cout << "s11 = s7 + s8 + s9;" << endl;
     cout << "s11 is: " << s11 << endl;
     cout << "s1 is: " << s1 << endl;
     cout << "s3 is: " << s3 << endl;
     cout << "s15 is: " << s15 << endl;
     s1.upcase();
     s3.downcase();
     s15.togglecase();
     cout << "s1 is now uppercase: " << s1 << endl;
     cout << "s3 is now lowercase: " << s3 << endl;
     cout << "s15 togglecase: " << s15 << endl;
     cout << "s4 is now an integer" << endl;
     cout << "s4 + 5 = " << s4 << " + 5 is: " << (int)s4 + 5 << endl;
     cout << "s5 is now a float: " << endl;
     cout << "s5 + 2.526 = " << s5 << " + 2.526 is: " << setprecision(7) 
          << (float)s5 + 2.526 << endl;
     (char*)s6;
     cout << "s6 is now a char* string: " << s6 << endl;  
     cout << endl << endl;
    
     return 0;
}
