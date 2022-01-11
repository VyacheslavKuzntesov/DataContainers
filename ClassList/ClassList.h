#pragma once
#include<iostream>
#include<string.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;	//����� �� ����� �������� ������ Element ��������� ��� ��������� �� Element
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		const int& operator*()const;
	};
public:

	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();

		//										Operator
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		//										Operators:
		ConstReverseIterator& operator++();
		ConstReverseIterator& operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator& operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		T& operator*();
	};


	Iterator begin();
	Iterator end();
	ConstIterator cbegin()const;
	ConstIterator cend()const;


	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	//										Constructors:
	List();
	List(const initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other);
	~List();

	//										Operators:

	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);

	//										Adding elements:
	void push_front(T Data);
	void push_back(T Data);

	void insert(T Data, int Index);

	//										Removing Elements:

	void pop_front();
	void pop_back();
	void erase(int Index);

	//										Methods:
	void print()const;
	void reverse_print()const;
};

template<typename T>
void print_list(const List<T>& list);

template<typename T>
void reverse_print_list(const List<T>& list);