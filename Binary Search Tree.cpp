#include <iostream>
#include "Binary Search Tree.h"
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#define TOSTRING(x) #x

template<class T>
inline BST<T>::BST()
{
	root = nullptr;
}

template<class T>
inline BST<T>::BST(T value)
{
	root = new Node;
	root->value = value;
	root->left = nullptr;
	root->right = nullptr;
}

template<class T>
bool BST<T>::Insert(T value)
{
	if (root == nullptr)
	{
		root = new Node;
		root->value = value;
		root->left = nullptr;
		root->right = nullptr;
		return true;
	}

	if (value == root->value)
		return false;

	if (value < root->value)
	{
		if (root->left == nullptr)
		{
			Node* left = new Node;
			left->value = value;
			left->left = nullptr;
			left->right = nullptr;
			root->left = left;
			return true;
		}
		else
			return Insert(value, root->left);
	}
	else
	{
		if (root->right == nullptr)
		{
			Node* right = new Node;
			right->value = value;
			right->left = nullptr;
			right->right = nullptr;
			root->right = right;
			return true;
		}
		else
			return Insert(value, root->right);
	}
	return false;
}

template<class T>
bool BST<T>::Insert(T value, Node* node)
{
	if (value == node->value)
		return false;

	if (value < node->value)
	{
		if (node->left == nullptr)
		{
			Node* left = new Node;
			left->value = value;
			left->left = nullptr;
			left->right = nullptr;
			node->left = left;
			return true;
		}
		else
			return Insert(value, node->left);
	}
	else
	{
		if (node->right == nullptr)
		{
			Node* right = new Node;
			right->value = value;
			right->left = nullptr;
			right->right = nullptr;
			node->right = right;
			return true;
		}
		else
			return Insert(value, node->right);
	}
	return false;
}

template<class T>
bool BST<T>::Search(T value)
{
	if (root == nullptr)
		return false;

	if (root->value == value)
		return true;

	if (root->left != nullptr)
		if (value < root->value)
			return Search(value, root->left);

	if (root->right != nullptr)
		if (value > root->value)
			return Search(value, root->right);

	return false;
}

template<class T>
bool BST<T>::Search(T value, Node* node)
{
	if (node->value == value)
		return true;

	if (node->left != nullptr)
		if (value < node->value)
			return Search(value, node->left);

	if (node->right != nullptr)
		if (value > node->value)
			return Search(value, node->right);

	return false;
}

template<class T>
bool BST<T>::DeleteElement(T value) {
	return DeleteElement(value, root);
}

template<class T>
bool BST<T>::DeleteElement(T value, Node*& node) {
	if (node == nullptr) {
		return false;
	}
	else if (value < node->value) {
		return DeleteElement(value, node->left);
	}
	else if (value > node->value) {
		return DeleteElement(value, node->right);
	}
	else {
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
			return true;
		}
		else if (node->left == nullptr) {
			Node* temp = node;
			node = node->right;
			delete temp;
			return true;
		}
		else if (node->right == nullptr) {
			Node* temp = node;
			node = node->left;
			delete temp;
			return true;
		}
		else {
			Node* temp = node->right;
			while (temp->left != nullptr) temp = temp->left;
			node->value = temp->value;
			return DeleteElement(temp->value, node->right);
		}
	}
}


template<class T>
void BST<T>::Delete(Node* node)
{
	if (node->left != nullptr)
	{
		Delete(node->left);
		delete node->left;
	}
	if (node->right != nullptr)
	{
		Delete(node->right);
		delete node->right;
	}
}


template<class T>
inline BST<T>::BST(const BST<T>& copy)
{
	root = copyHelper(copy.root);
}


template<class T>
typename BST<T>::Node* BST<T>::copyHelper(Node* node)
{
	if (node == nullptr) {
		return nullptr;
	}
	Node* newNode = new Node{ node->value };
	newNode->left = copyHelper(node->left);
	newNode->right = copyHelper(node->right);
	return newNode;
}


template<class T>
BST<T>::BST(BST<T>&& copied) noexcept
{
	root = std::move(copied.root);
	copied.root = nullptr;
}

