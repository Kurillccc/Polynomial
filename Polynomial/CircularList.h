#pragma once

#include<iostream>

#include "Monom.h"

using namespace std;

class CyclicList
{
private:

	Monom* head;

public:

	CyclicList()
	{
		head = new Monom();
	}

	CyclicList(const CyclicList& other)
	{
		head = new Monom(*other.head);

		Monom* current = head;
		Monom* other_current = other.head->getNext();

		while (other_current != other.head)
		{
			current->setNext(new Monom(*other_current));
			current = current->getNext();
			other_current = other_current->getNext();
		}

		current->setNext(head);
	}

	~CyclicList()
	{
		Monom* current = head->getNext();

		while (current != head)
		{
			Monom* temp = current;
			current = current->getNext();
			delete temp;
		}

		delete head;
	}

	CyclicList& operator=(const CyclicList& other)
	{
		if (head->getNext() != head)
		{
			Monom* current = head->getNext();

			while (current != head)
			{
				Monom* temp = current;
				current = current->getNext();
				delete temp;
			}
		}

		head = new Monom(*other.head);

		Monom* current = head;
		Monom* other_current = other.head->getNext();

		while (other_current != other.head)
		{
			Monom* A = new Monom(other_current->getCoefficient(), other_current->getSV());

			current->setNext(A);
			current = current->getNext();

			other_current = other_current->getNext();
		}

		current->setNext(head);
		return *this;
	}



	void add(Monom monomial)
	{
		Monom* new_monomial = new Monom(monomial);

		int convolution = monomial.getSV();
		int coefficient = monomial.getCoefficient();

		Monom* current = head;
		while (current->getNext() != head && current->getNext()->getSV() > convolution)
		{
			current = current->getNext();
		}

		if (convolution == current->getNext()->getSV())
		{
			int k = current->getNext()->getCoefficient();

			if (k + coefficient != 0)
			{
				current->getNext()->setCoefficient(k + coefficient);
			}
			else
			{
				Monom* A = current->getNext();
				current->setNext(current->getNext()->getNext());
				A->setNext(nullptr);
				delete A;
			}
		}
		else
		{
			new_monomial->setNext(current->getNext());
			current->setNext(new_monomial);
		}
	}

	void add(int coefficient, int convolution)
	{
		Monom* monomial = new Monom(coefficient, convolution);
		Monom* current = head;

		while (current->getNext() != head && current->getNext()->getSV() > convolution)
		{
			current = current->getNext();
		}

		if (convolution == current->getNext()->getSV())
		{
			int k = current->getNext()->getCoefficient();

			if (k + coefficient != 0)
			{
				current->getNext()->setCoefficient(k + coefficient);
			}
			else
			{
				Monom* A = current->getNext();

				current->setNext(current->getNext()->getNext());
				A->setNext(nullptr);

				delete A;
			}
		}
		else
		{
			monomial->setNext(current->getNext());
			current->setNext(monomial);
		}
	}

	void erase(int coefficient, int convolution)
	{
		Monom* A = head;
		while (A->getNext() != head)
		{
			if (A->getNext()->getCoefficient() == coefficient && A->getNext()->getSV() == convolution)
			{
				Monom* B = A->getNext();

				A->setNext(B->getNext());
				delete B;
				break;
			}
			A = A->getNext();
		}
	}

	CyclicList operator +(const CyclicList& list)
	{
		Monom* current = list.head->getNext();

		while (current != list.head)
		{
			this->add(*current);
			current = current->getNext();
		}

		return *this;
	}

	CyclicList operator *(int k)
	{
		if (k == 0)
		{
			CyclicList result;
			return result;
		}

		CyclicList result(*this);
		Monom* current = result.head->getNext();

		while (current != result.head)
		{
			current->setCoefficient(current->getCoefficient() * k);
			current = current->getNext();
		}

		return result;
	}

	CyclicList operator -(CyclicList tmp)
	{
		CyclicList res(*this);

		res = res + tmp * (-1);

		return res;
	}

	CyclicList multiply(CyclicList list, int maxSt, int n)
	{
		CyclicList result;
		Monom* current = head->getNext();

		while (current != head)
		{
			Monom* newCurrent = list.head->getNext();
			while (newCurrent != list.head)
			{
				result.add(current->multiply(*newCurrent, maxSt, n));
				newCurrent = newCurrent->getNext();
			}

			current = current->getNext();
		}

		return result;
	}

	void printList(int maxSt, int n)
	{
		Monom* current = head->getNext();

		if (current != head)
		{
			cout << current->mtostr(maxSt, n);
			current = current->getNext();
		}

		while (current != head)
		{
			if (current->getCoefficient() > 0)
			{
				cout << "+" << current->mtostr(maxSt, n);
			}
			else
			{
				cout << current->mtostr(maxSt, n);
			}

			current = current->getNext();
		}

		cout << endl;
	}

	Monom* getHead()
	{
		return head;
	}

	string getStringList(int maxSt, int n)
	{
		string result = "";
		Monom* current = head->getNext();

		if (current != head)
		{
			result = result + current->mtostr(maxSt, n);
			current = current->getNext();
		}
		while (current != head)
		{
			if (current->getCoefficient() > 0)
			{
				result = result + "+" + current->mtostr(maxSt, n);
			}
			else
			{
				result = result + current->mtostr(maxSt, n);
			}
			current = current->getNext();
		}

		return result;
	}
};