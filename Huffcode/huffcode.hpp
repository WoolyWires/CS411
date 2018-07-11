// huffcode.hpp
// Aisha Petes
// 1 Dec 2017
//
// For CS 411Fall 2017
// Assignment 6
//
// Header file for huffcode.cpp

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <unordered_map>
#include <memory>
#include <queue>
#include <vector>

// Tree node struct
struct Node
{
	char ch;
	int freq;
	std::shared_ptr<Node> left, right;
};
using pNode = std::shared_ptr<Node>;

// Comparison struct for priority queue
struct comp
{
	bool operator()(pNode const &n1, pNode const &n2)
	{
		return n1->freq > n2->freq;
	}
};

// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

// ***** HuffCode: private functions and data members *****
private:

    // class constructor for tree nodes
	pNode makeNode(char ch, int freq, pNode left, pNode right);
    // generates Huffman tree code and stores in map
	void genCode(const pNode &root, std::string str);
	// decodes given string using tree map
	std::string genText(const std::string &codestr) const;

	// map of Huffman tree code
	std::unordered_map<char, std::string> huffCode;
	// pointer to root of Huffman tree
	pNode huffRoot;

};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

