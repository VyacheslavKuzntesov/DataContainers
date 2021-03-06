#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class ForwardList;
class Element
{
	int Data;			//Значение элемента
	Element* pNext;		//Адрес следующего элемента
	static int count;	//Статическая переменная которая будет считать количество элементов.
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
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

	friend class ForwardList;
	friend class Iterator;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0;	//Инициализация статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)	//Suffix increment
	{
		Iterator old = *this;
		Temp = Temp->pNext;
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

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Element* get_Head()const
	{
		return Head;
	}

	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il):ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		//int const* - указатель на константу
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "MoveConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
		/*Element* Temp = Head;
		Element* Delete = Temp->pNext;
		for (;;)
		{
			delete Temp;
			Temp = Delete;
			Delete = Delete->pNext;
			if (Delete->pNext == nullptr)
			{
				delete Temp;
				delete Delete;
				break;
			}
		}*/
	}

	//										Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		cout << "CopyAssigment:\t" << this << endl;
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		cout << "MoveAssigment:\t" << this << endl;
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
	}

	//										Adding Elements:
	void push_front(int Data)
	{
		/*
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) "Привязываем" элемент к началу списка:
		New->pNext = Head;
		//3) Делаем новый элемент началом списка:
		Head = New;
		size++;
		*/

		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		/*if (Head == nullptr)return push_front(Data);
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
		size++;*/

		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Выход за пределы списка:" << endl;
			return;
		}
		//Общий случай:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);

		size++;
	}

	//										Removing Elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Erased->pNext;
		delete Erased;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		if (Index > size)
		{
			cout << "Error: Выход за пределы списка:" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* Delete = Temp->pNext;
		Temp->pNext = Delete->pNext;
		delete Delete;
		size--;
	}

	//										Methods
	void print()const
	{
		/*Element* Temp = Head;	//Temp - это Итератор
		//Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переходим на следующий элемент.
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}

	void unique()
	{
		if (Head == nullptr)return;
		int Index;
		int Count = 1;
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Index = 0;
			Index = Count;
			Element* Repeat = Temp;
			while (Repeat->pNext)
			{
				Repeat = Repeat->pNext;
				if(Temp->Data == Repeat->Data)
				{
					if (Repeat->pNext == nullptr)
					{
						this->pop_back();
						break;
					}
					else
					{
						this->erase(Index);
						Index--;
						Repeat = Temp;
						Index = Count;
					}
				}
				Index++;
				if (Repeat->pNext == nullptr)break;
			}
			if (Temp->pNext == nullptr)return;
			Temp = Temp->pNext;
			Count++;
			if (Temp->pNext == nullptr)return;
		}
	}

	void reverse()
	{
		if (Head == nullptr)return;
		Element* Temp = Head;
		Element* Next = nullptr;
		Element* Prev = nullptr;
		while (Temp)
		{
			Next = Temp->pNext;
			Temp->pNext = Prev;
			Prev = Temp;
			Temp = Next;
		}
		Head = Prev;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;	//CopyConstructor
	/*for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
	{
		cat.push_back(Temp->Data);
	}*/
	for (Iterator Temp = right.get_Head(); Temp; ++Temp)
	{
		cat.push_back(*Temp);
	}
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PREFORMANCE_CHEC
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
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
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // COUNT_CHECK

#ifdef PREFORMANCE_CHEC
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "List filled " << endl;
#endif // PREFORMANCE_CHEC

#ifdef OPERATOR_PLUS_CHECK
	//int arr[] = { 3,5,8,13,21 };
	ForwardList list1 = { 3,5,8,13,21 };
	list1 = list1;
	list1.print();
	ForwardList list2 = { 34,55,89 };
	list2.print();
	cout << "\n------------------------------\n";
	ForwardList list3 = list1 + list2;
	cout << "\n------------------------------\n";
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)//range-based for
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

	ForwardList list = { 3,3,5,4,5,4 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	list.unique();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	list.reverse();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
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

	СТАТИЧЕСКИЕ ПЕРЕМЕННЫЕ В КЛАССЕ
	Статическая переменная не принадлежит какому-то объекту поскольку она хранится в классе.
	Статическая переменная является общей для всех объектов класса. Каждый объект имеет равноправный доступ к статической переменной.
	При помощи статических переменных очень удобно считать количество объектов класса.
	Статические переменные могут быть проинициализированы только за пределами класса.

	Initializer list - это контейнер такой же как и наш Forwardlist
	Контейнер - это объект который организует хранение других объектов в памяти
	У любого контейнера есть методы:
	begin() - возвращает итератор на начало контейнера
	end() - возвращает итератор на конец контейнера
	Итератор - это указатель при помощи которого можно проходить по структуре данных

	ШАБЛОНЫ КЛАССОВ
	Шаблонным называется класс тип полей которого определяется при создании объектов.
	Для того что бы сделать класс шаблонным перед ним достаточно создать шаблон.
	Теперь любая переменная класса может быть шаблоным а все методы класса автоматически становятся шаблонными
	При обращении к шаблонаму классу обязательно нужно указовать конкретный тип данных
	например:
	class - обычный класс
	class<T> - шаблонный класс

	ДВУСВЯЗНЫЙ СПИСОК
	Двусвязным называется список каждый элемент которого содержит не только адрес следующего но и предедущего элемента это позволяет проходить список в обоих направлениях
	У двухсвязного списка есть не только голова но ищё и хвост позволяющий зайти в список с конца
	Когда список пуст его голова и хвост указывают на ноль
	Когда в списке появляется первый элемент он одновременно являеться и головой и хвостом списка а также первым и последним элементом списка с какой стороны не посмотреть
*/