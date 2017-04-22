#include <vector>
#include <queue>
#include <string>

#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
using namespace std;

/*USAGE
 * initialization : Trie* trie = new Trie();
 * destroy trie object after use : delete trie
 * add word to trie : trie->addWord("word")
 * delete word from trie : trie->deleteWord("word")
 * find all words with same prefix : trie queue<string>q = trie->findAll("word")
*/

class Node {
	
private:
	char mContent;
	bool mMarker;
	vector <Node*> mChildren;
public:
	Node() {
		mContent = '\0';
		mMarker = false;
	}
	
	~Node() {}
	
	char content() {
		return mContent;
	}
	
	void setContent(char c) {
		mContent = c;
	}
	
	bool wordMarker() {
		return mMarker;
	}
	
	void setWordMarker() {
		mMarker = true;
	}
	
	void resetWordMarker() {
		mMarker = false;
	}
	
	Node* findChild(char);
	
	void appendChild(Node* child) {
		mChildren.push_back(child);
	}
	
	vector<Node*> childern() {
		return mChildren;
	}
};

Node* Node::findChild(char c) {
	for(int i = 0; i < (int)mChildren.size(); i++) {
		Node * tmp = mChildren[i];
		if(tmp->mContent == c)
			return tmp;
	}
	
	return NULL;
}


class Trie {

private:
	Node* root;
	
public:
	Trie() {
		root = new Node();
	}
	void addWord(string);
	bool searchWord(string);
	void deleteWord(string);
	friend queue<string> trieTraverse(Node*, string, queue<string>);
	friend void deleter(Node*);
	queue<string> findAll(string);
	~Trie();
};

void Trie :: addWord(string s) {
	Node* current = root;
	
	for(int i = 0; i < (int)s.length(); i++) {
		Node* child = current->findChild(s[i]);
		if(child != NULL) {
			current = child;
		}
		else {
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
	}
	current->setWordMarker();
}

bool Trie::searchWord(string s) {
	Node* current = root;

	for(int i = 0; i < (int)s.length(); i++) {
		Node* tmp = current->findChild(s[i]);
			
		if(tmp == NULL)
			return false;
			
		current = tmp;
	}
		
	if(current->wordMarker())
		return true;

	return false;
}

queue<string> trieTraverse(Node* current, string s, queue<string>&q) {
	if(current->wordMarker())
		q.push(s);
		
	vector<Node*> child = current->childern();
	for(int i = 0; i < (int)child.size(); i++) {
		Node* tmp = child[i];
		if(tmp != NULL)
			trieTraverse(tmp, s + tmp->content(), q);
	}
	return q;
}

queue<string> Trie::findAll(string s) {
	Node* current = root;
	queue<string>q;
	
	for(int i = 0; i < (int)s.size(); i++) {
		Node* tmp = current->findChild(s[i]);
		
		if(tmp == NULL)
			return q;
		
		current = tmp;
	}
	return trieTraverse(current, s, q);
}

void deleter(Node* current) {
	vector<Node*> child = current->childern();
	for(int i = 0; i < (int)child.size(); i++) {
		Node *tmp = child[i];
		if(tmp != NULL)
			deleter(tmp);
	}
	delete current;
}

Trie :: ~Trie() {
	deleter(root);
}

void Trie:: deleteWord(string s) {
	Node* current = root;
	for(int i = 0; i < (int)s.length(); i++) {
		Node* tmp = current->findChild(s[i]);
		
		if(tmp != NULL)
			current = tmp;
		else
			return;
	}
	current->resetWordMarker();
}

#endif
