#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

typedef struct TreeNode
{
	char data;
	TreeNode* left;
	TreeNode* right;
}TreeNode;

// 构建二叉树
TreeNode* InitBinaryTree()
{
	char c;
	scanf_s("%c", &c);	// 格式化输出控制符不加'\n'，\n 空格和制表符，是空白符。空白字符会使scanf()函数在读操作中略去输入中的一个或多个空白字符。只有输入一个非空白符的时候才能终止scanf的输入。
	getchar();			// 循环中连续多次输入字符,此时缓存会记录上一次输入字符,不再停止输入

	if (c == '?')
	{
		return NULL;
	}

	TreeNode* root = (TreeNode*)malloc(1*sizeof(TreeNode));
	root->data = c;
	root->left = InitBinaryTree();	// 递归构建左子树
	root->right = InitBinaryTree();	// 递归构建右子树
	
	return root;
}

void  PrePrint(TreeNode* root)
{
	if (root != NULL)
	{
		printf("%c", root->data);
		PrePrint(root->left);
		PrePrint(root->right);
	}
}

void  MidPrint(TreeNode* root)
{
	if (root != NULL)
	{
		MidPrint(root->left);
		printf("%c", root->data);
		MidPrint(root->right);
	}
}

void  EndPrint(TreeNode* root)
{
	if (root != NULL)
	{
		EndPrint(root->left);
		EndPrint(root->right);
		printf("%c", root->data);
	}
}

/**************************定义栈*****************************/
typedef struct StackNode
{
	TreeNode* treeNode; 
	int isFirst; 						// 1:第一次访问节点 ; 2:第二次访问节点
	StackNode* next;
}StackNode;

typedef struct Stack
{
	StackNode* top;						// 栈顶指针
}Stack;

void InitStack(Stack* s)
{
	s->top = NULL;
}

bool IsStackEmpty(Stack* s)
{
	if (s->top == NULL)
	{
		return true;
	}

	return  false;
}

//TreeNode* GetStackTopValue(Stack* s)	// 获取栈顶节点内的树节点treeNode
//{
//	if (!IsStackEmpty(s))
//	{
//		return s->top->treeNode;
//	}
//}

StackNode* GetStackTopNode(Stack* s)	// 获取栈顶节点stackNode
{
	if (!IsStackEmpty(s))
	{
		return s->top;
	}
}

// 入栈:第一次入栈分配空间
void PushStackOfLastPrint(Stack* s, TreeNode* root, int isFirst)
{
	StackNode* ptr_new = (StackNode*)malloc(1 * sizeof(StackNode));
	if (isFirst == 1)
	{
		ptr_new->treeNode = root;
		ptr_new->next = NULL;
	}
	else
	{
		ptr_new->isFirst = isFirst;
	}

	ptr_new->next = s->top;
	s->top = ptr_new;

	//StackNode* ptr_new = (StackNode*)malloc(1 * sizeof(StackNode));
	//if (isFirst == 1)
	//{
	//	StackNode* ptr_new = (StackNode*)malloc(1 * sizeof(StackNode));
	//	ptr_new->treeNode = root;
	//	ptr_new->next = NULL;
	//}
	//
	//ptr_new->isFirst = isFirst;	// 如果标志位为2，则不用重新分配空间，只需要改变标志位的值即可.

	//ptr_new->next = s->top;
	//s->top = ptr_new;
}

//void PushStackOfLastPrint(Stack* s, TreeNode* root, int isFirst)
//{
//	if (isFirst == 1)
//	{
//		StackNode* ptr_new = (StackNode*)malloc(1 * sizeof(StackNode)); // 第一次进栈malloc
//		ptr_new->isFirst = 1;
//		ptr_new->treeNode = root;
//		ptr_new->next == NULL;
//		// 加入链表中
//		ptr_new->next = s->top;
//		s->top = ptr_new;
//	}
//	else if (isFirst == 2)
//	{
//		StackNode* ptr_temp =  s->top;
//		//ptr_temp->isFirst = 2;
//		ptr_temp->next = s->top;
//		s->top = ptr_temp;
//	}
//}

// 出栈:第一次出栈不释放空间,第二次出栈释放
StackNode* PopStack(Stack* s)
{
	if (!IsStackEmpty(s))
	{
		StackNode* tmpNode = GetStackTopNode(s);	// 先获取栈顶节点，再移动top指针，否则指针使用出错
		s->top = s->top->next;
		if (tmpNode->isFirst == 2)
		{
			free(tmpNode);
			tmpNode = NULL;
		}
		
		return tmpNode;
	}
}

