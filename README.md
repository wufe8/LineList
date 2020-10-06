# LineList

一堆有各种基本数据结构的文件 自学用  

本仓库(目前)包含以下内容  

1.[链表](LineList/Linelist.h) 双向链表 根据STL std::list模板类的成员函数进行模仿与兼容 但不使用迭代器  
2.[简易链表](LineList/SimpleLinkedList.h) 双向链表 较久前的个人实现了 已定归档  
3.[信号槽](LineList/SignalSlot.h) 信号与槽的实现 目前因不会解决编译期确定模板类实例 因此无法实现模板通用性  

## 目录

- [描述](#描述)
- [结构](#结构)
- [使用](#使用)
- [维护者](#维护者)
- [如何贡献](#如何贡献)
- [使用许可 LICENSE](#使用许可)

## 描述
自己研究和照着葫芦画的数据结构轮子  
研究学习数据结构用  

## 结构
```
LineList
|--README.md
|--.gitignore
|--LineList.sln				//vs工程文件
|--LineList             	
	|--LineList.h			//兼容链表头文件 模板类 包含实现
	|--pch.h				//预编译
	|--makefile				//编译配置
	|--SignalSlot.cpp		//信号槽实现
	|--SignalSlot.h			//信号槽声明
	|--SimpleLinkedList.h	//旧TLinkedList类及其继承子类
	|--test					//测试 二进制
	|--test.cpp				//测试
	|--Toolkit.h			//调试工具用函数
```

## 使用
**使用方法参考test.cpp**
类:
`TSimpleDoubleLL` 双向链表  
`TStackSLL` 栈  
`TQueueSLL` 队列  


## 维护者
Wufe8

## 如何贡献
或许可以提点issue 如果我哪个地方做的太烂 xd

## 使用许可
随意使用(虽然也不会有人用) 毕竟是烂大街的东西(笑)
