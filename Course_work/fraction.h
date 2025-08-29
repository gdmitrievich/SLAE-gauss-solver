#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

struct Fraction {
   private:
    int gcd(int a, int b) const;

    Fraction& shrink();
    Fraction& getShrinkedCopy() const;

   public:
    int n;
    int d;

    Fraction();
    Fraction(int n);
    Fraction(int n, int d);

    Fraction operator-() const;
    Fraction operator-(const Fraction& f) const;
    Fraction operator+(const Fraction& f) const;
    Fraction operator*(const Fraction& f) const;
    Fraction operator/(const Fraction& f) const;

    Fraction& operator=(const Fraction& f);

    bool operator==(const Fraction& f) const;
    bool operator!=(const Fraction& f) const;

    bool operator<(const Fraction& f) const;
    bool operator<=(const Fraction& f) const;
    bool operator>(const Fraction& f) const;
    bool operator>=(const Fraction& f) const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    friend std::istream& operator>>(std::istream& is, Fraction& f);
};

#endif // !FRACTION_H
