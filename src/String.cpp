
#include "String.h"


using namespace std;

enum {
    PLUS = '+', MINUS = '-', MULT = '*', DIV = '/'
};

bool replace(string & str, const string & from, const string & to) {
    size_t start_pos = str.find(from);
    if (start_pos == -1u)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

float toFloat(const string & str) {
    if (str.find_first_not_of("-.0123456789") != str.npos)
        return 0; // erreur, not a valid string
    bool dot = false;
    UShort power = 1;
    Short sign = 1;
    float out = 0;
    for (UInt i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-')
            sign = -1;
        else if (str[i] == '.')
            dot = true;
        else if (str[i] >= '0' && str[i] <= '9') {
            if (dot) {
                power = power * 10;
                out = out + (float) (str[i] - '0') / power;
            } else {
                out = out * 10 + (float) (str[i] - '0');
            }
        }
    }
    return sign * out;
}

Int toInt(const string & str) {
    if (str.find_first_not_of("-0123456789") != str.npos)
        return 0; // erreur, not a valid integer string
    Int out = 0;
    Int sign = 1;
    for (UInt i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-')
            sign = -1;
        else if (str[i] >= '0' && str[i] <= '9')
            out = out * 10 + (str[i] - '0');
    }
    return sign * out;
}

string toString(const Short & value) {
    string out = "";
    string sign = "";
    Short v = value;
    if (v == 0)
        out = "0";
    else {
        if (v < 0) {
            v = -v;
            sign = "-";
        }
        while (v != 0) {
            char in = '0' + (v % 10);
            out = in + out;
            v = v / 10;
        }
    }
    return sign + out;
}

string toString(const Int & value) {
    string out = "";
    string sign = "";
    Int v = value;
    if (v == 0)
        out = "0";
    else {
        if (v < 0) {
            v = -v;
            sign = "-";
        }
        while (value != 0) {
            char in = '0' + (v % 10);
            out = in + out;
            v = v / 10;
        }
    }
    return sign + out;
}

string toString(const Long & value) {
    string out = "";
    string sign = "";
    Long v = value;
    if (v == 0)
        out = "0";
    else {
        if (v < 0) {
            v = -v;
            sign = "-";
        }
        while (v != 0) {
            char in = '0' + (v % 10);
            out = in + out;
            v = v / 10;
        }
    }
    return sign + out;
}

string toString(const float & value, const UShort & length) {
    string out = "";
    Int left = 0, right = 0;
    float mantis;
    left = (int) value;
    mantis = value - left;
    if (length > 0)
        right = (int) (mantis * pow(10, length));
    out += toString(left);
    if (right != 0)
        out += "." + toString(right > 0 ? right : -right);
    return out;
}

float expressionValue(const string & expr) {
    for (Int i = expr.length() - 2; i >= 0; i--) //assuming last character will not be an operand
    {
        switch (expr.at(i)) {
            case MULT:
                return expressionValue(expr.substr(0, i)) *
                        expressionValue(expr.substr(i + 1, expr.length() - i - 1));
            case DIV:
                return expressionValue(expr.substr(0, i)) /
                        expressionValue(expr.substr(i + 1, expr.length() - i - 1));
        }
    }
    for (Int i = expr.length() - 2; i >= 0; i--) //assuming last character will not be an operand
    {
        switch (expr.at(i)) {
            case PLUS:
                return expressionValue(expr.substr(0, i)) +
                        expressionValue(expr.substr(i + 1, expr.length() - i - 1));
            case MINUS:
                return expressionValue(expr.substr(0, i)) -
                        expressionValue(expr.substr(i + 1, expr.length() - i - 1));
        }
    }
    return toFloat(expr);
}

string inter(const string & str, const string & left, const string & right) {
    Int start = str.find(left);
    if (start != -1) {
        Int end = str.find(right);
        if (end != -1) {
            return str.substr(start + left.length(), end - start - right.length());
        }
    }
    return string("");
}

std::string readUntil(std::string & str, const std::string & end) {
    if (str == "")
        return std::string("");
    Int stop = str.find_first_of(end);
    if (stop == -1)
        return std::string("");

    std::string temp = str.substr(0, stop);
    str = str.substr(stop + 1);
    if (temp == "")
        return str;
    return temp;
}

string inParathesis(const string & in) {
    string out;
    Int a, b;
    a = in.find_first_of('(') + 1;
    b = in.find_last_of(')');
    if (a > -1 && b > -1)
        out = in.substr(a, b - a);
    return out;
}