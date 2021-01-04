#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
class Tree
{
	struct Node {				// ���������, ������� ��������� ���� inf � ��������� ����� � ������
		T inf;
		Node* left, * right;
	};
	Node* root;					// ������ ������
public:
	void initRoot() {			// ������������� ����� ��������� NULL
		root = NULL;
	}

	Tree<T>::Node* getRoot() {	// �������, ������� ���������� ������ ������
		return root;
	}

	Tree& operator += (const T& value) {			// ���������� ��������� +- (��������� ������� (����) � ������)
		Node* temp = new Node, * sp = NULL, * spt;	// ������� ��������� ���� Node
		bool b;
		temp->inf = value;							// ����������� ���� inf �������� value
		temp->left = NULL;							// ��������� ������ ����������� �������� NULL
		temp->right = NULL;							// ��������� ������� ����������� �������� NULL
		if (root == NULL)							// ���� � ��� root = NULL (������),
			root = temp;							// �� �� ������ ���������� ��������� temp
		else {										// �����
			spt = root;								// ��������� spt ����������� root
			while (spt != NULL)						// ���� spt (�� ������� �������) �� ����� ����� NULL
			{
				sp = spt;							// ��������� sp ����������� spt
				b = (value < spt->inf);				// ���������� �������� value �� ��������� ���� spt
				if (b) spt = spt->left;				// ���� b = true, ��������� � ����� ����
				else spt = spt->right;				// ����� � ������ ����
			}
			if (b) sp->left = temp;					// ���� b = true, ��������� ����� ����������� ��������� temp
			else sp->right = temp;					// ����� ��������� ������ ����������� ��������� temp
		}
		return *this;								// ���������� ��������� this
	}

	void dellist(T value)					// ������� �������� �� �������� �� ������
	{										// ������� �� ����, ��� ��������
		Node* spt = root, * sp = root, * w, * v = NULL;

		while ((spt != NULL) && (spt->inf != value))
		{
			sp = spt;
			if (value < spt->inf) spt = spt->left;
			else spt = spt->right;
		}

		if (spt == NULL) return;

		if ((spt->left == NULL) && (spt->right == NULL))
		{
			if (spt == sp)
			{
				delete(spt);
				root = NULL;
				return;
			}
			if (sp->left == spt)	sp->left = NULL;
			else	sp->right = NULL;
			delete(spt);
			return;
		}

		if (spt->left == NULL)
		{
			if (spt == sp)
			{
				spt = spt->right;
				delete(sp);
				root = spt;
				return;
			}
			if (sp->left == spt)	sp->left = spt->right;
			else	sp->right = spt->right;
			delete(spt);
			return;
		}

		if (spt->right == NULL)
		{
			if (spt == sp)
			{
				spt = spt->left;
				delete(sp);
				root = spt;
				return;
			}
			if (sp->left == spt)
				sp->left = spt->left;
			else
				sp->right = spt->left;
			delete(spt);
			return;
		}

		w = spt->left;
		if (w->right == NULL)	w->right = spt->right;
		else
		{
			while (w->right != NULL)
			{
				v = w;
				w = w->right;
			}
			v->right = w->left;
			w->left = spt->left;
			w->right = spt->right;

		}

		if (spt == sp)
		{
			delete(spt);
			root = w;
			return;
		}
		if (sp->left == spt)	sp->left = w;
		else	sp->right = w;
		delete(spt);
		return;
	}

	void readTreeSimmertricallyLeft(Tree<T>::Node* spt)				// ����������� ����� ������ ������ �����������
	{
		if (spt == NULL) return;									// ���� ��������� �� ������� ������� ����� NULL, ������� �� �������
		readTreeSimmertricallyLeft(spt->left);						// ��������� � ����� ����
		cout << setw(15) << "|Key:" << setw(5) << spt->inf << " |" << endl;		// ����� ����������
		readTreeSimmertricallyLeft(spt->right);						// ��������� � ������ ����
	}

	void readTreeReverseOrder(Tree<T>::Node* spt)					// ����������� ����� ������ ������ � �������� �������
	{
		if (spt == NULL) return;									// ���� ��������� �� ������� ������� ����� NULL, ������� �� �������
		readTreeReverseOrder(spt->left);							// ��������� � ����� ����
		readTreeReverseOrder(spt->right);							// ��������� � ������ ����
		cout << setw(15) << "|Key:" << setw(5) << spt->inf << " |" << endl;		// ����� ����������
	}

	void static readTreeDirectOrder(Tree<T>::Node* spt)				// ����������� ����� ������ ������ � ������ �������
	{
		if (spt == NULL) return;									// ���� ��������� �� ������� ������� ����� NULL, ������� �� �������
		cout << setw(15) << "|Key:" << setw(5) << spt->inf << " |" << endl;		// ����� ����������
		readTreeDirectOrder(spt->left);								// ��������� � ����� ����
		readTreeDirectOrder(spt->right);							// ��������� � ������ ����
	}

	friend ostream& operator << (ostream& os, Tree<T> tree) {		// ���������� ��������� << (�������� ������� ������ ������)
		readTreeDirectOrder(tree.getRoot());
		return os;
	}

	void sum(Tree<T>::Node* spt, T& sum_)				// ������� �������� ���� ����� � ������
	{
		if (spt != NULL) {								// ���� ��������� �� ������� ������� �� ����� NULL, ����� ��������� �� ������
			sum_ += spt->inf;
			sum(spt->left, sum_);						// ��������� � ����� ����
			sum(spt->right, sum_);						// ��������� � ������ ����
		}
	}

	void deleteTree(Tree<T>::Node* spt)					// ������� �������� ������
	{
		if (spt == NULL) return;						// ���� ��������� �� ������� ������� ����� NULL, ������� �� �������
		deleteTree(spt->left);							// ��������� � ����� ����
		deleteTree(spt->right);							// ��������� � ������ ����

		delete (spt);									// ������� ��������� �� ������� ����
		spt = NULL;										// ����������� ��� �������� NULL
		return;
	}

	double average(int count) {							// �������, ������� ���������� ������� ��������������
		T sum_ = 0;
		sum(root, sum_);								// ����� �������� ����� �������� ���� ����� ������
		return (double)sum_ / count;					// ������� ������� ��������������
	}
};

int main()
{
	Tree<double> tree;											// ������� ��������� ������ Tree � ����� int
	tree.initRoot();										// ����� ������ ������������� �����
	double n = 0, inf;
	cout << "enter number of elements: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter number" << endl;
		cin >> inf;
		tree += inf;										// ���������� �������� � ������
	}
	cout << tree;
	cout << "Avarage:" << tree.average(n) << endl;			// ������� �������� ���������������

	cout << "Enter value which you want delete" << endl;
	cin >> inf;
	tree.dellist(inf);										// �������� �������� �� ������
	cout << tree;
	tree.deleteTree(tree.getRoot());						// �������� ����� ������
}