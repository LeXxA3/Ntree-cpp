#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
	int nodeValue;		
	int numberOfSon;       
	int levelOfSon;        
	Node** childsOfNodeArray;			
	int countChildsOfNode;  
};		

void readValueOfNodeFromKeyboard(Node *node)
{
	cout << "\nВведите значение узла (" << (node->levelOfSon) << "-" << (node->numberOfSon) << "): ";
	cin >> node->nodeValue;
}

void readChildsOfNodeFromKeyboard(Node *node)
{
	cout << "Сколько сыновей у (" << (node->levelOfSon) << "-" << (node->numberOfSon) << "): ";
	cin >> node->countChildsOfNode;
	node->childsOfNodeArray = new Node *[node->countChildsOfNode];
}

void createChildsOfNode(Node *node, int index, int levelOfSon)
{
	for (int i = 0; i < node->countChildsOfNode; i++)
	{
		node->childsOfNodeArray[i] = new Node;
		node->childsOfNodeArray[i]->numberOfSon = index + i;
		node->childsOfNodeArray[i]->levelOfSon = levelOfSon;
	}
}

Node *recursiveCreateTreeFromInput(Node *node, int index, int levelOfSon)	
{
	node->numberOfSon = index;					
	node->levelOfSon = levelOfSon;
	readValueOfNodeFromKeyboard(node);
	readChildsOfNodeFromKeyboard(node);
	levelOfSon++;		
	createChildsOfNode(node, index, levelOfSon);
	for (int i = 0; i < node->countChildsOfNode; i++)	
		recursiveCreateTreeFromInput(node->childsOfNodeArray[i], index + i, levelOfSon); 
	return node;									
}

void recursivePrintTree(Node *node)						 
{
	if (node)									
	{
		for (int i = 0; i < (node->levelOfSon); i++) 
			cout << "  ";								
		if (node->childsOfNodeArray != NULL)				
		cout << node->nodeValue << endl;			
		if ((node->countChildsOfNode) != 0)					
			for (int i = 0; i < (node->countChildsOfNode); i++) 
				recursivePrintTree(node->childsOfNodeArray[i]);		 
	}
}

void recursiveDeleteTree(Node *node)				
{
	if ((node->countChildsOfNode) != 0)				
		for (int i = 0; i < (node->countChildsOfNode); i++)
			recursiveDeleteTree(node->childsOfNodeArray[i]);		
	delete[] node->childsOfNodeArray;					
}

Node *recursiveSearchNode(Node *node, int targetHeight, int heightOfNode)	
{
	if (node)
	{
		if (heightOfNode == targetHeight)						
			return node;								
		for (int i = 0; i < node->countChildsOfNode; i++)
		{
			recursiveSearchNode(node->childsOfNodeArray[i], targetHeight, heightOfNode++);
		}
	}
														
}

Node *recursiveSearchMinWidthOfNode(Node *node, Node **min)	
{
	if (*min == NULL)					
		*min = node;						
	else if (node->countChildsOfNode < (*min)->countChildsOfNode)			
		*min = node;							
	for (int i = 0; i < node->countChildsOfNode; i++)
	{
		recursiveSearchMinWidthOfNode(node->childsOfNodeArray[i], min);		
	}
	return *min;
}

Node *recursiveSearchMaxWidthOfNode(Node *node, Node **max)	
{
	if (*max == NULL)										
	*max = node;													
	else if (node->countChildsOfNode > (*max)->countChildsOfNode)	
	*max = node;													

	for (int i = 0; i < node->countChildsOfNode; i++)
		{
			recursiveSearchMaxWidthOfNode(node->childsOfNodeArray[i], max);		
		}
	return *max;
}

int main()
{
	setlocale(LC_ALL, "RUS");				
	cout << "Первое число - номер уровня, второе число - номер элемента в уровне\n";
	Node *tree;								
	tree = new Node;						
	tree = recursiveCreateTreeFromInput(tree, 0, 0);			
	recursivePrintTree(tree);						
	cout << "Введите нужную высоту: " << endl;
	int targetHeight;							
	cin >> targetHeight;					
	Node *treeOfTargetHeight;
	treeOfTargetHeight = new Node;							
	treeOfTargetHeight = recursiveSearchNode(tree, targetHeight, 0);	
	Node *min = NULL, *max = NULL;			
	min=recursiveSearchMinWidthOfNode(treeOfTargetHeight, &min);			
	min=recursiveSearchMaxWidthOfNode(treeOfTargetHeight, &max);
	if (min)
	{
		cout << "Самое узкое дерево заданной высоты" << endl;
		recursivePrintTree(min);
	}
	else
	{
		cout << "Самое узкое дерево заданной высоты не найдено" << endl;
	}

	if (max)					
	{
		cout << "Самое широкое дерево заданной высоты" << endl;
		recursivePrintTree(max);						
	}
	else
	{
		cout << "Самое широкое дерево заданной высоты не найдено" << endl;
	}

	recursiveDeleteTree(tree);						
	recursiveDeleteTree(treeOfTargetHeight);	
	recursiveDeleteTree(min);
	recursiveDeleteTree(max);
	return 0;													
}
