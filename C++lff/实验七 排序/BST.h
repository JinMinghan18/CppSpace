#pragma once
#include<iostream>
#include<cstring>
using namespace std;

template<typename Data>
class BST{
	public:
		BST();
		bool empty() const;
		
		bool search(const Data &item);//���Ҹ����Ƿ���item
		void add(const Data &item);//��ӽڵ�
		void remove(const Data &item);//ɾ���ڵ� 
		void inorder(int* &x) const;//�����������
		void free();//�������� 
	private:
		class BinNode{
			public:
				Data data;
				BinNode* left;
				BinNode* right;
				BinNode():left(0),right(0){}
				BinNode(Data item):data(item),left(0),right(0){}
		};
		typedef BinNode* BinNodePointer;
		void inorderAux(int* &x, BST<Data>::BinNodePointer subtreeptr) const;//���������������
		void search2(const Data &item,bool & found,BinNodePointer & locptr,BinNodePointer & parent) const;//��λitem�ڵ��˫�׽ڵ� 
		void freeAux(BinNode* myRoot);//���������������� 
		BinNodePointer myRoot;
};
template<typename Data>
inline BST<Data>::BST():myRoot(0){}
 
template<typename Data>
inline bool BST<Data>::empty() const{
	return myRoot==0;
}

template<typename Data>
inline void BST<Data>::inorder(int* &x) const//����������� 
{
	inorderAux(x, myRoot);
}
template<typename Data>
void BST<Data>::inorderAux(int* &x, BST<Data>::BinNodePointer subtreeRoot) const//��������������� 
{
	static int i = 1;
	if (subtreeRoot != 0)
	{
		inorderAux(x, subtreeRoot->left);
		x[i++] = subtreeRoot->data;
		inorderAux(x, subtreeRoot->right);
	}
}
template<typename Data>
bool BST<Data>::search(const Data & item)//����item 
{
	BST<Data>::BinNodePointer locptr = myRoot;
	bool found = false;
	while (!found && locptr != 0)
	{
		if (item < locptr->data)
			locptr = locptr->left;
		else if (locptr->data < item)
			locptr = locptr->right;
		else
			found = true;
	}
	return found;
}
template<typename Data>
void BST<Data>::add(const Data & item)//��ӽڵ� 
{
	BST<Data>::BinNodePointer
		locptr = myRoot,
		parent = 0;
	bool found = false;
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)
			locptr = locptr->left;
		else if (locptr->data < item)
			locptr = locptr->right;
		else
			found = true;
	}
	if (!found)
	{
		locptr = new BST<Data>::BinNode(item);
		if (parent == 0)
			myRoot = locptr;
		else if (item < parent->data)
			parent->left = locptr;
		else
			parent->right = locptr;
	}
	else
		cout << "Item already in the tree\n";
}
template<typename Data>
void BST<Data>::search2(const Data & item, bool & found, BinNodePointer &locptr, BinNodePointer &parent) const//��λitem�ڵ��˫�׽ڵ� 
{
	locptr = myRoot;
	parent = 0;
	found = false;
	while (!found && locptr != 0)
	{
		if (item < locptr->data)
		{
			parent = locptr;
			locptr = locptr->left;
		}
		else if (item > locptr->data)
		{
			parent = locptr;
			locptr = locptr->right;
		}
		else
			found = true;
	}
}
template<typename Data>
void BST<Data>::remove(const Data & item)//ɾ���ڵ� 
{
	bool found;
	BST<Data>::BinNodePointer
		x,
		parent;
	search2(item, found, x, parent);
	if (!found)
	{
		cout << "Item nod in the BST\n";
		return;
	}
	if (x->left != 0 && x->right != 0)
	{
		BST<Data>::BinNodePointer xSucc = x->right;
		parent = x;
		while (xSucc->left != 0)
		{
			parent = xSucc;
			xSucc = xSucc->left;
		}
		x->data = xSucc->data;
		x = xSucc;
	}

	BST<Data>::BinNodePointer subtree = x->left;
	if (subtree == 0)
		subtree = x->left;
	if (parent == 0)
		myRoot = subtree;
	else if (parent->left == x)
		parent->left = subtree;
	else
		parent->right = subtree;
	delete x;
}
template<typename Data>
void BST<Data>::free() {
	freeAux(myRoot);
}
template<typename Data>
void BST<Data>::freeAux(BinNode* myRoot) {
	if (myRoot != 0)
	{
		BinNode* left = myRoot->left;
		BinNode* right = myRoot->right;
		delete myRoot;
		if (left != 0)
			freeAux(left);
		if (right != 0)
			freeAux(right);
	}
}