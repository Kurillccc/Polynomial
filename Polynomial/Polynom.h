#pragma once

#include "CircularList.h"

class Polynom 
{
private:

    void splitString(string str, int& k, string* w)
    {
        string zn = "+-";
        k = 0;
        str += " ";

        for (int i = 0; i < str.length(); i++) 
        {
            int l = zn.find(str[i]);

            if (l >= 0 && l < zn.length()) 
            {
                if (w[k].length() > 0) 
                {
                    k++;
                }

                w[k] = str[i];
                w[++k] = "";
            }
            else 
            {
                if (str[i] == ' ') 
                {
                    if (w[k].length() > 0) 
                    {
                        w[++k] = "";
                    }
                }
                else 
                {
                    w[k] = w[k] + str[i];
                }
            }
        }
    }

    CyclicList memory;
    int maxSt;
    int n;

public:

    Polynom(string str, int maxSt, int n) 
    {
        int flag = 0;

        this->maxSt = maxSt + 1;
        this->n = n;

        string* stringMemory = new string[str.length()];
        string* stringMemoryTmp = new string[str.length()];

        int k = 0;
        int newK = 0;

        splitString(str, k, stringMemoryTmp);
        for (int i = 0; i < k; i++) 
        {
            if (stringMemoryTmp[i] != "+") 
            {
                if (stringMemoryTmp[i] == "-") 
                {
                    i++;
                    stringMemory[newK++] = "-" + stringMemoryTmp[i];
                }
                else 
                {
                    stringMemory[newK++] = stringMemoryTmp[i];
                }
            }
        }
        for (int i = 0; i < newK; i++) 
        {
            Monom tmp(stringMemory[i], this->maxSt, this->n);
            memory.add(tmp);
        }
    }

    Polynom() { }

    Polynom(const Polynom& tmp) 
    {
        maxSt = tmp.maxSt;
        n = tmp.n;
        memory = *new CyclicList(tmp.memory);
    }

    Polynom& operator =(Polynom tmp) 
    {
        maxSt = tmp.maxSt;
        n = tmp.n;
        memory = *new CyclicList(tmp.memory);

        return*this;
    }

    void add(string str) 
    {
        string* stringMemory = new string[str.length()];
        int k = 0;

        splitString(str, k, stringMemory);
        for (int i = 0; i < k; i++) 
        {
            Monom tmp(stringMemory[i], maxSt, n);
            memory.add(tmp);
        }
    }

    Polynom operator +(const Polynom& tmp) 
    {
        Polynom X(*this);

        if (maxSt == tmp.maxSt && n == tmp.n) 
        {
            X.memory = X.memory + tmp.memory;
        }

        return X;
    }

    Polynom operator -(const Polynom& tmp) 
    {
        Polynom X(*this);

        if (maxSt == tmp.maxSt && n == tmp.n) 
        {
            X.memory = X.memory - tmp.memory;
        }

        return X;
    }

    Polynom operator *(int k) 
    {
        Polynom X(*this);
        X.memory = X.memory * k;

        return X;
    }

    Polynom operator *(const Polynom& tmp) 
    {
        Polynom X(*this);

        if (maxSt == tmp.maxSt && n == tmp.n) 
        {
            X.memory = X.memory.multiply(tmp.memory, maxSt, n);
        }

        return X;
    }


    int getMaxDegree() 
    {
        return maxSt;
    }

    int getCount() 
    {
        return n;
    }

    void printPolynomial() 
    {
        memory.printList(maxSt, n);
    }

    bool isMaximumDegreeExceeded() 
    {
        Monom* current = memory.getHead()->getNext();

        while (current != memory.getHead()) 
        {
            if (current->getSV() == -2) 
            {
                return true;
            }
        }

        return false;
    }

    string getStringPolynomial()
    {
        return memory.getStringList(maxSt, n);
    }
};