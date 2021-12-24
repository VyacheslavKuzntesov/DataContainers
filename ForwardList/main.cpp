#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

template<typename T>class ForwardList;		//Объявляем ForwardList как шаблонный класс
template<typename T>class Iterator;
template<typename T>class Element
{
	T Data;			//Значение элемента
	Element<T>* pNext;		//Адрес следующего элемента
	static int count;	//Статическая переменная которая будет считать количество элементов.
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
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

	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

template<typename T>int Element<T>::count = 0;	//Инициализация статической переменной

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int)	//Suffix increment
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}

	operator bool()const
	{
		return Temp;
	}
};

template<typename T>class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:
	Element<T>* get_Head()const
	{
		return Head;
	}

	Iterator<T> begin()const
	{
		return Head;
	}
	Iterator<T> end()const
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<T>& il):ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		//int const* - указатель на константу
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		//for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList<T>&& other) :ForwardList<T>()
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
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		cout << "CopyAssigment:\t" << this << endl;
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		return *this;
	}
	ForwardList<T>& operator=(ForwardList<T>&& other)
	{
		cout << "MoveAssigment:\t" << this << endl;
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
	}

	//										Adding Elements:
	void push_front(T Data)
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

		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
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
		Element<T>* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	void insert(T Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Выход за пределы списка:" << endl;
			return;
		}
		//Общий случай:
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element<T>(Data, Temp->pNext);

		size++;
	}

	//										Removing Elements:
	void pop_front()
	{
		Element<T>* Erased = Head;
		Head = Erased->pNext;
		delete Erased;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element<T>* Temp = Head;
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
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element<T>* Delete = Temp->pNext;
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
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element<T>::count << endl;
	}
};

template<typename T>ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;	//CopyConstructor
	/*for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
	{
		cat.push_back(Temp->Data);
	}*/
	for (Iterator<T> Temp = right.get_Head(); Temp; ++Temp)
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

	ForwardList<int> list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Happy"," New ","Year" };
	for(std::string i : s_list)cout << i << tab; cout << endl;
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
*/