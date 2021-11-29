#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Serialization.h"

namespace autoc
{
	class Node
	{
	public:
		// stored char
		char data;
		// end of word identifier
		int end; // 1 = end of word

		// left subtree
		class std::shared_ptr<Node> left;
		// equal subtree
		class std::shared_ptr<Node> eq;
		// right subtree
		class std::shared_ptr<Node> right;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(
				CEREAL_NVP(data),
				CEREAL_NVP(end),
				CEREAL_NVP(left),
				CEREAL_NVP(eq),
				CEREAL_NVP(right));
		}
	};

	std::shared_ptr<Node> createNode(char newData);

	// insert a word into the tree
	void insert(std::shared_ptr<Node>* root, const std::string& word, int pos = 0);

	// traverse the tree
	void traverse(std::shared_ptr<Node> root, std::vector<std::string>& ret, char* buff, int depth = 0);

	// util function to find the words
	std::vector<std::string> util(std::shared_ptr<Node> root, const std::string& pattern);

	// autocomplete function that returns suggestions
	std::vector<std::string> autocomplete(std::shared_ptr<Node> root, const std::string& pattern);
}