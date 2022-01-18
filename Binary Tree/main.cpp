#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
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
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it, Root);
	}
	~Tree()
	{
#ifdef DEBUG
		cout << "TDestructor:\t" << this << endl;
#endif // DEBUG

		this->clear();
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}

	void print()const
	{
		print(this->Root);
		cout << endl;
	}

	int minValue()const
	{
		return minValue(Root);
	}

	int maxValue()const
	{
		return maxValue(Root);
	}

	int count()const
	{
		return count(Root);
	}

	int sum()const
	{
		return sum(Root);
	}

	double avg()const
	{
		return (double)sum() / count();
	}

	int depth()const
	{
		return depth(Root);
	}

	void clear()
	{
		clear(Root);
		/*this->Root = nullptr;*/
	}

private:

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else /*if(Data>Root->Data)*/
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		/*insert(Data, Root);*/
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}

	int maxValue(Element* Root)const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}

	int sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + Root->Data;*/
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}

	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return 
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1? 
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		/*insert(Data, Root);*/
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.print(tree.getRoot());
	tree.print();
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	cout << "���������� ��������� ������: " << tree.count() << endl;
	cout << "����� ��������� ������: " << tree.sum() << endl;
	cout << "������� �������������� ��������� ������" << tree.avg() << endl;
	cout << "������� ������: " << tree.depth() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "����������� �������� � ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� � ������: " << u_tree.maxValue() << endl;
	cout << "���������� ��������� ������: " << u_tree.count() << endl;
	cout << "����� ��������� ������: " << u_tree.sum() << endl;
	cout << "������� �������������� ��������� ������" << u_tree.avg() << endl;
	cout << "������� ������: " << u_tree.depth() << endl;
#endif // BASE_CHECK

	Tree tree = { 50,25,75,16,32,48,64,80,85,77 };
	tree.print();
	cout << "������� ������: " << tree.depth() << endl;
}






/*
	���������� ��� ���������� ������
	��� ������������ ���������� ������ ���� ������ ������� ������ �� ������ ����� �������� �� � ����� ���������
	��� ����������� ���������� � ���� ��� ������������� �� ������� ����� ������������� ���� ������������� ����������� � ����� ��� ����������� ������ �������

	������� ������ ��� ���������� ������� �������� � �������� ������ � ��������� ��������������� ������ ���������� ����� �� ������ ���� ������ ����������� � ��� ���� ������������� � ��������� ��������������� ������ ���������� ����� �� ������ ������������ �� ������� N = 2^n; ��� N ��� ���������� ����� �� �������� ������ � n ��� ������� ������ 
	������� ������ ��������� � ����, �������� ������� ������ ��������� �� 0 ������� ������������� ���������� ��������� � ����� ������ ��������� 2 � 0 ������� 
*/