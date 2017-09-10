#include "Rational.h"
#include <iostream>
using namespace std;

//default constructor
Rational::Rational()
{
     _p = 0;
     _q = 1;
}

// Constructor to initialize the rational object
Rational::Rational(long p, long q)
{
     _p = p;  // numerator
     _q = q;  // denominator
     reduce();
}

// Copy constructor
Rational::Rational(const Rational &src)
{
     _p = src._p;
     _q = src._q;
}

Rational& Rational::operator=(const Rational &src)
{
     _p = src._p;
     _q = src._q;
     reduce();
     return *this;
}

Rational& Rational::operator+=(const Rational &other)
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     int lcd = lcm(temp._q, other._q);
     int quot1 = lcd/temp._q;
     int quot2 = lcd/other._q;
     _p = temp._p * quot1 + other._p * quot2;
     _q = lcd;
     reduce();
     return *this;
}

Rational& Rational::operator-=(const Rational &other)
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     int lcd = lcm(temp._q, other._q);
     int quot1 = lcd/temp._q;
     int quot2 = lcd/other._q;
     _p = temp._p * quot1 - other._p * quot2;
     _q = lcd;
     reduce();
     return *this;
}

Rational& Rational::operator*=(const Rational &other)
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     _p = temp._p * other._p;
     _q = temp._q * other._q;
     reduce();
     return *this;
}

Rational& Rational::operator/=(const Rational &other)
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     int lcd = lcm(temp._q, other._q);
     int quot1 = lcd/temp._q;
     int quot2 = lcd/other._q;
     _p = temp._p * quot1 - other._p * quot2;
     _q = lcd;
     reduce();
     return *this;
}

ostream& operator<< (ostream& os, const Rational &other)
{
     os << other._p << '/' << other._q;
     return os;
}

istream& operator>> (istream& is, Rational &other)
{
     char s;
     is >> other._p >> s >> other._q;
     other.reduce();
     return is;
}

Rational Rational::operator+ (const Rational &other) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp += other;
     return temp;
}

Rational Rational::operator+ (long l) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp += Rational(l);
     return temp;
}

Rational operator+ (long l, const Rational &other)
{
     Rational temp = Rational(l);
     temp += other;
     return temp;
}

Rational Rational::operator- (const Rational& other) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp -= other;
     return temp;
}

Rational Rational::operator- (long l) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp -= Rational(l);
     return temp;
}

Rational operator- (long l, const Rational& other)
{
     Rational temp = Rational(l);
     temp -= other;
     return temp;
}

Rational Rational::operator* (const Rational& other) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp *= other;
     return temp;
}

Rational Rational::operator* (long l) const
{
     Rational temp;
     temp._p = _p;
     temp *= Rational(l);
     return temp;
}

Rational operator* (long l, const Rational& other)
{
     Rational temp = Rational(l);
     temp *= other;
     return temp;
}

Rational Rational::operator/ (const Rational& other) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp /= other;
     return temp;
}

Rational Rational::operator/ (long l) const
{
     Rational temp;
     temp._p = _p;
     temp._q = _q;
     temp /= Rational(l);
     return temp;
}

Rational operator/ (long l, const Rational& other)
{
     Rational temp = Rational(l);
     temp /= other;
     return temp;
}

Rational Rational::operator- () 
{
     Rational &temp = *this;
     temp._p = -_p;
     return temp;
}

Rational Rational::operator+ () 
{
     Rational &temp = *this;
     return temp;
}

Rational Rational::operator++ (int) //post
{
     Rational &temp = *this;
     temp += 1;
     return temp;
}

Rational Rational::operator-- (int) //post
{
     Rational &temp = *this;
     temp -= 1;
     return temp;
}

Rational& Rational::operator++ () //pre
{
     Rational &temp = *this;
     temp += 1;
     return temp;
}

Rational& Rational::operator-- () //pre
{
     Rational &temp = *this;
     temp -= 1;
     return temp;
}

bool Rational::operator== (const Rational& other) const
{
     return(_p == other._p && _q == other._q);
}
bool Rational::operator== (long l) const 
{
     return(_p == l * _q);
}
bool operator== (long l, const Rational& other)
{
     return(other._p == l * other._q);
}
bool Rational::operator< (const Rational& other) const
{
     return (_p * other._q < _q * other._p);
}
bool Rational::operator< (long l) const  
{
     return (_p < l * _q);
}
bool operator< (long l, const Rational& other)
{
     return(l * other._q < other._p);
}
bool Rational::operator!= (const Rational& other) const
{
     return (_p * other._q != _q * other._p); 
}
bool Rational::operator!= (long l) const  
{
     return (_p != l * _q);
}
bool operator!= (long l, const Rational& other)
{
     return (other._p != l * other._q);
}
bool Rational::operator> (const Rational& other) const
{
     return (_p * other._q > _q * other._p);
}
bool Rational::operator> (long l) const  
{
     return (_p > l * _q);
}
bool operator> (long l, const Rational& other)
{
     return (l * other._q > other._p);
}
bool Rational::operator<= (const Rational& other) const
{
     return !(_p * other._q > _q * other._p);
}
bool Rational::operator<= (long l) const  
{
     return !(_p > l * _q);
}
bool operator<= (long l, const Rational& other)
{
     return !(l * other._q > other._p);
}
bool Rational::operator>= (const Rational& other) const
{
     return !(_p * other._q < _q * other._p);
}
bool Rational::operator>= (long l) const  
{
     return !(_p < l * _q);
}
bool operator>= (long l, const Rational& other)
{
     return !(l * other._q < other._p);
}
Rational Rational::reciprocal ( ) const 
{
     Rational temp;    
     temp._p = _q;
     temp._q = _p;
     return temp;
}
Rational Rational::pow(long L) const 
{
     Rational temp = *this; 
     Rational temp2;
     
     if(L == 0)
          return 1;     
     if(L < 0) 
     {
          L *= -1;
          temp = reciprocal();
     }
     temp2 = temp;
     for(int i = 1; i < L; i++) 
          temp *= temp2;
     return temp;
}             

Rational::operator long ( ) const 
{
     return (_p/_q);
}

/* Function: recursive function that takes two integers
             and finds the greatest common factor   */
int Rational::gcf(int q1, int q2)
{
     if((q1 % q2 == 0) && q2 > 0)
          return q2;
     else if((q1 % q2 == 0) && q2 < 0)
          return -q2;
     else
          return gcf(q2, q1 % q2);
}

// Function: puts the rational number in reduced form
void Rational::reduce()
{
     if(_q == 0)  // make sure the denominator is not 0
     {
          _p = 0;
          _q = 1;
     }
     if(_q < 0)  // if the denominator is a negative number,
     {           // put the negative sign in the numerator
          _p *= -1;
          _q *= -1;
     }
     int n = gcf(_p, _q);  // reduce the rational number by
     _p = _p / n;          // dividing the numerator and
     _q = _q / n;          // denominator by the greatest
}                          // common factor

/* Function: takes two integers and finds the lowest common
             multiple using the gcf function */
int Rational::lcm(int q1, int q2)
{
     return(q1 / gcf(q1, q2)) * q2;
}
