
#include "String.h"


using namespace std;

enum {
    PLUS = '+', MINUS = '-', MULT = '*', DIV = '/'
};

bool replace(string &str, string from, string to) {
    size_t start_pos = str.find(from);
    if (start_pos == -1u)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

float toFloat(string str) {
    bool dot = false;
    int power = 1;
    int sign = 1;
    float out = 0;
    unsigned int i = 0u;
    for (; i < str.length(); i++) {
        if (str[i] == '-')
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

int toInt(string str) {
    int out = 0;
    for (unsigned int i = 0u; i < str.length(); i++)
        out = out * 10 + (str[i] - '0');
    return out;
}

string toString(int value) {
    string out = "";
    string sign = "";
    if (value == 0)
        out = "0";
    else {
        if (value < 0) {
            value = -value;
            sign = "-";
        }
        while (value != 0) {
            char in = '0' + (value % 10);
            out = in + out;
            value = value / 10;
        }
    }
    return sign + out;
}

string toString(float value, int length) {
    string out = "";
    int left = 0, right = 0;
    float mantis;
    left = (int) value;
    mantis = value - left;
    if (length > 0)
        right = (int) (mantis * pow(10, length));
    out += toString(left);
    if (right != 0)
        out += "." + toString(abs(right));
    return out;
}

float expressionValue(string expr) {
    for (int i = expr.length() - 2; i >= 0; i--) //assuming last character will not be an operand
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
    for (int i = expr.length() - 2; i >= 0; i--) //assuming last character will not be an operand
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

string inter(string str, string left, string right) {
    int start = str.find(left);
    if (start != -1) {
        int end = str.find(right);
        if (end != -1) {
            return str.substr(start + left.length(), end - start - right.length());
        }
    }
    return string("");
}

std::string readUntil(std::string &str, std::string end) {
    if (str == "")
        return std::string("");
    int stop = str.find_first_of(end);
    if (stop == -1)
        return std::string("");

    std::string temp = str.substr(0, stop);
    str = str.substr(stop + 1);
    if (temp == "")
        return str;
    return temp;
}