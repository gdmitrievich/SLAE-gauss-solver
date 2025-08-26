#include "fraction.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

// Source: https://en.wikipedia.org/wiki/Greatest_common_divisor
int Fraction::gcd(int a, int b) const {
    a = abs(a), b = abs(b);
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

Fraction& Fraction::shrink() {
    int gcdN = n > d ? gcd(n, d) : gcd(d, n);
    n /= gcdN;
    d /= gcdN;

    return *this;
}

Fraction& Fraction::getShrinkedCopy() const {
    return Fraction(n, d).shrink();
}

Fraction::Fraction() : n(), d(1) {}
Fraction::Fraction(int n1) : n(n1), d(1) {}
Fraction::Fraction(int n1, int d1) : n(n1), d(d1) {
    if (d1 == 0) {
        std::cout << "Ќоль в знаменателе!";
        // јварийно завершает выполнение программы.
        exit(EXIT_FAILURE);
    }

    // ≈сли числитель равен нулю, то уже без разницы, что находитс€ в
    // знаменателе, поэтому в качестве значени€ там будет 1.
    if (n == 0) {
        d = 1;
    }
    // ≈сли дробь отрицательна€, то знак отрицани€ должен быть в числителе, или
    // его вообще не должно быть, если он присутствует и в числителе, и в
    // знаменателе.
    if (n < 0 && d < 0 || n > 0 && d < 0) {
        n = -n;
        d = -d;
    }

    shrink();
}

Fraction Fraction::operator-() const {
    return Fraction {-n, d};
}

Fraction Fraction::operator-(const Fraction& f) const {
    return Fraction {n * f.d - f.n * d, d * f.d};
}

Fraction Fraction::operator+(const Fraction& f) const {
    return Fraction {n * f.d + f.n * d, d * f.d};
}

Fraction Fraction::operator*(const Fraction& f) const {
    return Fraction {n * f.n, d * f.d};
}

Fraction Fraction::operator/(const Fraction& f) const {
    if (f.n == 0) {
        std::cout << "ƒеление на ноль!";
        // јварийно завершает выполнение программы.
        exit(EXIT_FAILURE);
    } else {
        return Fraction {n * f.d, f.n * d};
    }
}

Fraction& Fraction::operator=(const Fraction& f) {
    if (this == &f)
        return *this;

    n = f.n;
    d = f.d;

    return *this;
}

bool Fraction::operator==(const Fraction& f) const {
    Fraction f1 = getShrinkedCopy();
    Fraction f2 = f.getShrinkedCopy();

    return f1.n == f2.n && f1.d == f2.d;
}

bool Fraction::operator!=(const Fraction& f) const {
    return !(*this == f);
}

bool Fraction::operator<(const Fraction& f) const {
    Fraction f1 = getShrinkedCopy();
    Fraction f2 = f.getShrinkedCopy();
    return f1.n * f2.d < f2.n * f1.d;
};

bool Fraction::operator<=(const Fraction& f) const {
    return !(f < *this);
}

bool Fraction::operator>(const Fraction& f) const {
    return f < *this;
}

bool Fraction::operator>=(const Fraction& f) const {
    return !(*this < f);
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    if (std::abs(f.d) <= 1)
        os << f.n;
    else
        os << f.n << '/' << f.d;

    return os;
}

// Think about it later..
std::istream& operator>>(std::istream& is, Fraction& f) {
    is >> f.n;
    return is;
}
