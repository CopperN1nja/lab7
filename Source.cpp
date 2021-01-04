#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
class Tree
{
	struct Node {				// структура, которая содержить поле inf и указатели влево и вправо
		T inf;
		Node* left, * right;
	};
	Node* root;					// корень дерева
public:
	void initRoot() {			// инициализация корня значением NULL
		root = NULL;
	}

	Tree<T>::Node* getRoot() {	// функция, которая возвращает корень дерева
		return root;
	}

	Tree& operator += (const T& value) {			// перегрузка оператора +- (добавляет элемент (узел) в дерево)
		Node* temp = new Node, * sp = NULL, * spt;	// создает указатели типа Node
		bool b;
		temp->inf = value;							// призваеваем полю inf значение value
		temp->left = NULL;							// указателю налево присваиваем значение NULL
		temp->right = NULL;							// указателю направо присваиваем значение NULL
		if (root == NULL)							// если у нас root = NULL (пустой),
			root = temp;							// то мы просто возвращаем указатель temp
		else {										// иначе
			spt = root;								// указателю spt присваиваем root
			while (spt != NULL)						// пока spt (на текущий элемент) не будет равен NULL
			{
				sp = spt;							// указателю sp присваиваем spt
				b = (value < spt->inf);				// сравнивает значение value со значением узла spt
				if (b) spt = spt->left;				// если b = true, переходим в левый узел
				else spt = spt->right;				// иначе в правый узел
			}
			if (b) sp->left = temp;					// если b = true, указателю слева присваиваем указатель temp
			else sp->right = temp;					// иначе указателю справа присваиваем указатель temp
		}
		return *this;								// возвращаем указатель this
	}

	void dellist(T value)					// функция удаления из элемента из дерева
	{										// понятия не имею, как работает
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

	void readTreeSimmertricallyLeft(Tree<T>::Node* spt)				// рекурсивный метод вывода дерева симметрично
	{
		if (spt == NULL) return;									// если указатель на текущий элемент равен NULL, выходим из функции
		readTreeSimmertricallyLeft(spt->left);						// переходим в левый узел
		cout << setw(15) << "|Key:" << setw(5) << spt->inf << " |" << endl;		// вывод информации
		readTreeSimmertricallyLeft(spt->right);						// переходим в правый узел
	}

	void readTreeReverseOrder(Tree<T>::Node* spt)					// рекурсивный метод вывода дерева в обратном порядке
	{
		if (spt == NULL) return;									// если указатель на текущий элемент равен NULL, выходим из функции
		readTreeReverseOrder(spt->left);							// переходим в левый узел
		readTreeReverseOrder(spt->right);							// переходим в правый узел
		cout << setw(15) << "|Key:" << setw(5) << spt->inf << " |" << endl;		// вывод информации
	}

	void static readTreeDirectOrder(Tree<T>::Node* spt)				// рекурсивный метод вывода дерева в прямом порядке
	{
		if (spt == NULL) return;									// если указатель на текущий элемент равен NULL, выходим из функции
		cout << setw(15) << "|Key:" << setw(5) << spt->inf << " |" << endl;		// вывод информации
		readTreeDirectOrder(spt->left);								// переходим в левый узел
		readTreeDirectOrder(spt->right);							// переходим в правый узел
	}

	friend ostream& operator << (ostream& os, Tree<T> tree) {		// перегрузка оператора << (вызывает функцию вывода дерева)
		readTreeDirectOrder(tree.getRoot());
		return os;
	}

	void sum(Tree<T>::Node* spt, T& sum_)				// функция подсчета всех чисел в дереве
	{
		if (spt != NULL) {								// пока указатель на текущий элемент не равен NULL, будем проходить по дереву
			sum_ += spt->inf;
			sum(spt->left, sum_);						// переходим в левый узел
			sum(spt->right, sum_);						// переходим в правый узел
		}
	}

	void deleteTree(Tree<T>::Node* spt)					// функция удаления дерева
	{
		if (spt == NULL) return;						// если указатель на текущий элемент равен NULL, выходим из функции
		deleteTree(spt->left);							// переходим в левый узел
		deleteTree(spt->right);							// переходим в правый узел

		delete (spt);									// удаляем указатель на текущий узел
		spt = NULL;										// присваиваем ему значение NULL
		return;
	}

	double average(int count) {							// функция, которая возвращает среднее арифметическое
		T sum_ = 0;
		sum(root, sum_);								// вызов подсчета суммы значений всех узлов дерева
		return (double)sum_ / count;					// считаем среднее арифметическое
	}
};

int main()
{
	Tree<double> tree;											// создаем экземпляр класса Tree с типом int
	tree.initRoot();										// вызов метода инициализации корня
	double n = 0, inf;
	cout << "enter number of elements: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter number" << endl;
		cin >> inf;
		tree += inf;										// добавление элемента в дерево
	}
	cout << tree;
	cout << "Avarage:" << tree.average(n) << endl;			// подсчет среднего арифметического

	cout << "Enter value which you want delete" << endl;
	cin >> inf;
	tree.dellist(inf);										// удаление элемента из дерева
	cout << tree;
	tree.deleteTree(tree.getRoot());						// удаление всего дерева
}