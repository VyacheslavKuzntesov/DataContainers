#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		this->pPrev = pPrev;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}

	friend class Iterator;
	friend class ReverseIterator;
	friend class List;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	Iterator& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	Iterator& operator--()
	{
		Temp = Temp->pPrev;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator old = *this;
		Temp = Temp->pPrev;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}

	operator bool()const
	{
		return Temp;
	}
};

class ReverseIterator
{
	Element* Temp;
public:
	ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ReItConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~ReverseIterator()
	{
#ifdef DEBUG
		cout << "ReItDestructor:\t" << this << endl;
#endif // DEBUG

	}

	ReverseIterator& operator++()
	{
		Temp = Temp->pPrev;
		return *this;
	}
	ReverseIterator operator++(int)
	{
		ReverseIterator old = *this;
		Temp = Temp->pPrev;
		return old;
	}
	ReverseIterator& operator--()
	{
		Temp = Temp->pNext;
		return *this;
	}
	ReverseIterator operator--(int)
	{
		ReverseIterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const ReverseIterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ReverseIterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	Element* get_Head()const
	{
		return Head;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rebegin()
	{
		return Tail;
	}
	ReverseIterator reend()
	{
		return nullptr;
	}

	List& operator=(const List& other)
	{
		cout << "CopyAssigment:\t" << this << endl;
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		return *this;
	}

	//										Adding elements:

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(unsigned int Index, int Data)
	{
		if (Index > size)return;
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index == size)
		{
			push_back(Data);
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//										Erasing elements:
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size - 1)
		{
			pop_back();
			return;
		}
		if (index >= size)return;

		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
	}
	//										Methods:
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void print_reverse()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (Iterator Temp = right.get_Head(); Temp; ++Temp)
	{
		cat.push_back(*Temp);
	}
	return cat;
}

void main()
{
	setlocale(LC_ALL, "Russian");

	/*int n;	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++) list.push_back(rand() % 100);
	list.print();
	list.print_reverse();

	int index;
	int value;
	cout << "Введите значение добавляемого элемента в начало: "; cin >> value;
	list.push_front(value);
	cout << "Введите значение добавляемого элемента в конец: "; cin >> value;
	list.push_back(value);
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.print_reverse();

	list.pop_front();
	list.pop_back();
	list.print();
	list.print_reverse();
	cout << "Введите индекс удавляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.print_reverse();*/

	List list1 = { 34, 55, 89, 144, 233 };
	List list = { 3, 5, 8, 13, 21 };
	list1.print();
	for (int i : list1)
		cout << i << tab;
	cout << endl;
	for (Iterator it = list1.begin(); it != list1.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << "\n-----------------------------------------------\n";
	for (ReverseIterator it = list1.rebegin(); it != list1.reend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	list.print();
	list1.print();
	List list3 = list + list1;
	list3.print();
}