/*
 Simran Soin
 CS2124
 Recitation 8
 Operator Overloading - Writing a class for rational numbers
 October 25, 2019
 */

#include "Rational.h"
#include <iostream>
using namespace std;
namespace CS2124{
void Rational::reduceRationalNumber(){
        int gcd = 0;
        int num1, num2;
        num1 = numerator;
        num2 = denominator;
        while (abs(num1) >= 1 && abs(num2) >= 1){
            if (num1 % num2 == 0){
                gcd = num2;
                break;
            }
            int temp = num1;
            num1 = num2;
            num2 = temp % num2;
        }
        if (gcd != 0){
            numerator /= gcd;
            denominator /= gcd;
        }
    }

    ostream& operator<<(ostream& os, const Rational& rhs) {
        os << rhs.numerator << "/" << rhs.denominator;
        return os;
    }

    istream& operator>>(istream& is, Rational& rhs) {
        char slash;
        is >> rhs.numerator >> slash >> rhs.denominator;
        if (rhs.denominator < 0){
            rhs.denominator *= -1;
            rhs.numerator *= -1;
        }
        
        rhs.reduceRationalNumber();
        
        return is;
    }

    bool operator==(const Rational& lhs, const Rational& rhs){
        return (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
    }

    Rational operator+(const Rational& lhs, const Rational& rhs){
        Rational retval;
        int lhs_num = lhs.numerator * rhs.denominator;
        int rhs_num = rhs.numerator * lhs.denominator;
        retval.numerator = lhs_num + rhs_num;
        retval.denominator = lhs.denominator * rhs.denominator;
        retval.reduceRationalNumber();
        return retval;
    }

    bool operator<(const Rational& lhs, const Rational& rhs){
        // convert both to have the same common denominator
            // do so by multiplying numerators by each other's denominators
        int lhs_num = lhs.numerator * rhs.denominator;
        int rhs_num = rhs.numerator * lhs.denominator;
        return (lhs_num < rhs_num);
    }

    Rational& Rational::operator+=(const Rational& rhs){
        numerator *= rhs.denominator;
        int orig_lhs_den = denominator;
        denominator *= rhs.denominator;
        numerator += (rhs.numerator * orig_lhs_den);
        reduceRationalNumber();
        return *this;
    }


    //pre-increment i.e. ++x
    Rational& Rational::operator++(){
        numerator += denominator;
        reduceRationalNumber();
        return *this;
    }

    //post-increment i.e. x++
    Rational Rational::operator++(int){
        Rational retval(*this);
        numerator += denominator;
        reduceRationalNumber();
        return retval;
    }

    Rational::operator bool() const{
        return (numerator != 0);
    }

    bool operator!=(const Rational& lhs, const Rational& rhs){
        return !(lhs == rhs);
    }

    //pre increment (decrease and then return new value)
    Rational& operator-- (Rational& num){
        Rational decrement(-1, 1);
        num += decrement;
        return num;
    }

    //post decrement (decrease but return original value)
    Rational operator-- (Rational& num, int){
        Rational decrement(-1, 1);
        Rational orig_num(num);
        num += decrement;
        return orig_num;
    }

    bool operator <=(const Rational& lhs, const Rational& rhs){
        return (lhs < rhs || lhs == rhs);
    }

    bool operator >(const Rational& lhs, const Rational& rhs){
        return !(lhs < rhs) && !(lhs == rhs);
    }

    bool operator >=(const Rational& lhs, const Rational& rhs){
        return !(lhs < rhs);
    }
}