void BinaryPrePrintNoRecursion(TreeNode* root)
{
	stack<TreeNode*> s;
	
	while (root != NULL || !s.empty())
	{
		while (root != NULL)
		{
			printf("%c", root->data);
			s.push(root);
			root = root->left;
		}
		// 经过上面的while循环后，此时root->left已为NULL，接下来对root->right操作
		if (!s.empty())
		{
			root = s.top(); // 之前root指向left，所以 root=NULL，需要从栈取出
			s.pop();
			root = root->right;
			//s.push(root);	// error：在while循环中进行push操作
		}
	}
}

void BinaryMidPrintRecursion(TreeNode* root)
{
	stack<TreeNode*> s;

	while (root != NULL || !s.empty())
	{
		while (root != NULL)
		{
			// 依次将 root->left 入栈,直到NULL为止
			s.push(root);
			root = root->left;
		}

		if (!s.empty())
		{
			root = s.top();
			printf("%c", root->data);
			s.pop();
			root = root->right;
		}
	}
}

bool isValidBST1(TreeNode* root)
{
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		//cout << root->data << endl;
		q.pop();
		if (root->data < root->left->data || root->data > root->right->data)
		{
			return false;
		}
		if (root->left != NULL)
			q.push(root->left);
		if (root->right != NULL)
			q.push(root->right);
	}	
	return true;
}

void BFS(TreeNode* root)
{
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		printf("%c", root->data);
		q.pop();

		if (root->left != NULL)
		{
			q.push(root->left);
		}
		if (root->right != NULL)
		{
			q.push(root->right);
		}
	}
}

void BinaryEndPrintNoRecursion(TreeNode* root)
{
	Stack s;
	InitStack(&s);
	while (root != NULL || !IsStackEmpty(&s))
	{
		while (root != NULL)
		{
			PushStackOfLastPrint(&s, root, 1);
			root = root->left;		// 循环遍历左子树，直到左子树为NULL
		}

		if (!IsStackEmpty(&s))
		{
			StackNode* st_node = GetStackTopNode(&s);
			//printf("%c\t",root->ch);
			root = (st_node->treeNode);
			if (st_node->isFirst == 1)
			{
				StackNode* tmpNode = PopStack(&s);
				st_node->isFirst = 2;
				PushStackOfLastPrint(&s, root, 2);
				root = root->right;	// 循环遍历右子树，直到右子树为NULL
			}
			else					// 若root左子树和右子树都为NULL时，则输出并出栈
			{
				printf("%c\t", root->data);
				PopStack(&s);
				root = NULL;		// 直到root节点变为叶子节点，其左子树和右子树都为NULL时
			}
		}
	}

	//Stack st;
	//InitStack(&st);
	//while (root != NULL || !IsStackEmpty(&st))
	//{
	//	while (root != NULL)
	//	{
	//		PushStackOfLastPrint(&st, root, 1);	// 第一次入栈标志位为1
	//		root = root->left;
	//	}

	//	if (!IsStackEmpty(&st))
	//	{
	//		// 获取栈顶元素
	//		StackNode* StackTopNode = GetStackTopNode(&st);
	//		root = StackTopNode->treeNode;
	//		if (StackTopNode->isFirst == 1)
	//		{
	//			PopStack(&st); //先出栈
	//			PushStackOfLastPrint(&st, root, 2);
	//			root = root->right;
	//		}
	//		else
	//		{
	//			printf("%c\t", root->data);
	//			PopStack(&st);
	//			root = NULL;
	//		}
	//	}
	//	
	//}
}

/*******************************************************************************/
// 输出每条路径（递归：使用当前新结果作为下一次调用的传参）
void printPath(TreeNode* root, string s)
{
	if (root != NULL)
	{
		s += root->data;
		if (root->left == NULL && root->right == NULL)
		{
			cout << s << endl;
		}
		printPath(root->left, s);
		printPath(root->right, s);
	}
}

// 输出每条路径和
bool hasPathSum(TreeNode* root, int tmp, int sum)
{
	if (root == NULL)
		return 0;
	/*if (root != NULL)
	{*/
	tmp += root->data;
	if (root->left == NULL && root->right == NULL)
	{
		sum += tmp;
		cout << "sum = " << sum << endl;
	}
	hasPathSum(root->left, tmp, sum);
	hasPathSum(root->right, tmp, sum);
	//}
}

