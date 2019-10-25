/* rec08_h */
#ifndef rec08_h
#define rec08_h
#include <iostream>

namespace CS2124{
    class Rational{
        friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
        friend std::istream& operator>>(std::istream& is, Rational& rhs);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend Rational operator+(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);
        
    public:
        void reduceRationalNumber();
        Rational(int num = 0, int den = 1): numerator(num), denominator(den){
            if (denominator < 0){
                denominator *= -1;
                numerator *= -1;
            }
            reduceRationalNumber();
            
        };
        
        Rational& operator+=(const Rational& rhs);
        
        Rational& operator++(); //pre-increment i.e. ++x
        
        Rational operator++(int); //post-increment i.e. x++
        
        explicit operator bool() const;
    private:
        int numerator;
        int denominator;
    };


    bool operator!=(const Rational& lhs, const Rational& rhs);

    //pre increment (decrease and then return new value)
    Rational& operator-- (Rational& num);

    //post decrement (decrease but return original value)
    Rational operator-- (Rational& num, int);

    bool operator <=(const Rational& lhs, const Rational& rhs);

    bool operator >(const Rational& lhs, const Rational& rhs);

    bool operator >=(const Rational& lhs, const Rational& rhs);

}
#endif
