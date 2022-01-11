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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List<T>;
	}*Head, * Tail;	//Сразу же после описания класса Element объявляем два указателя на Element
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BseItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstBaseIterator()
		{
#ifdef DEBUG
			cout << "BseItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:

	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		//										Operator
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ReItConstructors:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "ReItDestructor:\t" << this << endl;
#endif // DEBUG

		}

		//										Operators:
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator& operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator& operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};


	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}


	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()const
	{
		return Tail;
	}
	ConstReverseIterator crend()const
	{
		return nullptr;
	}

	//										Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}
	List(const initializer_list<T>& il) :List()
	{
		//for (T const* it = il.begin(); it != il.end(); it++)push_back(*it);
		//for(T const* it = il.end()-1;it!=il.begin()-1;it--)push_front(*it); //Добавление с конца
		for (T i : il)push_back(i);
	}
	List(const List<T>& other) :List()
	{
		*this = other;
#ifdef DEBUG
		cout << "CopyConstructor:" << this << endl;
#endif // DEBUG

	}
	List(List<T>&& other)
	{
		*this = std::move(other);
#ifdef DEBUG
		cout << "MoveConstructor:" << this << endl;
#endif // DEBUG

	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//										Operators:

	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Deep copy (Глубокое копирование) - Побитовое копирование
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
#ifdef DEBUG
		cout << "CopyAssigment:\t" << this << endl;
#endif // DEBUG

		return *this;
	}
	List<T>& operator=(List<T>&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy - Поверхностное копирование:
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size;
#ifdef DEBUG
		cout << "MoveAssigment:" << this << endl;
#endif // DEBUG
		return *this;
	}

	//										Adding elements:
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)//Добавление элемента в пустой список
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Общий случай
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);//Добавление элемента в пустой список
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;
	}

	void insert(T Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);

		Element* Temp;		//Создаем итератор, но мы пока не знаем, с какой стороны списка, лучше зайти с начала или с конца
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
		//Неважно с какой стороны мы добрались до нужной позиции, вставка элемента будет осуществляться по одному и тому же алгоритму
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//										Removing Elements:

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
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
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		if (Index == size - 1)return pop_back();
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
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	//										Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

template<typename T>
void print_list(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>
void reverse_print_list(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
}

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	int Value;
	int Index;
	cout << "Введите индекс добовляемого элемента: "; cin >> Index;
	cout << "Введите значение добовляемого элемента: "; cin >> Value;
	list.insert(Value, Index);
	list.print();
	list.reverse_print();
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	list.erase(Index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List<int> list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse_print();
	List<int> list2 = list;
	/*list2.print();
	list.reverse_print();*/
	for (int i : list2)cout << i << tab; cout << endl;

	for (List<int>::ReverseIterator rit = list2.rbegin(); rit != list2.rend(); rit++)cout << *rit << tab; cout << endl;

	print_list(list);
	reverse_print_list(list);

	List<double> d_list = { 2.5,3.14,5.2,8.3 };
	for(double i:d_list)cout << i << tab; cout << endl;

	List<string> s_list = { "Happy ","New ","Year " };
	for (string i : s_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it != d_list.rend(); it++)
		cout << *it << tab;
	cout << endl;
	for (List<string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); it++)
		cout << *it << tab;
	cout << endl;

	cout << "\n----------------------------------------------------------------\n" << endl;
	List<List<int>> list2d =
	{
		{3,5,8,13,21},
		{34,55,89},
		{144,233,377,610}
	};
	for (List<List<int>>::Iterator i = list2d.begin(); i != list2d.end(); i++)
	{
		for (List<int>::Iterator j = (*i).begin();j!=(*i).end();j++)
			cout << *j << tab;
		cout << endl;
	}
	cout << "\n----------------------------------------------------------------\n" << endl;
	for (List<int> i : list2d)
	{
		for (int j : i)
			cout << j << tab;
		cout << endl;
	}
	cout << "\n----------------------------------------------------------------\n" << endl;

}