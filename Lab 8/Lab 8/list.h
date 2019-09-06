#pragma once
#include "node.h"
/*
This is a list class which is a friend of the node class. Together they make up a linked list.
*/
template <class T>
class list
{
public:
	list<T>();
	list<T>(const list<T>& rhs);
	list& operator=(const list<T>& rhs);
	void PushFront(T potion);
	void PushBack(T potion);
	T PopFront();
	T PopBack();
	T Front();
	T Back();
	int getNumNodes();
	void display();
	void Purge();
	void deleteNode(int offset);
	void displayPtr();
	T& GetIthElement(int offset);
	node<T>* getHead();
	node<T>* getTail();
	~list();


private:

	node<T>* m_head;
	node<T>* m_tail;
	int m_numNodes;
};

template <class T>
list<T>::list() : m_head(nullptr), m_tail(nullptr), m_numNodes(0)
{
}

template <class T>
list<T>::list(const list<T> & rhs) : m_head(nullptr), m_tail(nullptr), m_numNodes(0)
{
	if (rhs.m_head != nullptr)
	{
		node<T>* temp = rhs.m_head;
		m_numNodes = rhs.m_numNodes;
		m_head = new node<T>;
		m_head->m_data = temp->m_data;
		m_head->m_next = nullptr;
		node<T>* travel = m_head;

		temp = temp->m_next;
		while (temp != nullptr)
		{
			travel->m_next = new node<T>;
			travel = travel->m_next;
			travel->m_data = temp->m_data;
			travel->m_next = nullptr;
			temp = temp->m_next;
		}
		m_numNodes = rhs.m_numNodes;
		m_tail = travel;
	}


}

template <class T>
list<T> & list<T>::operator=(const list<T> & rhs)
{
	if (this != &rhs)
	{
		Purge();
		if (rhs.m_head != nullptr)
		{

			node<T>* temp = rhs.m_head;

			m_head = new node<T>;
			m_head->m_data = temp->m_data;
			m_head->m_next = nullptr;
			node<T>* travel = m_head;

			temp = temp->m_next;
			while (temp != nullptr)
			{
				travel->m_next = new node<T>;
				travel = travel->m_next;
				travel->m_data = temp->m_data;
				travel->m_next = nullptr;
				temp = temp->m_next;
			}
			m_numNodes = rhs.m_numNodes;
			m_tail = travel;
		}
	}

	return *this;
}

template <class T>
void list<T>::PushFront(T potion)
{
	node<T>* n = new node<T>(potion);

	n->m_next = m_head;
	m_head = n;
	m_numNodes++;
}

template <class T>
void list<T>::PushBack(T potion)
{
	node<T>* n = new node<T>(potion);

	if (m_head == nullptr)
	{
		m_head = n;
		m_numNodes++;
	}
	else
	{
		node<T>* travel = m_head;
		while (travel->m_next != nullptr)
		{
			travel = travel->m_next;
		}

		travel->m_next = n;
		m_tail = n;
		m_numNodes++;
	}
}

template <class T>
T list<T>::PopFront()
{
	if (m_head != nullptr)
	{
		node<T>* travel = m_head;
		T temp(m_head->m_data);

		m_head = m_head->m_next;

		delete travel;
		m_numNodes--;
		return temp;
	}
	else
	{
		throw cString("Empty list pop not completed");
	}
}

template <class T>
T list<T>::PopBack()
{
	if (m_head != nullptr)
	{
		node<T>* travel = m_head;
		while (travel->m_next != m_tail)
		{
			travel = travel->m_next;
		}
		T temp = m_tail->m_data;


		m_tail = travel;

		delete travel->m_next;
		m_tail->m_next = nullptr;
		m_numNodes--;
		return temp;
	}
	else
	{
		throw cString("empty list pop not completed");
	}
}

template <class T>
T list<T>::Front()
{
	T temp(m_head->m_data);
	return temp;
}

template <class T>
T list<T>::Back()
{
	T temp(m_tail->m_data);
	return temp;
}

template <class T>
int list<T>::getNumNodes()
{
	return m_numNodes;
}

template <class T>
void list<T>::display()
{
	if (m_head != nullptr)
	{
		node<T>* travel = m_head;
		while (travel != nullptr)
		{
			travel->m_data.display();
			travel = travel->m_next;
		}
	}

}

template <class T>
void list<T>::displayPtr()
{
	if (m_head != nullptr)
	{
		node<T>* travel = m_head;
		while (travel != nullptr)
		{
			travel->m_data->display();
			travel = travel->m_next;
		}
	}

}

template <class T>
void list<T>::Purge()
{
	node<T>* travel = m_head;
	node<T>* trail = nullptr;

	while (travel != nullptr)
	{
		trail = travel;
		travel = travel->m_next;

		delete trail;
	}
	m_head = nullptr;
	m_tail = nullptr;
	m_numNodes = 0;
}

template<class T>
void list<T>::deleteNode(int offset)
{
	node<T>* travel = m_head;
	node<T>* trail = m_head;
	for (int i = 0; i < offset; i++)
	{
		if (travel != nullptr)
		{
			trail = travel;
			travel = travel->m_next;
		}
		else
		{
			throw cString("invalid offset");
		}
	}
	if (travel == m_head)
	{
		m_head = travel->m_next;
	}
	trail->m_next = travel->m_next;
	delete travel;
	m_numNodes--;
}

template <class T>
T& list<T>::GetIthElement(int offset)
{
	node<T>* travel = m_head;
	
	int found = 0;
	for (int i = 0; i < offset; i++)
	{
		if (travel != nullptr)
		{
			travel = travel->m_next;
		}
		else
		{
			throw cString("invalid offset");
		}

	}
	
	return travel->m_data;
}

template <class T>
node<T> * list<T>::getHead()
{
	return m_head;
}

template <class T>
node<T> * list<T>::getTail()
{
	return m_tail;
}

template <class T>
list<T>::~list()
{
	Purge();
}

