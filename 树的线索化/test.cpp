#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;

enum Tag{
	THREAD,
	LINK,
};
template<typename T>
struct BinaryTreeNode{
	T data;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;
	Tag _leftTag;
	Tag _rightTag;

	BinaryTreeNode(T _data)
		:data(_data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template<typename T>
class BinaryTree{
private:
	BinaryTreeNode<T> *_root;
protected:
	BinaryTreeNode<T> *_CreateBinaryTree(const char *a,size_t size,size_t & index)
	{
		BinaryTreeNode<T> *root = NULL;
		if(index < size && a[index] != '#'){
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateBinaryTree(a,size,++index);	
			root->_right = _CreateBinaryTree(a,size,++index);
		}
		return root;
	}
	void _InOrderThreading(BinaryTreeNode<T> *cur,BinaryTreeNode<T> * & prev)
	{
		if(cur == NULL)
			return;
		_InOrderThreading(cur->_left,prev);
		if(cur->_left == NULL)   //如果左为空，对左进行线索化
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if(prev && prev->_right == NULL)   //如果右为空，对右进行线索化
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		_InOrderThreading(cur->_right,prev);
	}

	void _PreOrderThreading(BinaryTreeNode<T> *cur,BinaryTreeNode<T> * & prev)
	{
		if(cur == NULL)
			return;
		if(cur->_left == NULL)   //如果左为空，对左进行线索化
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if(prev && prev->_right == NULL)   //如果右为空，对右进行线索化
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		if(cur->_leftTag == LINK)
			_PreOrderThreading(cur->_left,prev);

		if(cur->_rightTag == LINK)
			_PreOrderThreading(cur->_right,prev);
	}
	void _PostOrderThreading(BinaryTreeNode<T> *cur,BinaryTreeNode<T> * & prev)
	{
		if(cur == NULL)
			return;
		
		_PostOrderThreading(cur->_left,prev);
				_PostOrderThreading(cur->_right,prev);

		if(cur->_left == NULL)   //如果左为空，对左进行线索化
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if(prev && prev->_right == NULL)   //如果右为空，对右进行线索化
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
	}

public:
	BinaryTree(const char *a,size_t size)
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a,size,index);
	}
	void InOrderThreading()
	{
		BinaryTreeNode<T> *prev = NULL;
		_InOrderThreading(_root,prev);
	}
	void InOrderThd()
	{
		BinaryTreeNode<T> *cur = _root;
		while(cur)
		{
			while( cur && cur->_leftTag == LINK) //找到最左结点
				cur = cur->_left;
			cout<<cur->data<<" ";

			if(cur->_rightTag == THREAD){
				cur = cur->_right;
				cout<<cur->data<<" ";
			}

			cur = cur->_right;
		}
	}
	void PreOrderThreading()
	{
		BinaryTreeNode<T> *prev = NULL;
		_PreOrderThreading(_root,prev);
	}
	void PreOrderThd()
	{
		BinaryTreeNode<T> *cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK){
				cout<<cur->data<<" ";
				cur = cur->_left;
			}
			cout<<cur->data<<" ";
			cur = cur->_right;
		}
	}
	void PostOrderThreading()
	{
		BinaryTreeNode<T> *prev = NULL;
		_PostOrderThreading(_root,prev);
	}
	void PostOrderThd()
	{
		stack<BinaryTreeNode<T> *> s;
		BinaryTreeNode<T> *cur = _root;
		while(cur)
		{
			while(cur->_rightTag == LINK){
				s.push(cur);
				cur = cur->_right;
			}

			s.push(cur);
			cur = cur->_left;		    
		}
		while(s.size() > 0){
			BinaryTreeNode<T> *tmp = s.top();
			cout<<tmp->data<<" ";
			s.pop();
		}
	}
};
void test()
{
	char a[11] = "123##4##56";
	BinaryTree <char> B(a,10);
	/*B.InOrderThreading();
	B.InOrderThd();*/
	/*B.PreOrderThreading();
	B.PreOrderThd();*/
	B.PostOrderThreading();
	B.PostOrderThd();
}
int main()
{
	test();
	system("pause");
	return 0;
}