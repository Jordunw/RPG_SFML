#include "Autocomplete.h"

namespace autoc
{
	std::shared_ptr<Node> createNode(char newData)
	{
		// create the new node
		std::shared_ptr<Node> newNode = std::make_shared<Node>();
		// assign char and null everything else
		newNode->data = newData;
		newNode->end = 0;
		newNode->left = NULL;
		newNode->eq = NULL;
		newNode->right = NULL;

		return newNode;
	}

	// insert a word into the tree
	void insert(std::shared_ptr<Node>* root, const std::string& word, int pos)
	{
		// base case
		if (!(*root))
			*root = createNode(word[pos]);

		// if the current char is less than the roots data then insert into left subtree
		if ((*root)->data > word[pos])
			insert(&((*root)->left), word, pos);

		// else if greater insert into right subtree
		else if ((*root)->data < word[pos])
			insert(&((*root)->right), word, pos);

		// else if same as the roots data
		else
		{
			// if at the end of the word
			if (pos == word.size() - 1)
				(*root)->end = 1; // mark as end of the word
			else
				insert(&((*root)->eq), word, pos + 1);
		}
	}

	// traverse the tree
	void traverse(std::shared_ptr<Node> root, std::vector<std::string>& ret, char* buff, int depth)
	{
		// base case
		if (!root)
			return;

		// traverse the left tree
		traverse(root->left, ret, buff, depth);

		// store the current char
		buff[depth] = root->data;

		// if at the end of the string store it in the final ans
		if (root->end)
		{
			buff[depth + 1] = '\0'; // add the break char to the end
			ret.push_back(std::string(buff));
		}

		// traverse the equal subtree
		traverse(root->eq, ret, buff, depth + 1);

		// traverse the right subtree
		traverse(root->right, ret, buff, depth + 1);
	}

	// util function to find the words
	std::vector<std::string> util(std::shared_ptr<Node> root, const std::string& pattern)
	{
		// stores the words to suggest
		char buffer[1001];

		std::vector<std::string> ret;

		traverse(root, ret, buffer);

		if (root != nullptr && root->end == 1)
			ret.push_back(pattern);
		return ret;
	}

	// autocomplete function that returns suggestions
	std::vector<std::string> autocomplete(std::shared_ptr<Node> root, const std::string& pattern)
	{
		std::vector<std::string> words;
		int pos = 0;

		// if nothing works return empty suggestions
		if (pattern.empty())
			return words;

		// iterate over all the chars in the pattern to find words in the tree
		while (root && pos < static_cast<int>(pattern.length())) {

			// if current character is smaller
			if (root->data > pattern[pos])
				// search the left subtree
				root = root->left;

			// current character is greater
			else if (root->data < pattern[pos])
				// Search right subtree
				root = root->right;

			// If current character is equal
			else if (root->data == pattern[pos]) {

				// search equal subtree
				root = root->eq;
				pos++;
			}

			// if not found
			else
				return words;
		}

		// search for words in current node
		words = util(root, pattern);

		return words;
	}
}