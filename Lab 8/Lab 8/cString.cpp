#include "cString.h"


/*
	Purpose: This is the default constructor for the cString class.
	m_string is initialized to nullptr with length being 0.
*/
cString::cString() : m_string(nullptr), m_length(0)
{
}

/*
	Purpose: This is the copy constructor for the cString class that takes a const char* string.
	m_string is initialized to a new char array with length being strlen + 1 of the const char* string.

*/
cString::cString(const char * string) : m_string(nullptr), m_length(0)
{
	if (string != nullptr)
	{
		m_string = new char[strlen(string) + 1];
		strcpy(m_string, string);
		m_length = (strlen(string) + 1);
	}
}

/*
	Purpose: This is the copy constructor for the cString class.
	It takes a const cString object&. m_string is initialized to the same member of the string object passed.
	m_length is initialized to string's m_length.
*/
cString::cString(const cString & string) : m_string(nullptr), m_length(0)
{
	if (string.m_string != nullptr)
	{
		m_string = new char[strlen(string.m_string) + 1];
		strcpy(m_string, string.m_string);
		m_length = string.m_length;
	}
}

cString::cString(cString && string) : m_string(string.m_string), m_length(string.m_length)
{
	string.m_string = nullptr;
}

/*
	Purpose: This function overloads the = operator for the cString class.
	by initializing one string to another. That takes a cString object on the right side.
*/
cString & cString::operator=(const cString & string)
{
	if (this != &string)
	{
		if (m_string != nullptr)
		{
			delete[] m_string;
			m_string = new char[strlen(string.m_string) + 1];
			strcpy(m_string, string.m_string);
			m_length = string.m_length;
		}
		else
		{
			m_string = new char[strlen(string.m_string) + 1];
			strcpy(m_string, string.m_string);
			m_length = string.m_length;
		}
	}
	return *this;
}

cString & cString::operator=(cString && rhs)
{
	if (this != &rhs)
	{
		delete[] m_string;
		m_string = rhs.m_string;
		rhs.m_string = nullptr;
	}

	return *this;
}

/*
	Purpose: This function overloads the = operator for the cString class.
	by initializing one string to another. That takes a const char* on the right side.
*/
cString & cString::operator=(const char * arr)
{
	if (arr != nullptr)
	{
		delete[] m_string;
		m_string = new char[strlen(arr) + 1];
		strcpy(m_string, arr);
		m_length = (strlen(arr) + 1);
	}
	else
	{
		delete[] m_string;
		m_string = nullptr;
		m_length = 0;
	}
	return *this;
}

/*
	Purpose: This function overloads the == operator for the cString class.
	And returns whether or not the too strings are the same string.
*/
bool cString::operator==(const cString& rhs) const
{
	bool test = false;
	if (strcmp(rhs.m_string, m_string) == 0)
	{
		test = true;
	}

	return test;
}

/*
	Purpose: This function overloads the < operator for the cString class.
	And returns whether or not the string on the left comes later alphabetically.
*/
bool cString::operator<(const cString & rhs) const
{
	bool test = false;
	if (strcmp(rhs.m_string, m_string) < 0)
	{
		test = true;
	}

	return test;
}

/*
	Purpose: This function overloads the > operator for the cString class.
	And returns whether or not the string on the left comes earlier alphabetically.
*/
bool cString::operator>(const cString & rhs) const
{
	bool test = false;
	if (strcmp(rhs.m_string, m_string) > 0)
	{
		test = true;
	}

	return test;
}

/*
	Purpose: This function overloads the <= operator for the cString class.
	And returns whether or not the string on the left comes later alphabetically or is the same as the string on the right.
*/
bool cString::operator<=(const cString & rhs) const
{
	bool test = false;
	if (strcmp(rhs.m_string, m_string) <= 0)
	{
		test = true;
	}

	return test;
}

/*
	Purpose: This function overloads the >= operator for the cString class.
	And returns whether or not the string on the left comes earlier alphabetically or is the same as the string on the right.
*/
bool cString::operator>=(const cString & rhs) const
{
	bool test = false;
	if (strcmp(rhs.m_string, m_string) >= 0)
	{
		test = true;
	}

	return test;
}

/*
	Purpose: This function overloads the != operator for the cString class.
	And returns whether or not the string on the left is the not same as the string on the right.
*/
bool cString::operator!=(const cString & rhs) const
{
	bool test = false;
	if (strcmp(rhs.m_string, m_string) != 0)
	{
		test = true;
	}

	return test;

}

/*
	Purpose: This function overloads the [] operator for the cString class.
	And returns the character within the string that is at the offset indicated by the integer passed to it.
*/
char cString::operator[](int index) const
{
	char temp = '/0';
	if (index < m_length && index > 0)
	{
		temp = m_string[index];
	}
	return temp;
}

/*
	Purpose: This function overloads the + operator for the cString class.
	This function returns a new cString object that is the characters of the string on the left
	to the characters of the string on the right.
*/
cString cString::operator+(cString & rhs)
{
	cString newString;
	newString.m_length = m_length + rhs.m_length;
	newString.m_string = new char[newString.m_length];

	strcpy(newString.m_string, m_string);
	strcat(newString.m_string, rhs.m_string);

	return newString;
}

/*
	Purpose: This function overloads the += operator for the cString class.
	This function modifies the string on the left by adding the characters of the string on left.
*/
cString & cString::operator+=(cString & rhs)
{
	cString newString;

	newString.m_string = new char[m_length];

	strcpy(newString.m_string, m_string);
	delete[] m_string;
	m_length += rhs.m_length;
	m_string = new char[m_length];

	strcpy(m_string, newString.m_string);
	strcat(m_string, rhs.m_string);

	return *this;
}

/*
	Purpose: This function overloads the pre++ operator in order to make the string uppercase.
*/
cString & cString::operator++()
{
	toupper(*m_string);
	return *this;

}

/*
	Purpose: This function overloads the post++ operator in order to make the string uppercase.
*/
const cString cString::operator++(int)
{
	cString temp(*this);
	++(*this);
	return temp;
}

/*
	Purpose: This function overloads the post-- operator in order to make the string lowercase.
*/
cString & cString::operator--()
{
	tolower(*m_string);
	return *this;
}

/*
	Purpose: This function overloads the pre-- operator in order to make the string lowercase.
*/
const cString cString::operator--(int)
{
	cString temp(*this);
	--(*this);
	return temp;
}

/*
	Purpose: This function displays the cString object.
*/
void cString::display() const
{
	cout << m_string;
}

/*
	Purpose: This function returns the number of characters plus 1.
*/
int cString::getLength()
{
	return m_length;
}

/*
	Purpose: This function returns a const char* to the character array inside the cString object.
*/
const char * cString::getString()
{
	return m_string;
}

/*
	Purpose: This function overloads the insertion operator so that you can use cout with the cString object.
*/
ostream & operator<<(ostream & out, const cString & s)
{
	return out << s.m_string;
}

/*
	Purpose: This is destructor for the cString class.
*/
cString::~cString()
{
	delete[] m_string;
	m_string = nullptr;
	m_length = 0;
}
