#ifndef SEARCHTREE_H
#define SEARCHTREE_H

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
	T node;                              // 内容
	SearchTree<T>* left;                 // 左孩子
	SearchTree<T>* right;                // 右孩子
	SearchTree<T>* parent;               // 双亲
	void printAllR();                    // 中遍历打印所有节点 实际代码
	bool setSelf(SearchTree<T>* target); // 修改自身相对双亲的地址 用于同步子节点的变更
public:
	SearchTree(T elem = NULL);                // 构造函数
	~SearchTree();                         // 析构函数 请使用deleteAll删除整个树
	void clone(const SearchTree* target);  // 拷贝类 不会改变双亲
	T getNode();                           // 返回node成员变量
	bool insert(T elem);                   // 添加结点
	SearchTree<T>* find(T elem);           // 查找节点 返回节点地址
	SearchTree<T>* findMin();              // 查找最小节点 返回节点地址
	bool remove(T elem);                   // 删除节点 有则返回1 无则返回0
	void printAll();                       // 中遍历打印所有节点 初步引用
	void deleteAll();                      // 后序遍历删除整个树
};

template<typename T>
SearchTree<T>::SearchTree(T elem)
	:node(elem)
{
	this->left   = nullptr;
	this->right  = nullptr;
	this->parent = nullptr;
}

template<typename T>
SearchTree<T>::~SearchTree()
{

}

template<typename T>
void SearchTree<T>::clone(const SearchTree<T>* target)
{
	if (target == nullptr)
	{
		this->node  = 0;
		this->left  = nullptr;
		this->right = nullptr;
	}
	else
	{
		this->node  = target->node;
		this->left  = target->left;
		this->right = target->right;
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
			this->left->parent = this;
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
			this->right->parent = this;
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
	if (elem < this->node) //左节点递归
	{
		if (this->left == nullptr) //找不到elem 返回nullptr
		{
			return nullptr;
		}
		else
		{
			return this->left->find(elem);
		}
	}
	else if (elem > this->node) //右节点递归
	{
		if (this->right == nullptr) //找不到elem 返回nullptr
		{
			return nullptr;
		}
		else
		{
			return this->left->find(elem);
		}
	}
	else //找到elem 返回地址
	{
		return this;
	}
}

template<typename T>
bool SearchTree<T>::remove(T elem)
{
	SearchTree<T>* ptr = this->find(elem);   //递归获取节点
	if (ptr == nullptr) //找不到elem节点
	{
		return false;
	}
	if (ptr->left != nullptr && ptr->right != nullptr) //有两个子节点 需要替换最接近elem的节点以代替删除的节点
	{
		SearchTree<T>* closestNode = ptr->right->findMin(); //获取右子节点中的最小节点 应为最接近原节点的值(之一)
		ptr->node = closestNode->node; //复制其node 保持树仍符合查找树规律
		ptr->right->remove(closestNode->node); //删除被复制的节点 因为是最接近elem的节点(之一) 其左孩子必为空
	}
	else if (ptr->left == nullptr && ptr->right == nullptr) //没有子节点 需要对父节点进行处理 避免野指针
	{
		ptr->setSelf(nullptr);
		delete ptr;
	}
	else //只有一个子节点(也可能是删除被复制节点) 将自身替换为子节点并与父节点连接以保持二叉查找树合法 而如果删除自身并将子节点与父节点连接 将在删除根节点时导致丢失根节点
	{
		SearchTree<T>* copyTarget = (ptr->left == nullptr) ? ptr->right : ptr->left;
		ptr->clone(copyTarget);
		if (copyTarget->left != nullptr) //处理子节点的双亲地址
		{
			copyTarget->left->parent = copyTarget->parent;
		}
		if (copyTarget->right != nullptr)
		{
			copyTarget->right->parent = copyTarget->parent;
		}
		delete copyTarget;
	}
	return true;
}

template<typename T>
SearchTree<T>* SearchTree<T>::findMin()
{
	if (this->left == nullptr)
	{
		return this;
	}
	return this->left->findMin();
}

template<typename T>
bool SearchTree<T>::setSelf(SearchTree<T>* target)
{
	if (this->parent->left == this)
	{
		this->parent->left = target;
		return true;
	}
	else if (this->parent->right == this)
	{
		this->parent->right = target;
		return true;
	}
	else
	{
		return false; //找不到自身 可能是parent不正确
	}
}

template<typename T>
void SearchTree<T>::printAllR()
{
	if (this->left != nullptr)
	{
		this->left->printAllR();
	}
	std::cout << this->node << " ";
	if (this->right != nullptr)
	{
		this->right->printAllR();
	}
}

template<typename T>
void SearchTree<T>::printAll()
{
	printAllR();
	std::cout << std::endl;
}

template<typename T>
void SearchTree<T>::deleteAll()
{
	if (this->left != nullptr)
	{
		this->left->deleteAll();
	}
	if (this->right != nullptr)
	{
		this->right->deleteAll();
	}
	delete this;
}

#endif
