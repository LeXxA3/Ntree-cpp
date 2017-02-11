
#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
	int nodeValue;			//значение узла
	int numberOfSon;        //номер узла
	int levelOfSon;         //уровень узла
	Node** childs;			//массив указателей на сыновей
	int countChildsOfNode;  //количество сыновей узла
};

int tempValue;					//переменная для временного хранения значения узла

void createNode(Node *node, int index, int levelOfSon)
{
	for (int i = 0; i < node->countChildsOfNode; i++)				//для всех сыновей
	{
	node->childs[i] = new Node;						//выделяем память
	node->childs[i]->numberOfSon = index + i;		//увеличиваем номер
	node->childs[i]->levelOfSon = levelOfSon;
	}
}


Node *createTree(Node *node, int index, int levelOfSon)	//функция создания дерева
{
	node->numberOfSon = index;					//передаём номер узла
	node->levelOfSon = levelOfSon;				//передаём уровень узла
	cout << "\nВведите значение узла (" << (node->levelOfSon) << "-" << (node->numberOfSon) << "): ";
	cin >> tempValue;									//вводим значение узла
	node->nodeValue = tempValue;							//привязываем это значение к узлу
	cout << "Сколько сыновей у (" << (node->levelOfSon) << "-" << (node->numberOfSon) << "): ";
	cin >> node->countChildsOfNode;								//вводим количество сыновей
		node->childs = new Node *[node->countChildsOfNode];		//Выделяем память под них
		levelOfSon++;							//увеличиваем уровень узла
		createNode(node, index, levelOfSon);
		for (int i = 0; i < node->countChildsOfNode; i++)	
			createTree(node->childs[i], index + i, levelOfSon); //рекурсивно проделываем все операции для каждого нового сына
	return node;									//возвращаем дерево
}

void printTree(Node *node)						 //функция печати дерева
{
	if (node)									 //если дерево не пустое
	{
		for (int i = 0; i < (node->levelOfSon); i++) 
			cout << "  ";					 //выводим отступ, обозначающий уровень
		if (node->childs != NULL)				 //если массив сыновей не пуст
		cout << node->nodeValue << endl;			 //то выводим информацию узла
		if ((node->countChildsOfNode) != 0)					 //если есть сыновья
			for (int i = 0; i < (node->countChildsOfNode); i++) 
				printTree(node->childs[i]);		 //то рекурсивно выводим каждого
	}
}

void deleteTree(Node *node)					//функция удаления дерева
{
		if ((node->countChildsOfNode) != 0)					//если есть сыновья
			for (int i = 0; i < (node->countChildsOfNode); i++)
				deleteTree(node->childs[i]);		//рекурсивно удаляем каждого их них
	delete[] node->childs;						//операция удаления
}

Node *needHeight(Node *t, int cHeight, int h)	//функция поиска дерева нужной высоты
{
	if (h == cHeight)							//если высота поддерева совпадает с нужной
		return t;								//возвращаем корень этого поддерева
	for (int i = 0; i < t->countChildsOfNode; i++)		
	{
		needHeight(t->childs[i], cHeight, h++);//рекурсивно проделываем это для каждого сына
	}										 //увеличивая высоту			
}

void Width(Node *t, Node **min, Node **max)	 //функция определения самого широкого(узкого) поддерева
{

	if (*min == NULL)						//если минимальное дерево пусто
		*min = t;							//то присваеваем ему текущее дерево
	else if (t->countChildsOfNode < (*min)->countChildsOfNode)				//иначе если ширина текущего дерева меньше минимальной
		*min = t;							//то делаем текущее дерево узким

	if (*max == NULL)						//если максимальное дерево пусто
		*max = t;							//то присваеваем ему текущее дерево
	else if (t->countChildsOfNode >(*max)->countChildsOfNode)				//иначе если ширина текущего дерева больше максимальной
		*max = t;							//то делаем текущее дерево широким

	for (int i = 0; i < t->countChildsOfNode; i++)
	{
		Width(t->childs[i], min, max);		//рекурсивно выполняем данные операции для каждого поддерева
	}
}


int main()
{
	setlocale(LC_ALL, "RUS");				//поддержка русских символов
	cout << "Первое число - номер уровня, второе число - номер элемента в уровне\n";
	Node *t;								//создаем дерево
	t = new Node;							//и выделяем под него память
	t = createTree(t, 0, 0);				//заполняем дерево
	printTree(t);							//выводим дерево на экран
	cout << "Введите нужную высоту: " << endl;
	int cHeight;							
	cin >> cHeight;							//вводим высоту поддерева
	Node *t1;								//создаем ещё одно дерево
	t1 = new Node;							//и выделяем под него память
	t1 = needHeight(t, cHeight, 0);			//Находим поддеревья нужной высоты
	Node *min = NULL, *max = NULL;			//создаем объекты широкого и узкого поддеревьев
	Width(t1, &min, &max);					//определяем их
	if (min != NULL)						//если самое узкое дерево нашлось
	{
		cout << "Самое узкое дерево заданной высоты" << endl;
		printTree(min);						//то выводим его на экран
	}
	if (max != NULL)						//если самое широкое дерево нашлось
	{
		cout << "Самое широкое дерево заданной высоты" << endl;
		printTree(max);						//то выводим его на экран
	}
	deleteTree(t);							//удаляем деревья
	deleteTree(t1);	
	deleteTree(min);
	deleteTree(max);
	return 0;								//выход из программы						
}
