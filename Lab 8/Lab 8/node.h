#pragma once
#include "Potion.h"
template <class T>
class node
{
public:
	template <class T>
	friend class list;
	static void addCount()
	{
		count++;
	}

private:

	static int count;
	node<T>();
	node<T>(const T data);
	node<T>(const node<T>& n);
	node& operator=(const node<T>& rhs);
	T getData();
	node<T>* getNext();
	~node();
	node<T>* m_next;
	T m_data;
};

/*
	Purpose: This is the default constructor for the templated node class that initializes the next pointer to nullptr
	and initializes m_data to a default instance of whatever object is being called.
*/

template <class T>
node<T>::node() : m_next(nullptr), m_data()
{
	addCount();
}

/*
	Purpose: This is the 1 arg constructor for the templated node class that initializes the next pointer to nullptr
	and initializes m_data by calling the one arg constructor of whatever data type is used
*/
template <class T>
node<T>::node(const T data) : m_next(nullptr), m_data(data)
{
	addCount();
}

/*
	Purpose: This is the copy constructor for the templated node class that initializes the next pointer to
	the next pointer of the node<T> m_next pointer and initializes m_data by using the op= of whatever the object is.
*/
template <class T>
node<T>::node(const node<T> & n)
{
	addCount();
	m_next = n.m_next;
	m_data = n.m_data;
}

/*
	Purpose: This is the op= for the templated node class that initializes the next pointer to
	the next pointer of the node<T> m_next pointer and initializes m_data by using the op= of whatever the object is.
*/
template <class T>
node<T> & node<T>::operator=(const node<T> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
	}

	return *this;
}

/*
	Purpose: This function returns the m_data.
*/
template <class T>
T node<T>::getData()
{
	return m_data;
}

/*
	Purpose: This function returns the m_next pointer.
*/
template <class T>
node<T> * node<T>::getNext()
{
	return m_next;
}

/*
	Purpose: This is the destructor for the node class.
*/
template <class T>
node<T>::~node()
{
}

