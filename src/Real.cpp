
#include "Real.h"

Real::Real() {
    setValue(0);
}

Real::Real(const int & value) {
    setValue(value);
}

Real::Real(const float & value) {
    setValue(value);
}

Real::Real(const Real & value) {
    setValue(value);
}

Real& Real::operator=(const Real & b) {
    if (this != &b)
        setValue(b);
    return *this;
}

void Real::setValue(const int & value) {
    this->value = value * 100;
}

void Real::setValue(const float & value) {
    this->value = (int) (value * 100);
}

void Real::setValue(const Real & value) {
    this->value = value.value;
}

int Real::toInt() const {
    return value / 100;
}

float Real::toFloat() const {
    return ((float) value) / 100.f;
}

Real operator+(const Real & a, const Real & b) {
    Real out;
    out.value = (a.value) + (b.value);
    return out;
}

Real operator-(const Real & a, const Real & b) {
    Real out;
    out.value = (a.value) - (b.value);
    return out;
}

Real operator*(const Real & a, const Real & b) {
    Real out;
    out.value = (a.value * b.value) / 100;
    return out;
}

Real operator/(const Real & a, const Real & b) {
    Real out;
    out.value = (a.value * 100) / b.value;
    return out;
}