// 二叉树的最大深度
int maxDepth(TreeNode* root)
{
	if (root == NULL)
		return 0;
	/*if (root != NULL)
	{*/
	int l = maxDepth(root->left)  + 1;
	int r = maxDepth(root->right) + 1;
	return l > r ? l : r;
	//}
}

// 验证二叉搜索树
bool isValidBST(TreeNode* root)
{
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		//cout << root->data << endl;
		if (root->data < root->left->data || root->data > root->right->data)
		{
			return false;
		}
		q.pop();
		if (root->left != NULL)
			q.push(root->left);
		if (root->right != NULL)
			q.push(root->right);
	}
	return true;
}

//// 广度优先遍历（借助队列queue结构来实现）
//void BFS(TreeNode* root)
//{
//	queue<TreeNode*> q;
//	q.push(root);
//	while (!q.empty())				// 当队列不为空时
//	{
//		root = q.front();			// Gets the head element of the queue
//		q.pop();
//		printf("%c", root->data);
//		if (root->left != NULL)
//		{
//			q.push(root->left);
//		}
//		if (root->right != NULL)
//		{
//			q.push(root->right);
//		}
	//	}
	//}

/*
    总结：所有结点都看作根结点，关键在于何时访问。前序：入栈时访问；中序：第一次退栈时访问；后序：第二次退栈时访问。
	
	深度优先遍历（借助栈stack结构来实现） = 前中后序遍历
	dfs:一条路走的死,用栈实现,进栈、退栈，一搜到底!一般用<递归>实现
	bfs: 辐射八方,用队实现,入队、出队，步步为营!一般用<迭代>实现
	深度优先，就是<一条路走到底>，广度优先，就是<每条路都同时派人走>。

	另外：删除一棵二叉树，即释放一棵二叉树的内存，用后续遍历即可实现（这里的“访问”变成了delete 结点）.
*/

int main()
{
		
	TreeNode* root = InitBinaryTree();
	//printf("递归前序/深度优先遍历：");
	//PrePrint(root);
	//printf("\n");
	//printf("递归中序：");
	//MidPrint(root);
	//printf("\n");
	//printf("递归后序：");
	//EndPrint(root);
	//printf("广度优先遍历：");
	//BFS(root);
	//printf("\n");

	//printf("非递归前序/深度优先遍历：");
	//BinaryPrePrintNoRecursion(root);
	//printf("\n");
	//printf("非递归中序：");
	//BinaryMidPrintNoRecursion(root);
	//printf("\n");
	//printf("非递归后序：");
	//BinaryEndPrintNoRecursion(root);
	//printf("\n");

	printf("输出每条路径：");
	string s = "";
	printPath(root, s);

	//printf("输出每条路径和：");
	//int tmp = 0;
	//int sum = 0;
	//hasPathSum(root, tmp, sum);

	//printf("二叉树的最大深度：");
	//cout << maxDepth(root) << endl;

	printf("验证二叉搜索树：");
	cout << isValidBST(root) << endl;

	getchar();

	return 0;
}

/*
	 a
	/ \
   b   c
  / \
 d   e

测试输入数据：

a
b
d
?
?
e
?
?
c
?
?

	栈节点 = 树节点 + IsFirst标志位 + 栈的next指针

*/



