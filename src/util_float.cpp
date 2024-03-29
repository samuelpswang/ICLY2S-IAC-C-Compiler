#include "util_float.hpp"

// name: first non zero digit
// returns index of first non-zero digit of a fractional num
int _fnzd(double f) {
    f = f - (int) f;
    int count = -1;
    while (f < 1) {
        f *= 2;
        count++;
    }
    return count;
}

// name: string float to string binary integral part
// returns the unsigned binary representation of the INTEGRAL part of a float
std::string _sftosb_i(double f) {
    int num = (int) f;
    std::string result = "";
    while (num > 0) {
        result = std::to_string(num%2) + result;
        num /= 2;
    }
    return result;
}

// name: string float to string binary fractional part
// returns the unsigned binary representation of the FRACTIONAL part of a float
std::string _sftosb_f(double f, int length) {
    double num = f - (int) f;
    std::string result = "";
    for (int i = 0; i < length; i++) {
        num *= 2;
        std::cout << "> " << num << std::endl;
        if (num >= 1) {
            result += "1";
            num -= 1;
        } else {
            if (i == length-1) { // last digit
                if (num > 0) result += "1";
                else result += "0";
            } else {
                result += "0";
            }
        }
    }
    return result;
}

// name: string binary to string integer
// returns the decimanl representatinl of a unsinged binary string
std::string _sbtosi(std::string bin) {
    long num = 0;
    for (int i = 0; i < 32; i++) {
        if (bin[i] == '0') {
            num *= 2;
        } else {
            num *= 2;
            num += 1;
        }
    }
    return std::to_string(num);
}

// returns the IEEE754 representation of float in decimal format
std::string ieee754(std::string s) {
    double num = std::stod(s);
    
    // 1 sign
    std::string sign;
    if (num > 0) { sign = "0"; }
    else { sign = "1"; num *= -1;}

    // 2 mantissa & exp
    std::string mantissa;
    int exp_num = 127;
    if (num > 1) {
        std::string int_bin = _sftosb_i(num);
        if (int_bin.size() > 23) {
            mantissa = int_bin.substr(1, 23);
            exp_num += int_bin.size()-1;
        } else {
            std::string frac_bin = _sftosb_f(num, 23-int_bin.size()+1);
            mantissa = int_bin.substr(1, int_bin.size()-1) + frac_bin;
            exp_num += int_bin.size()-1;
        }
    } else {
        int fnzd = _fnzd(num);
        std::string frac_bin = _sftosb_f(num, 23+fnzd+1);
        mantissa = frac_bin.substr(fnzd+1, 23);
        exp_num -= fnzd+1;
    }

    // 3 exponent
    std::string exp;
    exp = _sftosb_i(exp_num);
    while (exp.size() < 8) {
        exp = "0" + exp;
    }

    // 4 assembling
    return _sbtosi(sign + exp + mantissa);
}
