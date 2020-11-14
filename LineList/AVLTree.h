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
	SearchTree<T>* father;
	void printAllR();                     // 中遍历打印所有节点 实际代码
public:
	SearchTree(T elem = 0);               // 构造函数
	SearchTree(const SearchTree& target); // 拷贝构造函数
	~SearchTree();                        // 析构函数
	void clone(const SearchTree& target); // 拷贝类
	T getNode();                          // 返回node成员变量
	bool insert(T elem);                  // 添加结点
	SearchTree<T>* find(T elem);          // 查找节点 返回节点地址
	bool remove(T elem);                  // 删除节点 有则返回1 无则返回0
	SearchTree<T>*  findMin();            // 查找最小节点 返回节点地址
	void printAll();                      // 中遍历打印所有节点 初步引用
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
	this->left   = nullptr;
	this->right  = nullptr;
	this->father = nullptr;
}

template<typename T>
SearchTree<T>::SearchTree(const SearchTree<T>& target)
{
	this->clone(target);
}

template<typename T>
SearchTree<T>::~SearchTree()
{

}

template<typename T>
void SearchTree<T>::clone(const SearchTree<T>& target)
{
	if(target == nullptr)
	{
		this.node  = 0;
		this.left  = nullptr;
		this.right = nullptr;
		this.father = nullptr;
	}
	else
	{
		this.node   = target.node;
		this.left   = target.left;
		this.right  = target.right;
		this.father = target.father;
	}
}

template<typename T>
T SearchTree<T>::getNode()
{
	return this->node;
}

template<typename T>
bool SearchTree<T>::insert(T elem)
{
	if (elem < this->node) //左节点递归
	{
		if (this->left == nullptr)
		{
			this->left = new SearchTree<T>(elem);
			this->left->father = this;
			return true;
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
			this->right = new SearchTree<T>(elem);
			this->right->father = this;
			return true;
		}
		else
		{
			return this->right->insert(elem);
		}		
	}
	else //二叉树不允许有相同内容的节点
	{
		//std::cout << "[ERROR] binary search tree not allow have several same node" << std::endl;
		return false;
	}
}

template<typename T>
SearchTree<T>* SearchTree<T>::find(T elem) // 查找节点 返回节点地址
{
	if (this == nullptr)
	{
		return nullptr;
	}
	if (elem < this->node) //左节点递归
	{
		return this->left->find(elem);
	}
	else if (elem > this->node) //右节点递归
	{
		return this->right->find(elem);
	}
	else if (elem == this->node)
	{
		return this;
	}
}

template<typename T>
bool SearchTree<T>::remove(T elem)
{
	SearchTree<T>* ptr = this->find(elem);   //递归获取节点
	SearchTree<T>* closestNode = ptr->right->findMin(); //获取右子节点中的最小节点 应为最接近原节点的值(之一)
	SearchTree<T>* fatherToPtr = (ptr->father->left == ptr) ? //TODO 完成删除
	if (ptr->left == nullptr)
	{
		if (ptr->father->left == ptr)
		{
			ptr->father->left = ptr->right;
		}
		else
		{
			ptr->father->right = ptr->right;
		}
	}
	else
	{
		if (ptr->father->left == ptr)
		{
			ptr->father->left = closestNode;
		}
		else
		{
			ptr->father->right = closestNode;
		}
		closestNode->father->left = closestNode->right; //准备删除原有最小节点 对父节点进行操作 最小节点不存在更小节点 必不存在左孩子 因此将其右孩子连接至父节点即可
		closestNode->right->father = closestNode->father; //对子节点进行操作
		closestNode->clone(*ptr);
	}
	delete ptr;
	return true;
}

template<typename T>
SearchTree<T>* SearchTree<T>::findMin()
{
	if (this == nullptr)
	{
		return nullptr;
	}
	if (this->left == nullptr)
	{
		return this;
	}
	return this->left->findMin();
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
