#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>
#include <string>

//----------------------
//二叉查找树 SearchTree 所有节点均符合:左儿子<父亲<右儿子
//----------------------
template<typename T>
class SearchTree
{
private:
	T node;
	SearchTree<T>* left;
	SearchTree<T>* right;
	void printAllR();        // 中遍历打印所有节点 实际代码
public:
	SearchTree(T elem = 0); // 构造函数
	~SearchTree();          // 析构函数
	void insert(T elem);    // 添加结点
	bool find(T elem);      // 查找节点 有则返回1 无则返回0
	bool remove(T elem);    // 删除节点 有则返回1 无则返回0
	void printAll();        // 中遍历打印所有节点 初步引用
};

//----------------------
//AVL树 原于二叉查找树 SearchTree
//属于平衡树 最大节点高度差不大于1
//通过旋转达到效果
//----------------------
//template<typename T>
//class AVLTree
//{
//private:
//public:

//};

template<typename T>
SearchTree<T>::SearchTree(T elem)
	:node(elem)
{
	this->left  = nullptr;
	this->right = nullptr;
}

template<typename T>
SearchTree<T>::~SearchTree()
{

}

template<typename T>
void SearchTree<T>::insert(T elem)
{
	if (elem < this->node) //左节点递归
	{
		if (this->left == nullptr)
		{
			this->left = new SearchTree<T>(elem);
			return;
		}
		else
		{
			this->left->insert(elem);
		}
	}
	else if (elem > this->node) //右节点递归
	{
		if (this->right == nullptr)
		{
			this->right = new SearchTree<T>(elem);
			return;
		}
		else
		{
			this->right->insert(elem);
		}		
	}
	else //二叉树不允许有相同内容的节点
	{
		std::cout << "[ERROR] binary search tree not allow have several same node" << std::endl;
		return;
	}
}

template<typename T>
bool SearchTree<T>::find(T elem)
{
	if (this == nullptr)
	{
		return false;	
	}
	if (elem == this->node)
	{
		return true;
	}
	else if (elem < this->node) //左节点递归
	{
		return this->left->find(elem);
	}
	else if (elem > this->node) //右节点递归
	{
		return this->right->find(elem);
	}
	return false; //正常不会出现 可能出现在类大小于运算符重载错误的情况
}

template<typename T>
bool SearchTree<T>::remove(T elem)
{
	if (elem < this->node) //左节点递归
	{
		if (this->left == nullptr)
		{
			return false;
		}
		else
		{
			return this->left->insert(elem);
		}
	}
	else if (elem > this->node) //右节点递归
	{
		if (this->right == nullptr)
		{
			return false;
		}
		else
		{
			return this->right->insert(elem);
		}		
	}
	else //找到后删除
	{
		delete this;
		return true;
	}
}

template<typename T>
void SearchTree<T>::printAllR()
{
	if (this == nullptr)
	{
		return;
	}
	this->left->printAllR();
	std::cout << this->node << "  ";
	this->right->printAllR();
}

template<typename T>
void SearchTree<T>::printAll()
{
	printAllR();
	std::cout << std::endl;
}

#endif
