#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Monom {
private:
    int getCoefficient(string str) {
        if (str.empty()) {
            return 0;
        }
        int position = str.find("x");
        int result = 1;
        if (position != string::npos) {
            str.erase(position);
            if (position > 1) {
                result = stoi(str);
            }
            else {
                if (str >= "0" && str <= "9") {
                    result = stoi(str);
                }
                else {
                    str += "1";
                    result = stoi(str);
                }
            }
        }
        else {
            result = stoi(str);
        }
        return result;
    }

    int getCoefficientSV(string str, int maxDegree, int count) {
        int* degree = new int[count]();
        for (int i = 0; i < count; i++) {
            degree[i] = 0;
        }

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == 'x') {
                i++;
                int number = 0;
                while (isdigit(str[i])) {
                    number = number * 10 + str[i] - '0';
                    i++;
                }
                int degreeValue = 0;
                if (str[i] == '^') {
                    i++;
                    while (isdigit(str[i])) {
                        degreeValue = degreeValue * 10 + str[i] - '0';
                        i++;
                    }
                }
                else {
                    degreeValue = 1;
                }
                if (degreeValue >= maxDegree) {
                    return -2;
                }
                if (number <= count) {
                    degree[number - 1] = degreeValue;
                }
                i--;
            }
        }

        int result = 0;
        int tmpCount = count - 1;
        for (int i = 0; i < count; i++) {
            result += degree[i] * pow(maxDegree, tmpCount--);
        }
        delete[] degree;
        return result;
    }

    int coefficient;
    int SV;
    Monom* next;

public:
    Monom(int coefficient = 0, int SV = -1) {
        this->coefficient = coefficient;
        this->SV = SV;
        next = this;
    }

    Monom(string str, int maxDegree, int count) {
        coefficient = getCoefficient(str);
        SV = getCoefficientSV(str, maxDegree, count);
        next = this;
    }

    ~Monom() {
        next = nullptr;
    }

    Monom(const Monom& tmp) {
        coefficient = tmp.coefficient;
        SV = tmp.SV;
        next = this;
    }

    Monom& operator =(Monom tmp) {
        coefficient = tmp.coefficient;
        SV = tmp.SV;
        next = this;
        return*this;
    }

    Monom operator +(Monom tmp) {
        Monom res;
        if (SV == tmp.SV){
            if (coefficient + tmp.coefficient != 0)
            {
                res.coefficient = coefficient + tmp.coefficient;
                res.SV = SV;
            }
        }
        return res;
    }

    Monom operator -(Monom tmp) {
        Monom res;
        if (SV == tmp.SV) {
            if (coefficient - tmp.coefficient != 0)
            {
                res.coefficient = coefficient - tmp.coefficient;
                res.SV = SV;
            }
        }
        return res;
    }

    Monom multiply(Monom tmp, int maxDegree, int count) const {
        Monom res;
        int* Pth;
        int* Ptm;
        Ptm = new int[count];
        Pth = new int[count];
        int Dv = SV;
        for (int i = 0; i < count; i++)
        {
            Pth[i] = Dv % maxDegree;
            Dv = Dv / maxDegree;
        }
        Dv = tmp.SV;
        for (int i = 0; i < count; i++)
        {
            Ptm[i] = Dv % maxDegree;
            Dv = Dv / maxDegree;
        }

        for (int i = 0; i < count; i++)
        {
            Pth[i] += Ptm[i];
            if (Pth[i] > maxDegree)
            {
                Monom res(0, -2);
                return res;
            }
        }
        res.SV = 0;
        for (int i = count -1; i > -1; i--)
        {
            res.SV = res.SV * maxDegree + Pth[i];
        }
        res.coefficient = coefficient * tmp.coefficient;
        return res;
    }

    string getStringMonomial(int maxDegree, int count) {
        if (SV == -2) {
            return "Exceeded the maximum degree";
        }
        string result = "";
        int tmp = SV;
        while (tmp > 0) {
            int degreeValue = tmp % maxDegree;
            if (degreeValue > 1) {
                result = "x" + to_string(count) + "^" + to_string(degreeValue) + result;
            }
            else if (degreeValue == 1) {
                result = "x" + to_string(count) + result;
            }
            count--;
            tmp /= maxDegree;
        }
        if (coefficient != 1) {
            if (coefficient == -1) {
                result = "-" + result;
            }
            else {
                result = to_string(coefficient) + result;
            }
        }
        return result;
    }

    int getCoefficient() {
        return coefficient;
    }

    int getSV() {
        return SV;
    }

    Monom* getNext() {
        return next;
    }

    void setCoefficient(int coefficient) {
        this->coefficient = coefficient;
    }

    void setSV(int SV) {
        this->SV = SV;
    }

    void setNext(Monom* next) {
        this->next = next;
    }
};

