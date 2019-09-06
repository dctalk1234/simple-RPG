#define _CRT_SECURE_NO_WARNINGS 
#pragma once
#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;

class cString
{
public:
	cString();
	cString(const char* string);
	cString(const cString& string);
	cString(cString&& string);
	cString& operator=(const cString& rhs);
	cString& operator=(cString&& rhs);
	cString& operator=(const char * arr);
	bool operator==(const cString& rhs) const;
	bool operator<(const cString& rhs) const;
	bool operator>(const cString& rhs) const;
	bool operator<=(const cString& rhs) const;
	bool operator>=(const cString& rhs) const;
	bool operator!=(const cString& rhs) const;
	char operator[](int index) const;
	cString operator+(cString& rhs);
	cString& operator+=(cString& rhs);
	cString& operator++();
	const cString operator++(int);
	cString& operator--();
	const cString operator--(int);
	void display() const;
	int getLength();
	const char* getString();
	friend ostream& operator << (ostream& out, const cString& s);
	~cString();
private:
	char* m_string;
	int m_length;
};