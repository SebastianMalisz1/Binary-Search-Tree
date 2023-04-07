#pragma once
#include <iostream>

/**
*@class BST
*@tparam T the data type of the elements in the BST
*Class representing a Binary Search Tree data structure.
*/
template <class T>
class BST {
	/*
	* @struct Node
	*
	* Struct representing a Node in the BST.
	* Each Node contains a value of type T, and a pointer to its left and right children.
	*/
	struct Node {
		T value;
		Node* left;
		Node* right;
	};

public:
	/**
	* @brief Default constructor for BST
	* Initializes an empty BST
	*/
	BST();
	/**
	*@brief Constructor for BST
	* @param value the value to insert into the BST
	*
	* Initializes a BST with the given value as the root
	*/
	BST(T value);

	/**
	 * @brief Inserts a value into the BST
	 * @param value the value to insert
	 * @return true if the value was inserted successfully, false otherwise
	 */
	bool Insert(T value);

	/**
	 * @brief Inserts a value into the BST
	 * @param value the value to insert
	 * @param node the node to start the insertion from
	 * @return true if the value was inserted successfully, false otherwise
	 */
	bool Insert(T value, Node* node);

	/**
	 * @brief Searches the BST for a given value
	 * @param value the value to search for
	 * @return true if the value is found in the BST, false otherwise
	 */
	bool Search(T value);

	/**
	 * @brief Searches the BST for a given value
	 * @param value the value to search for
	 * @param node the node to start the search from
	 * @return true if the value is found in the BST, false otherwise
	 */
	bool Search(T value, Node* node);

	/*
	 * @brief Deletes an element with the given value from the BST 
	 * @param value the value of the element to delete
	 * @return true if element was deleted successfully, false otherwise
	*/
	bool DeleteElement(T value);

	/*
	 * @brief Deletes an element with the given value from the BST
	 * @param value the value of the element to delete
	 * @param node the node to start the deletion from
	 * @return true if element was deleted successfully, false otherwise
	*/
	bool DeleteElement(T value, Node*& node);


	/**
	 * @brief Deletes a given node from the BST
	 * @param node the node to delete
	 */
	void Delete(Node* node);

	/**
	 * @brief Copy constructor for BST
	 * @param copy the BST to copy
	 */
	BST(const BST<T>& copy);

	/**
	 * @brief Move constructor for BST
	 * @param copied the BST to move
	 */
	BST(BST<T>&& copied) noexcept;

	/**
	 * @brief Move assignment operator for BST
	 * @param copied the BST to move
	 * @return a reference to the newly moved BST
	 */
	BST& operator=(BST<T>&& copied) noexcept;

	/**
	 * @brief Copy assignment operator for BST
	 * @param other the BST to copy
	 * @return a reference to the newly copied BST
	 */
	BST& operator=(const BST<T>& other) noexcept;

	/**
	 * @brief Performs an in-order traversal of the BST
	 */
	void inOrderTraversal();

	/**
	 * @brief Helper function for in-order traversal
	 * @param node the node to start the traversal from
	 */
	void inOrderTraversal(Node* node);

	/**
	 * @brief Performs a pre-order traversal of the BST
	 */
	void preOrderTraversal();

	/**
	 * @brief Helper function for pre-order traversal
	 * @param node the node to start the traversal from
	 */
	void preOrderTraversal(Node* node);

	/**
	* @brief Performs a post-order traversal of the BST
	*/
	void postOrderTraversal();

	/**
	 * @brief Helper function for post-order traversal
	 * @param node the node to start the traversal from
	 */
	void postOrderTraversal(Node* node);

	/**
	* @brief Serializes the BST to a file
	* @param fileName the name of the file to save the serialized BST to
	*/
	void Serialize(const std::string& fileName);

	/**
	 * @brief Deserializes a BST from a file
	 * @param fileName the name of the file to load the serialized BST from
	 */
	void Deserialize(const std::string& fileName);

	/**
	 * @brief Destructor for BST
	 */
	~BST();
private:

	Node* root;
	/**
	* @brief Helper function for the copy constructor
	* @param node the node to start the copy from
	* @return a pointer to the newly copied node
	*/
	Node* copyHelper(Node* node);

	/**
	 * @brief Helper function for Deserialize
	 * @param stream the input stream to read the serialized data from
	 * @return a pointer to the newly deserialized node
	 */
	Node* DeserializeHelper(std::istream& stream);

	/**
	 * @brief Helper function for Serialize
	 * @param node the node to start the serialization from
	 * @param stream the output stream to write the serialized data to
	 */
	void SerializeHelper(Node* node, std::ostream& stream);
};




