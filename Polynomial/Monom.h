#pragma once

#include <string>

using namespace std;

class Monom
{
private:

	int A; // К/ф
	int Sv;
	Monom* Next;

public:

	Monom(int A_ = 1, int Sv_ = -1)
	{
		A = A_;
		Sv = Sv_;
		Next = this; // Закрутили на себя
	}

	~Monom()
	{
		Next = NULL; // Все вернется компьютеру, а иначе он ходил бы по кругу, пытаясь удалить один и тот же указатель 
	}

	Monom(const Monom& tmp)
	{
		// Отслеживать в конструкторе копирования списка
		Next = this;
		A = tmp.A;
		Sv = tmp.Sv;
	}

	Monom& operator = (Monom tmp)
	{
		A = tmp.A;
		Sv = tmp.Sv;
		Next = tmp.Next;
		return *this;
	}

	int GetK(string str)
	{
		int L = str.find("X");
		if (L == -1) return stoi(str);
		else
		{
			str.erase(L, str.size() - 1); // До конца

			if (str.size() > 1) return stoi(str);
			else if (str == "-") return -1;
			else if (str == "+") return 1;
			else return str[0] - 48;
		}
	}

	int GetSv (string str, int maxSt, int n)
	{
		int* degree = new int[n]();

		for (int i = 0; i < n; i++) 
		{
			degree[i] = 0;
		}

		for (int i = 0; i < str.length(); i++) 
		{
			if (str[i] == 'X') 
			{
				i++;
				int number = 0;

				while (isdigit(str[i])) 
				{
					number = number * 10 + str[i] - '0';
					i++;
				}

				int degreeValue = 0;
				if (str[i] == '^') 
				{
					i++;
					while (isdigit(str[i])) 
					{
						degreeValue = degreeValue * 10 + str[i] - '0';
						i++;
					}
				}
				else 
				{
					degreeValue = 1;
				}
				if (degreeValue >= maxSt) 
				{
					return -2;
				}
				if (number <= n) 
				{
					degree[number - 1] = degreeValue;
				}

				i--;
			}
		}

		int result = 0;
		int tmpCount = n - 1;

		for (int i = 0; i < n; i++) 
		{
			result += degree[i] * pow(maxSt, tmpCount--);
		}

		delete[] degree;
		return result;
	}

	int MadeSv(int n, int maxSt, int* Pv)
	{
		Sv = 0;
		for (int i = n - 1; i >= 0; i--) Sv = Sv * maxSt + Pv[i];

		return Sv;
	}

	Monom(string str, int maxS = 10, int n = 6)
	{
		A = GetK(str);
		Sv = GetSv(str, maxS, n);
		Next = this;
	}

	string mtostr(int maxSt, int n)
	{
		string res = "";
		int Dv = Sv, l;

		if (Sv == -2)
		{
			return "Higher degree";
		}

		for (int i = n; i > 0; i--)
		{
			l = Dv % maxSt;

			if (l > 1) res += ('X' + to_string(i) + "^" + to_string(l));
			else if (l == 1) res += ('X' + to_string(i));

			Dv /= maxSt;
		}

		Dv /= maxSt;

		if (A != 1)
		{
			if (A == -1) res = " - " + res;
			else res = to_string(A) + res;
		}

		return res;
	}

	Monom operator + (const Monom& tmp) const
	{
		Monom res;

		if (Sv == tmp.Sv)
		{
			if (A + tmp.A != 0)
			{
				res.A = tmp.A + A;
				res.Sv = Sv;
			}
		}

		return res;
	}

	Monom operator - (const Monom& tmp) const
	{
		Monom res;

		if (Sv == tmp.Sv)
		{
			if (tmp.A - A != 0)
			{
				res.A = A - tmp.A;
				res.Sv = Sv;
			}
		}

		return res;
	}

	Monom multiply(Monom tmp, int maxSt, int n)
	{
		Monom res;

		int* Pth;
		int* Ptm;

		Ptm = new int[n];
		Pth = new int[n];

		int Dv = Sv;
		for (int i = 0; i < n; i++)
		{
			Pth[i] = Dv % maxSt;
			Dv = Dv / maxSt;
		}

		Dv = tmp.Sv;
		for (int i = 0; i < n; i++)
		{
			Ptm[i] = Dv % maxSt;
			Dv = Dv / maxSt;
		}

		for (int i = 0; i < n; i++)
		{
			Pth[i] += Ptm[i];
			if (Pth[i] > maxSt)
			{
				Monom res(0, -2);
				return res;
			}
		}

		res.Sv = 0;
		for (int i = n - 1; i > -1; i--)
		{
			res.Sv = res.Sv * maxSt + Pth[i];
		}
		res.A = A * tmp.A;

		return res;
	}


	int getCoefficient() 
	{
		return A;
	}

	int getSV() 
	{
		return Sv;
	}

	Monom* getNext() 
	{
		return Next;
	}

	void setCoefficient(int coefficient) 
	{
		this->A = coefficient;
	}

	void setSV(int SV) 
	{
		this->Sv = SV;
	}

	void setNext(Monom* next) 
	{
		this->Next = next;
	}
};