template<class T>
typename BST<T>::BST& BST<T>::operator=(BST<T>&& copied) noexcept
{
	if (this != &copied)
	{
		if (root != nullptr)
		{
			Delete(root);
		}
			root = std::move(copied.root);
			copied.root = nullptr;

	}
	return *this;
}


template<class T>
typename BST<T>::BST& BST<T>::operator=(const BST<T>& other) noexcept
{
	if (this != &other)
	{
		if (root != nullptr)
		{
			Delete(root);
		}
			root = copyHelper(other.root);
	}
	return *this;
}


template<class T>
void BST<T>::inOrderTraversal()
{
	inOrderTraversal(root);
}

template<class T>
void BST<T>::inOrderTraversal(Node* node)
{
	if (node != nullptr)
	{
		inOrderTraversal(node->left);
		std::cout << node->value << " ";
		inOrderTraversal(node->right);
	}
}

template<class T>
void BST<T>::preOrderTraversal()
{
	preOrderTraversal(root);
}

template<class T>
void BST<T>::preOrderTraversal(Node* node)
{
	if (node != nullptr)
	{
		std::cout << node->value << " ";
		preOrderTraversal(node->left);
		preOrderTraversal(node->right);
	}
}



template<class T>
void BST<T>::postOrderTraversal()
{
	postOrderTraversal(root);
}

template<class T>
void BST<T>::postOrderTraversal(Node* node)
{
	if (node != nullptr)
	{
		postOrderTraversal(node->left);
		postOrderTraversal(node->right);
		std::cout << node->value << " ";
	}
}


template <class T>
void BST<T>::Serialize(const std::string& fileName) {
	std::ofstream outfile(fileName);
	if (!outfile.is_open()) {
		outfile.open(fileName, std::ios::out);
	}
	SerializeHelper(root, outfile);
	outfile.close();
}

template <class T>
void BST<T>::SerializeHelper(Node* node, std::ostream& stream) {
	if (node == nullptr) {
		stream << "";
		return;
	}

	SerializeHelper(node->left, stream);
	stream << node->value << " ";
	SerializeHelper(node->right, stream);
}



template <class T>
void BST<T>::Deserialize(const std::string& fileName) {
	std::ifstream infile(fileName);
	if (!infile.is_open()) {
		throw std::runtime_error("Error: Unable to open file " + fileName);
	}
	DeserializeHelper(infile);
	infile.close();
}

template <class T>
typename BST<T>::Node* BST<T>::DeserializeHelper(std::istream& stream) {
	T text;
	stream >> std::ws >> text;
	if (stream.eof()) {
		return nullptr;
	}
	this->Insert(text);
	DeserializeHelper(stream);
	return nullptr;
}


