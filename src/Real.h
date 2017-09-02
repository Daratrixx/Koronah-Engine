/* 
 * File:   Real.h
 * Author: ANTOINE
 *
 * Created on 3 may 2017, 21:21
 */

#ifndef REAL_H
#define REAL_H

class Real {
public:
    Real();
    Real(const int & value);
    Real(const float & value);
    Real(const Real & value);
    Real& operator=(const Real & b);
    void setValue(const int & value);
    void setValue(const float & value);
    void setValue(const Real & value);

    int toInt() const;
    float toFloat() const;

    int value;
};

Real operator+(const Real & a, const Real & b);
Real operator-(const Real & a, const Real & b);
Real operator*(const Real & a, const Real & b);
Real operator/(const Real & a, const Real & b);

#endif /* REAL_H */

