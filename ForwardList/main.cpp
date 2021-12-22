#include<iostream>
using namespace std;
#define tab "\t"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//										Adding Elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) "Привязываем" элемент к началу списка:
		New->pNext = Head;
		//3) Делаем новый элемент началом списка:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем первый элемент
		Element* New = new Element(Data);
		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//3) Добавляем созданный элемент в конце списка:
		Temp->pNext = New;
	}

	void insert(int Data, int Index)
	{
		Element* Temp = Head;
		Element* New = new Element(Data);
		for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//										Removing Elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Erased->pNext;
		delete Erased;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void erase(int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* Delete = Temp->pNext;
		Temp->pNext = Delete->pNext;
		delete Delete;
	}

	//										Methods
	void print()const
	{
		Element* Temp = Head;	//Temp - это Итератор
		//Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переходим на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	int value;
	int index;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	cout << endl;
	list.pop_front();
	list.print();
	cout << endl;
	list.pop_back();
	list.print();
	cout << endl;
	cout << "Введите индекс добовляемого элемента: "; cin >> index;
	cout << "Введите значение добовляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}


/*
	ДИНАМИЧЕСКИЕ СТРУКТУРЫ ДАННЫХ
	Простейшая динамическая структура данных с которой мы работали это массив
	Массив это набор элементов одного типа в непрерывной области памяти. Непрерывная область памяти одновременно является приимуществом и недостатком массива.
	Главным приимуществом массива являеться быстрый доступом к объектам который осуществляеться за константное значение потому что выполняеться сложение.
	Главным недостатком массива являеться сложность добавление удаление элементов которое требует дополнительних затрат памяти и времени что приводит к снижению производительности
	Затраченная память и время при добавлении элемента в массив зависят от размера массива чем больше массив тем больше памяти и времени затрачивается на удаление добавление элемента массива
	
	Недостатки масива устраняют списки Список это набор элементов в произвольной области каждый из которых содержит адрес следующего элемента у любого списка есть голова которая указывает на начальный элемент списка и является точкой входа в список последний элемент списка всегда указывает на ноль.
	Хранение элементов в произвольних областях памяти является одновременно приимуществом и недостатком списка
	Главным приимуществом списка является быстрое добавление и удаление элементов которое осуществляется за константное время и не зависит от размеров списка
	Главным недостатком списка является медленный доступ к элементам который зависит от размера списка по скольку что бы получить доступ к одному элементу нужно пройти через все элементы от начала списка до нужного элемента если массив дает произвольный доступ к элементам то список обеспечивает лишь последовательный доступ к элементам

	Реализация односвязного списка
	Односвязный список реализуется при помощи двух классов:
	1. Класс элемент описувающий структуру элемента каждый элемент списка содержит поле данных(в котором содержится значение элемента) и поля pNext(которое содержит адрес следующего элемента)
	2. Класс ForwardList - односвязный(однонаправленный) список отвечает за объэдинение элементов в список добавление элементов, удаление элементов, и т.д
	У списка есть только голова которая указывает на начальный элемент списка последний элемент списка всегда указывает на ноль


*/