#pragma once
#include "cString.h"
template <class T>
class DynamicArray
{
public:
	DynamicArray<T>();
	~DynamicArray<T>();
	DynamicArray<T>(const DynamicArray& arr);
	DynamicArray& operator=(const DynamicArray& arr);
	int getElements();
	void Insert(const T& to_add);
	void Delete(const T& to_delete);
	void Sort();
	void display();

private:
	int Find(const T& target);
	T* m_array;
	int m_elements;
};

template <class T>
DynamicArray<T>::DynamicArray() : m_array(nullptr), m_elements(0)
{
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray & arr)
{
	m_array = new T[arr.m_elements];

	for (int i = 0; i < arr.m_elements; i++)
	{
		*(m_array + i) = *(arr.m_array + i);
	}
	m_elements = arr.m_elements;
}

template <class T>
DynamicArray<T> & DynamicArray<T>::operator=(const DynamicArray & arr)
{
	if (this != &arr)
	{
		delete[] m_array;
		m_array = new T[arr.m_elements];

		for (int i = 0; i < arr.m_elements; i++)
		{
			*(m_array + i) = *(arr.m_array + i);
		}

		m_elements = arr.m_elements;
	}
	return *this;
}

template <class T>
int DynamicArray<T>::getElements()
{
	return m_elements;
}

template <class T>
void DynamicArray<T>::Insert(const T & to_add)
{

	T* tempT = new T[m_elements + 1];
	T temp;

	for (int i = 0; i < m_elements; i++)
	{
		*(tempT + i) = *(m_array + i);
	}

	*(tempT + m_elements) = to_add;

	m_elements++;
	delete[] m_array;
	m_array = new T[m_elements];
	for (int i = 0; i < m_elements; i++)
	{
		for (int j = 0; j < m_elements - 1; j++)
		{
			if ((tempT + j) < (tempT + j + 1))
			{
				temp = *(tempT + j);
				*(tempT + j) = *(tempT + j + 1);
				*(tempT + j + 1) = temp;
			}
		}
	}

	for (int i = 0; i < m_elements; i++)
	{
		*(m_array + i) = *(tempT + i);
	}
	delete[] tempT;
}

template <class T>
void DynamicArray<T>::Delete(const T & to_delete)
{
	int position = 0;
	try { position = Find(to_delete); }

	catch (cString error)
	{
		error.display();
		cout << endl;
	}
	T* tempT = new T[m_elements];
	T temp;
	for (int i = 0; i < m_elements; i++)
	{
		*(tempT + i) = *(m_array + i);
	}

	for (int i = 0; i < m_elements; i++)
	{
		for (int j = 0; j < m_elements - 1; j++)
		{
			if ((tempT + j) == to_delete)
			{
				temp = *(tempT + j);
				*(tempT + j) = *(tempT + j + 1);
				*(tempT + j + 1) = temp;
			}
		}
	}
	m_elements -= 1;
	for (int i = 0; i < m_elements; i++)
	{
		*(m_array + i) = *(tempT + i);
	}
	delete[] tempT;
	this->Sort();
}

template <class T>
void DynamicArray<T>::Sort()
{
	T temp;
	for (int i = 0; i < m_elements; i++)
	{
		for (int j = 0; j < m_elements - 1; j++)
		{
			if ((m_array + j) < (m_array + j + 1))
			{
				temp = *(m_array + j);
				*(m_array + j) = *(m_array + j + 1);
				*(m_array + j + 1) = temp;
			}
		}
	}
}

template <class T>
void DynamicArray<T>::display()
{
	for (int i = 0; i < m_elements; i++)
	{
		(m_array + i)->display();
	}
}

template <class T>
int DynamicArray<T>::Find(const T & target)
{
	int temp = -1;
	for (int i = 0; i < m_elements; i++)
	{
		if (target == (m_array + i))
		{
			temp = i;
		}
	}
	if (temp == -1)
	{
		throw cString("T not found");
	}
	return temp;

}

template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete[] m_array;
	m_array = nullptr;
	m_elements = 0;
}
