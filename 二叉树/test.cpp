#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stack>
using namespace std;

template<typename T>
struct BinaryTreeNode{
	T data;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;

	BinaryTreeNode(T _data)
		:data(_data)
		,_left(NULL)
		,_right(NULL)
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
	void _PreOrder(BinaryTreeNode<T> *root)
	{
		if(root == NULL){
			return;
		}
		cout<<root->data<<" ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}
	void _InOrder(BinaryTreeNode<T> *root)
	{
		if(root == NULL){
			return;
		}
		_InOrder(root->_left);
		cout<<root->data<<" ";
		_InOrder(root->_right);
	}
	void _PostOrder(BinaryTreeNode<T> *root)
	{
		if(root == NULL){
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->data<<" ";
	}
	void _LevelOrder(BinaryTreeNode<T> *root)
	{
		if(root == NULL){
			cout<<"NULL";
			return;
		}
		queue<BinaryTreeNode<T> *> s;
		s.push(root);
		while(!s.empty()){
			BinaryTreeNode<T> *tmp = s.front();
			cout<<tmp->data<<" ";
			s.pop();
			if(tmp->_left != NULL){
				s.push(tmp->_left);
			}
			if(tmp->_right != NULL){
				s.push(tmp->_right);
			}
		}
	}
	/*size_t _Size(BinaryTreeNode<T> *root)
	{
		if(root == NULL){
			return 0;
		}
		return _Size(root->_left) + 1 + _Size(root->_right);
	}*/

	//有线程安全的问题？？？----->多线程访问一个size----->这样写不好
	//size_t _Size(BinaryTreeNode<T> *root)  //遍历树，遇到一个结点就加一
	//{
	//	static size_t size = 0;
	//	if(root == NULL){
	//		return 0;
	//	}else{
	//		++size;
	//	}
	//	_Size(root->_left);
	//	_Size(root->_right);
	//	return size;
	//}
	void _Size(BinaryTreeNode<T> *root,size_t & size)  //解决方案
	{
		if(root == NULL){
			return;
		}else{
			++size;
		}
		_Size(root->_left,size);
		_Size(root->_right,size);
	}

	size_t _Depth(BinaryTreeNode<T> *root)
	{
		/*size_t depth_l = 0;
		size_t depth_r = 0;

		if(root == NULL)
			return 0;
		depth_l = _Depth(root->_left) + 1;
		depth_r = _Depth(root->_right) + 1;

		return depth_l > depth_r ? depth_l : depth_r;	*/

		if(root == NULL)
			return 0;
		size_t depth_l = _Depth(root->_left);
		size_t depth_r = _Depth(root->_right);

		return depth_l > depth_r ? depth_l+1 : depth_r+1;	

	}
	BinaryTreeNode<T> *_copy(BinaryTreeNode<T> * B_root)
	{
		BinaryTreeNode<T> *root = NULL;
		if(B_root != NULL){
			root = new BinaryTreeNode<T>(B_root->data);
			root->_left = _copy(B_root->_left);
			root->_right = _copy(B_root->_right);
		}
		return root;
	}
	void _Destroy(BinaryTreeNode<T> * &root)
	{
		if(root == NULL){
			return;
		}                               
		if(root->_left == NULL && root->_right == NULL){    //!!!
			delete root;
			root = NULL;
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}                   
	BinaryTreeNode<T> *_Find(BinaryTreeNode<T> *root,const T &x)
	{
		if(root == NULL){
			return NULL;
		}else if(root->data == x){
			return root;
		}else{
			BinaryTreeNode<T> *ret = _Find(root->_left,x);
			if(ret)
				return ret;
			else
				return _Find(root->_right,x);
		}
	}
public:
	BinaryTree(const char *a,size_t size)  //用先根遍历的方法创建数组
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a,size,index);
	}
	void PreOrder()
	{
		_PreOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout<<endl;
	}
	/*size_t Size()
	{
		return _Size(_root);
	}*/
	size_t Size()   //解决线程安全问题
	{
		size_t size = 0;
		_Size(_root,size);
		return size;
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	BinaryTree(const BinaryTree & B) 
	{
		_root = _copy(B._root);
	}
	~BinaryTree()
	{
		_Destroy(_root);
	}
	BinaryTree<T> &operator = (const BinaryTree &B)
	{
		if(this != &B)
		{
			this->_Destroy(_root);
			_root = _copy(B._root);
		}
		return *this;
	}
	BinaryTreeNode<T> *Find(const T &x)
	{
		return _Find(_root,x);
	} 
	void PreOrder_NonR()
	{
		stack<BinaryTreeNode<T> *> s;
		if(_root == NULL){
			return;
		}
		s.push(_root);
		while(!s.empty()){
			BinaryTreeNode<T> *top =s.top();
			s.pop();
			cout<<top->data<<" ";
			if(top->_right != NULL)
				s.push(top->_right);
			if(top->_left != NULL)
				s.push(top->_left);
		}
		cout<<endl;
	}
	void InOrder_NonR()
	{
		stack<BinaryTreeNode<T> *> s;
		BinaryTreeNode<T> *cur = _root;
		if(_root == NULL){
			return;
		}
		while(cur || !s.empty()){
			while(cur){
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode<T> *top = s.top();
			cout<<top->data<<" ";
			s.pop();
		    cur = top->_right;
		}
		cout<<endl;
	}
	void PostOrder_NonR()
	{
		stack<BinaryTreeNode<T> *> s;
		BinaryTreeNode<T> *cur = _root;
		BinaryTreeNode<T> *PreVisited = NULL;
		if(_root == NULL){
			return;
		}
		while(cur || !s.empty()){
			while(cur){
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode<T> *top = s.top();
			if(top->_right == NULL || top->_right == PreVisited){
				cout<<top->data<<" ";
				s.pop();
				PreVisited = top;
			}else{
		        cur = top->_right;
			}
		}
	}
};

void test()
{
	char a[11] = "123##4##56";
	BinaryTree <char> B(a,10);
	/*B.PreOrder();
	B.InOrder();
	B.PostOrder();
	B.LevelOrder();*/
	//cout<<B.Size()<<endl;
	//cout<<B.Depth()<<endl;
	//BinaryTree <char> B1(B);
	//B1.PreOrder();
	//B1 = B;
	//B1.PreOrder();
	cout<<B.Find('3')->data<<endl;
}

void test1()
{
	char a[11] = "123##4##56";
	BinaryTree <char> B(a,10);
	B.PreOrder_NonR();
	B.InOrder_NonR();
	B.PostOrder_NonR();
}
int main()
{
	test();
	//test1();
	system("pause");
	return 0;
}