void test1()
{
	std::cout << "Test for intigers\n\n";
	//Creating binary search tree using default constructor
	BST<int> tree1;

	//Inserting elements to the binary search tree tree1
	tree1.Insert(4);
	tree1.Insert(7);
	tree1.Insert(21);
	tree1.Insert(0);

	//Printing in console elements in In-Order Traversal
	//Expectations: 0 4 7 21
	std::cout << "Expectations: 0 4 7 21" << std::endl;
	std::cout << "In-Order Traversal: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console elements in Pre-Order
	//Expectations: 4 0 7 21
	std::cout << "Expectations: 4 0 7 21" << std::endl;
	std::cout << "Pre-Order Traversal: ";
	tree1.preOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console elements in Post-Order Traversal
	//Expectations: 0 21 7 4
	std::cout << "Expectations: 0 21 7 4" << std::endl;
	std::cout << "Post-Order Traversal: ";
	tree1.postOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Searching object tree1 to find 17
	//Expected value: 0 (due to bool function)
	std::cout << "Expectations: 0" << std::endl;
	std::cout << "Searching for 17: " << tree1.Search(17) << std::endl << std::endl;;

	//Searching object tree1 to find 7
	//Expected value: 1 (due to bool function)
	std::cout << "Expectations: 1" << std::endl;
	std::cout << "Searching for 7: " << tree1.Search(7) << std::endl << std::endl;

	//Deleting element 7 from tree1
	tree1.DeleteElement(7);

	//Printing in console current content of tree1 in In-Order Traversal
	//Expectations: 0 4 21
	std::cout << "Expectations: 0 4 21" << std::endl;
	std::cout << "In-Order Traversal without 7: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Creating new object tree2 using copy constructor: tree2 copies content from tree1
	BST<int> tree2(tree1);

	// Printing in console content of tree1
	std::cout << "Expectations: 0 4 21" << std::endl;
	std::cout << "In-Order Traversal of tree1: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console content of tree2
	std::cout << "Expectations: 0 4 21" << std::endl;
	std::cout << "In-Order Traversal of tree2: ";
	tree2.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Creating new object tree3 using move operator: tree3 moves content from tree1
	BST<int> tree3 = std::move(tree1);

	//Printing in console content of tree1 after move operation
	//Expetation: No content
	std::cout << "Expectations: EMPTY" << std::endl;
	std::cout << "In-Order Traversal of tree1 after move operation: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console content of tree3
	std::cout << "Expectations: 0 4 21" << std::endl;
	std::cout << "In-Order Traversal of tree3: ";
	tree3.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Inserting element 100 to tree2
	tree2.Insert(100);

	//Using assignment operator for tree1 to have tree2 content
	tree1 = tree2;

	// Printing in console content of tree1
	std::cout << "Expectations: 0 4 21 100" << std::endl;
	std::cout << "In-Order Traversal of tree1: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	// Printing in console content of tree2
	std::cout << "Expectations: 0 4 21 100" << std::endl;
	std::cout << "In-Order Traversal of tree2: ";
	tree2.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Creating new object tree3 using move operator: tree3 moves content from tree1
	BST<int> tree4 = std::move(tree1);

	//Printing in console content of tree1
	//Expectations: No content
	std::cout << "Expectations: EMPTY" << std::endl;
	std::cout << "In-Order Traversal of tree1 after move operation: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console content of tree4
	//Expectations: 0 4 21 100
	std::cout << "Expectations: 0 4 21 100" << std::endl;
	std::cout << "In-Order Traversal of tree4: ";
	tree4.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Saving content of tree4 to the file "tree4.txt"
	tree4.Serialize("tree4.txt");

	//Inserting content to tree1
	tree1.Insert(10);
	tree1.Insert(100);
	tree1.Insert(1000);
	tree1.Insert(10000);

	//Saving content of tree1 to the file "tree4.txt"
	tree1.Serialize("tree1.txt");

	//Creating new object tree5
	BST<int> tree5;

	//Reading from file "tree1.txt" and writing it to tree5
	tree5.Deserialize("tree1.txt");
	std::cout << "Expectations: 10 100 1000 10000" << std::endl;
	std::cout << "In-Order Traversal of tree5: ";
	tree5.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;


}