//#include  <stdio.h>
//#include  <stdlib.h>
///*
//树(tree):是一种非线性结构,由n(n>=0)个节点组成结构,结构中有且只能存在一个节点为根,
//其它的节点为子节点,n-1个节点也是一个棵子树,是一种递归定义
//树优点:
//1.提高查询效率
//树常用的概念:
//根节点:只有直接点无树父节点,一般是在树的最顶层.树有且只能存在一个根节点
//子节点:既有父节点也有子节点,一般树在树的中间层
//叶子节点:没有子节点,也称为终端节点,树的最后一个节点
//树深度:从根节点到达终端叶子节点的最大路径值
//树广度:子节点拥有子节点的最大值
//二叉树(binary tree):广度为2的树,树节点只能有左右两个子节点
//3个节点可以组成几种二叉树:
//1.空树
//2.根 左  右(二层)
//3.根 左 左
//4.跟 右 右
//5.根 右 左
//6.根 左 右(三层)
//二叉树特点:
//1.深度为n的二叉树,节点数最多是:2^n-1
//2.深度为n的二叉树,其终端叶子节点数最多是:2(n-1)
//3.如果存在一棵二叉树,度为0的节点树为n0,度为1的节点树为n1,度为2的节点树为n2
//n0 n1 n2之间存在怎样关系:n0=n2+1(根据总结点树:n0+n1+n2=n0*0+n1*1+n2*2+1(根节点))
//
//满二叉树:除开终端叶子节点之外其它所有节点广度都为2,
//如果根节点编号为i,左节点编号为2*i,右节点编号为2*i+1
//完全二叉树:除开终端叶子节点之外其它所有节点之中必定存在一个节点的广度小于2,其节点编号必须与对应满二叉树编号一致.(必须是现有左孩子)
//如果存在一个有n个节点二叉树,其深度最大值是:n-1
//如果存在一个有n个节点完全二叉树,其深度最大值是:log2(n)+1
//遍历二叉树:
//1.前序遍历:根 左  右
//2.中序遍历:左 根 右
//3.后序遍历:左 右 根
//
//*/
////树节点定义:
//typedef  struct tree_node
//{
//	char  ch;
//	//struct tree_node *parent;//指向根节点
//	struct tree_node *right;//指向右孩子
//	struct tree_node *left;//指向左孩子
//}tree_node;
//
////栈节点定义
//typedef struct stack_node
//{
//	tree_node tree_node_value;
//	int  is_first;//1:第一次访问节点, 2:第二次访问节点
//	struct stack_node* next;
//}stack_node;
////栈定义
//typedef struct stack
//{
//	stack_node * top;
//}stack;
////初始化栈
//void   init_stack(stack* st)
//{
//	st->top = NULL;
//}
////入栈
//void   push_stack(stack *st, tree_node * ptr_root, int  is_first)
//{
//	if (is_first == 1)
//	{
//		stack_node * ptr_new = (stack_node*)malloc(1 * sizeof(stack_node));
//		ptr_new->tree_node_value = *ptr_root;
//		ptr_new->next = NULL;
//		ptr_new->is_first = is_first;
//		ptr_new->next = st->top;
//		st->top = ptr_new;
//	}
//}
////判断栈是否为空
//int  is_stack_empty(stack* st)
//{
//	if (st->top == NULL)
//	{
//		return 1;
//	}
//	return 0;
//}
////出栈
//void  pop_stack(stack* st)
//{
//	if (!is_stack_empty(st))
//	{
//		stack_node * ptr_cur = st->top;
//		st->top = st->top->next;
//		if (ptr_cur->is_first == 2)
//		{
//			free(ptr_cur);
//			ptr_cur = NULL;
//		}
//	}
//}
////获取栈顶值
//stack_node*  get_stack_top_value(stack * st)
//{
//	if (!is_stack_empty(st))
//	{
//		return  st->top;
//	}
//}
////构建树
//tree_node *  init_binary_tree()
//{
//	tree_node * root;
//	char ch_value;
//	scanf_s("%c", &ch_value);//循环中连续多次输入字符,此时缓存会记录上一次输入字符,不再停止输入
//	getchar();//清空缓存
//	if (ch_value == 'q')
//	{
//		return NULL;
//	}
//	root = (tree_node*)malloc(1 * sizeof(tree_node));
//	root->ch = ch_value;
//	root->left = init_binary_tree();//递归构建左子树
//	root->right = init_binary_tree();//递归构建右子树
//	return root;
//}
////递归后序遍历
//void  binary_last_print(tree_node* root)
//{
//	if (root != NULL)
//	{
//		binary_last_print(root->left);
//		binary_last_print(root->right);
//		printf("%c\t", root->ch);
//	}
//}
//
////
//void  binary_last_print_new(tree_node * root)
//{
//	stack st;
//	init_stack(&st);
//	while (root != NULL || !is_stack_empty(&st))
//	{
//		while (root != NULL)
//		{
//			push_stack(&st, root, 1);
//			root = root->left;
//		}
//
//		if (!is_stack_empty(&st))
//		{
//			stack_node* st_node = get_stack_top_value(&st);
//			//printf("%c\t",root->ch);
//			root = &(st_node->tree_node_value);
//			if (st_node->is_first == 1)
//			{
//				pop_stack(&st);
//				push_stack(&st, root, 2);
//				st_node->is_first = 2;
//				root = root->right;
//			}
//			else
//			{
//				printf("%c\t", root->ch);
//				pop_stack(&st);
//				root = NULL;
//			}
//		}
//	}
//}
//
//int  main(int argc, const char * argv[])
//{
//	tree_node * root = init_binary_tree();
//	binary_last_print(root);
//	printf("\n");
//	binary_last_print_new(root);
//	printf("\n");
//	return 0;
//}
////按照树的深度优先输出树的节点(树前序遍历)
////按照树的广度优先输出输的节点
