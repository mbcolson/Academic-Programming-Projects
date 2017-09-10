#ifndef _RATIONAL_H_
#define _RATIONAL_H_
#include <iostream>
using namespace std;

class Rational
{
   long _p;  // numerator
   long _q;  // denominator
   void reduce();  // put fraction in reduced form
   int gcf(int, int); // Greatest Common Factor
   int lcm(int, int); // Lowest Common Multiple
public:
   Rational( );  //default constructor
   Rational(long, long = 1);  //constructor
   Rational(const Rational&);  //copy constructor
   Rational& operator=(const Rational&);
   Rational& operator+=(const Rational&);
   Rational& operator-=(const Rational&);
   Rational& operator*=(const Rational&);
   Rational& operator/=(const Rational&);
   friend ostream& operator<< ( ostream&, const Rational&);
   friend istream& operator>> ( istream&, Rational&);
   Rational operator+ (const Rational& ) const;
   Rational operator+ (long) const;
   friend Rational operator+ (long, const Rational&);
   Rational operator- (const Rational& ) const;
   Rational operator- (long) const;
   friend Rational operator- (long, const Rational&);
   Rational operator* (const Rational& ) const;
   Rational operator* (long) const;
   friend Rational operator* (long, const Rational&);
   Rational operator/ (const Rational& ) const;
   Rational operator/ (long) const;
   friend Rational operator/ (long, const Rational&);
   Rational operator- ();
   Rational operator+ ();
   Rational operator++ (int); //post
   Rational operator-- (int); //post
   Rational& operator++ (); //pre
   Rational& operator-- (); //pre
   bool operator== (const Rational& ) const;
   bool operator== (long) const;    
   friend bool operator== (long, const Rational&);
   bool operator< (const Rational& ) const;
   bool operator< (long) const;  
   friend bool operator< (long, const Rational&);
   bool operator!= (const Rational& ) const;
   bool operator!= (long) const;  
   friend bool operator!= (long, const Rational&);
   bool operator> (const Rational& ) const;
   bool operator> (long) const;  
   friend bool operator> (long, const Rational&);
   bool operator<= (const Rational& ) const;
   bool operator<= (long) const;  
   friend bool operator<= (long, const Rational&);
   bool operator>= (const Rational& ) const;
   bool operator>= (long) const;  
   friend bool operator>= (long, const Rational&);
   Rational reciprocal ()const; //returns the reciprocal
   Rational pow(long L)const; //returns the Rational to the L power
   operator long ( ) const; //Casting operators
};

#endif