void test2()
{

	std::cout << "Test for strings\n\n";
	//Creating binary search tree using default constructor
	BST<std::string> tree1;

	//Inserting elements to the binary search tree tree1
	tree1.Insert("hello");
	tree1.Insert("goodbye");
	tree1.Insert("milk");
	tree1.Insert("bread");
	tree1.Insert("water");

	//Printing in console elements in In-Order Traversal
	//Expectations: bread goodbye hello milk water
	std::cout << "Expectations: bread goodbye hello milk water" << std::endl;
	std::cout << "In-Order Traversal: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console elements in Pre-Order
	//Expectations: hello goodbye bread milk water
	std::cout << "Expectations: hello goodbye bread milk water" << std::endl;
	std::cout << "Pre-Order Traversal: ";
	tree1.preOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console elements in Post-Order Traversal
	//Expectations: bread goodbye water milk hello
	std::cout << "Expectations: bread goodbye water milk hello" << std::endl;
	std::cout << "Post-Order Traversal: ";
	tree1.postOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Searching object tree1 to find ball
	//Expected value: 0 (due to bool function)
	std::cout << "Expectations: 0" << std::endl;
	std::cout << "Searching for ball: " << tree1.Search("ball") << std::endl << std::endl;;

	//Searching object tree1 to find milk
	//Expected value: 1 (due to bool function)
	std::cout << "Expectations: 1" << std::endl;
	std::cout << "Searching for milk: " << tree1.Search("milk") << std::endl << std::endl;

	//Deleting element 7 from tree1
	tree1.DeleteElement("milk");

	//Printing in console current content of tree1 in In-Order Traversal
	//Expectations: break goodbye hello water
	std::cout << "Expectations: break goodbye hello water" << std::endl;
	std::cout << "In-Order Traversal without milk: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Creating new object tree2 using copy constructor: tree2 copies content from tree1
	BST<std::string> tree2(tree1);

	// Printing in console content of tree1
	//Expectations: break goodbye hello water
	std::cout << "Expectations: break goodbye hello water" << std::endl;
	std::cout << "In-Order Traversal of tree1: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console content of tree2
	//Expectations: break goodbye hello water
	std::cout << "Expectations: break goodbye hello water" << std::endl;
	std::cout << "In-Order Traversal of tree2: ";
	tree2.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Creating new object tree3 using move operator: tree3 moves content from tree1
	BST<std::string> tree3 = std::move(tree1);

	//Printing in console content of tree1 after move operation
	//Expetation: No content
	std::cout << "Expectations: EMPTY" << std::endl;
	std::cout << "In-Order Traversal of tree1 after move operation: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console content of tree3
	//Expectations: break goodbye hello water
	std::cout << "Expectations: break goodbye hello water" << std::endl;
	std::cout << "In-Order Traversal of tree3: ";
	tree3.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Inserting element 100 to tree2
	tree2.Insert("soccer");

	//Using assignment operator for tree1 to have tree2 content
	tree1 = tree2;

	// Printing in console content of tree1
	//Expectations: break goodbye hello soccer water
	std::cout << "Expectations: break goodbye hello soccer water" << std::endl;
	std::cout << "In-Order Traversal of tree1: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	// Printing in console content of tree2
	//Expectations: break goodbye hello soccer water
	std::cout << "Expectations: break goodbye hello soccer water" << std::endl;
	std::cout << "In-Order Traversal of tree2: ";
	tree2.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Creating new object tree3 using move operator: tree3 moves content from tree1
	BST<std::string> tree4 = std::move(tree1);

	//Printing in console content of tree1
	//Expectations: No content
	std::cout << "Expectations: EMPTY" << std::endl;
	std::cout << "In-Order Traversal of tree1 after move operation: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Printing in console content of tree4
	//Expectations: break goodbye hello soccer water
	std::cout << "Expectations: break goodbye hello soccer water" << std::endl;
	std::cout << "In-Order Traversal of tree4: ";
	tree4.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Saving content of tree4 to the file "tree4.txt"
	tree4.Serialize("tree4strings.txt");

	//Inserting content to tree1
	tree1.Insert("mother");
	tree1.Insert("father");
	tree1.Insert("daughter");
	tree1.Insert("grandmother");

	//Printing in console content of tree1
	//Expectations: daughter father grandmother mother
	std::cout << "Expectations: daughter father grandmother mother" << std::endl;
	std::cout << "In-Order Traversal of tree1: ";
	tree1.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

	//Saving content of tree1 to the file "tree4.txt"
	tree1.Serialize("tree1strings.txt");

	//Creating new object tree5
	BST<std::string> tree5;

	//Reading from file "tree1.txt" and writing it to tree5
	tree5.Deserialize("tree1strings.txt");
	std::cout << "Expectations: mother grandmother father daughter" << std::endl;
	std::cout << "In-Order Traversal of tree5: ";
	tree5.inOrderTraversal();
	std::cout << std::endl;
	std::cout << std::endl;

}


template<class T>
BST<T>::~BST()
{
	if (root == nullptr) {
		return;
	}
	Delete(root);
	delete root;
}


int main()
{
	test1();
	test2();

	return 0;
}

