// huffcode.cpp
// Aisha Petes
// 1 Dec 2017
//
// For CS 411Fall 2017
// Assignment 6
//
// Implements Huffman coding

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <memory>
#include <queue>
#include <vector>

pNode HuffCode::makeNode(char ch, int freq, pNode left, pNode right)
{
    pNode node = std::make_shared<Node>();

	node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

void HuffCode::genCode(const pNode &root, string str)
{
	// base case: no more nodes
	if (root == NULL)
		return;

	// if at a leaf node, store code
	if (!root->left && !root->right)
		huffCode[root->ch] = str;

	// search left and right nodes
	genCode(root->left, str + "0");
	genCode(root->right, str + "1");
}

string HuffCode::genText(const string &codestr) const
{
    string decoded = "";
    int n = codestr.size();

    auto curr = huffRoot;
    for (auto i=0; i<n; i++)
    {
        // traverse tree left for 0 and right for 1
        if (codestr[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;

        // check for leaf node and retrieve character
        if (!curr->left && !curr->right)
        {
            decoded += curr->ch;
            curr = huffRoot; //restart search
        }
    }
    return decoded;
}

void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    if(theweights.size()==0)
        return;

    pNode n1, n2, root;
    std::priority_queue<pNode, std::vector<pNode>, comp> pqueue;

	// create leaf nodes for each char and enqueue
	for (auto it : theweights)
        pqueue.push(makeNode(it.first, it.second, NULL, NULL));

	// while there is more than one node in the queue
    while(pqueue.size() > 1)
    {
        n1 = pqueue.top();
        pqueue.pop();
        n2 = pqueue.top();
        pqueue.pop();
		// create new node and enqueue
        pqueue.push(makeNode('\0', n1->freq + n2->freq, n1, n2));
    }

    // update root pointer
	huffRoot = pqueue.top();

	// generate code map
	genCode(huffRoot, "");
}


string HuffCode::encode(const string & text) const
{
	string code = "";
	for (char c:text) //retrieve codes for each character in text
		code += huffCode.find(c)->second;
    return code;
}


string HuffCode::decode(const string & codestr) const
{
    return genText(codestr);
}

