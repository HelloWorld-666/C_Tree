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

// ����������
TreeNode* InitBinaryTree()
{
	char c;
	scanf_s("%c", &c);	// ��ʽ��������Ʒ�����'\n'��\n �ո���Ʊ�����ǿհ׷����հ��ַ���ʹscanf()�����ڶ���������ȥ�����е�һ�������հ��ַ���ֻ������һ���ǿհ׷���ʱ�������ֹscanf�����롣
	getchar();			// ѭ����������������ַ�,��ʱ������¼��һ�������ַ�,����ֹͣ����

	if (c == '?')
	{
		return NULL;
	}

	TreeNode* root = (TreeNode*)malloc(1*sizeof(TreeNode));
	root->data = c;
	root->left = InitBinaryTree();	// �ݹ鹹��������
	root->right = InitBinaryTree();	// �ݹ鹹��������
	
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

/**************************����ջ*****************************/
typedef struct StackNode
{
	TreeNode* treeNode; 
	int isFirst; 						// 1:��һ�η��ʽڵ� ; 2:�ڶ��η��ʽڵ�
	StackNode* next;
}StackNode;

typedef struct Stack
{
	StackNode* top;						// ջ��ָ��
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

//TreeNode* GetStackTopValue(Stack* s)	// ��ȡջ���ڵ��ڵ����ڵ�treeNode
//{
//	if (!IsStackEmpty(s))
//	{
//		return s->top->treeNode;
//	}
//}

StackNode* GetStackTopNode(Stack* s)	// ��ȡջ���ڵ�stackNode
{
	if (!IsStackEmpty(s))
	{
		return s->top;
	}
}

// ��ջ:��һ����ջ����ռ�
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
	//ptr_new->isFirst = isFirst;	// �����־λΪ2���������·���ռ䣬ֻ��Ҫ�ı��־λ��ֵ����.

	//ptr_new->next = s->top;
	//s->top = ptr_new;
}

//void PushStackOfLastPrint(Stack* s, TreeNode* root, int isFirst)
//{
//	if (isFirst == 1)
//	{
//		StackNode* ptr_new = (StackNode*)malloc(1 * sizeof(StackNode)); // ��һ�ν�ջmalloc
//		ptr_new->isFirst = 1;
//		ptr_new->treeNode = root;
//		ptr_new->next == NULL;
//		// ����������
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

// ��ջ:��һ�γ�ջ���ͷſռ�,�ڶ��γ�ջ�ͷ�
StackNode* PopStack(Stack* s)
{
	if (!IsStackEmpty(s))
	{
		StackNode* tmpNode = GetStackTopNode(s);	// �Ȼ�ȡջ���ڵ㣬���ƶ�topָ�룬����ָ��ʹ�ó���
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
		// ���������whileѭ���󣬴�ʱroot->left��ΪNULL����������root->right����
		if (!s.empty())
		{
			root = s.top(); // ֮ǰrootָ��left������ root=NULL����Ҫ��ջȡ��
			s.pop();
			root = root->right;
			//s.push(root);	// error����whileѭ���н���push����
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
			// ���ν� root->left ��ջ,ֱ��NULLΪֹ
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
			root = root->left;		// ѭ��������������ֱ��������ΪNULL
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
				root = root->right;	// ѭ��������������ֱ��������ΪNULL
			}
			else					// ��root����������������ΪNULLʱ�����������ջ
			{
				printf("%c\t", root->data);
				PopStack(&s);
				root = NULL;		// ֱ��root�ڵ��ΪҶ�ӽڵ㣬������������������ΪNULLʱ
			}
		}
	}

	//Stack st;
	//InitStack(&st);
	//while (root != NULL || !IsStackEmpty(&st))
	//{
	//	while (root != NULL)
	//	{
	//		PushStackOfLastPrint(&st, root, 1);	// ��һ����ջ��־λΪ1
	//		root = root->left;
	//	}

	//	if (!IsStackEmpty(&st))
	//	{
	//		// ��ȡջ��Ԫ��
	//		StackNode* StackTopNode = GetStackTopNode(&st);
	//		root = StackTopNode->treeNode;
	//		if (StackTopNode->isFirst == 1)
	//		{
	//			PopStack(&st); //�ȳ�ջ
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
// ���ÿ��·�����ݹ飺ʹ�õ�ǰ�½����Ϊ��һ�ε��õĴ��Σ�
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

// ���ÿ��·����
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

// ��������������
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

// ��֤����������
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

//// ������ȱ�������������queue�ṹ��ʵ�֣�
//void BFS(TreeNode* root)
//{
//	queue<TreeNode*> q;
//	q.push(root);
//	while (!q.empty())				// �����в�Ϊ��ʱ
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
    �ܽ᣺���н�㶼��������㣬�ؼ����ں�ʱ���ʡ�ǰ����ջʱ���ʣ����򣺵�һ����ջʱ���ʣ����򣺵ڶ�����ջʱ���ʡ�
	
	������ȱ���������ջstack�ṹ��ʵ�֣� = ǰ�к������
	dfs:һ��·�ߵ���,��ջʵ��,��ջ����ջ��һ�ѵ���!һ����<�ݹ�>ʵ��
	bfs: ����˷�,�ö�ʵ��,��ӡ����ӣ�����ΪӪ!һ����<����>ʵ��
	������ȣ�����<һ��·�ߵ���>��������ȣ�����<ÿ��·��ͬʱ������>��

	���⣺ɾ��һ�ö����������ͷ�һ�ö��������ڴ棬�ú�����������ʵ�֣�����ġ����ʡ������delete ��㣩.
*/

int main()
{
		
	TreeNode* root = InitBinaryTree();
	//printf("�ݹ�ǰ��/������ȱ�����");
	//PrePrint(root);
	//printf("\n");
	//printf("�ݹ�����");
	//MidPrint(root);
	//printf("\n");
	//printf("�ݹ����");
	//EndPrint(root);
	//printf("������ȱ�����");
	//BFS(root);
	//printf("\n");

	//printf("�ǵݹ�ǰ��/������ȱ�����");
	//BinaryPrePrintNoRecursion(root);
	//printf("\n");
	//printf("�ǵݹ�����");
	//BinaryMidPrintNoRecursion(root);
	//printf("\n");
	//printf("�ǵݹ����");
	//BinaryEndPrintNoRecursion(root);
	//printf("\n");

	printf("���ÿ��·����");
	string s = "";
	printPath(root, s);

	//printf("���ÿ��·���ͣ�");
	//int tmp = 0;
	//int sum = 0;
	//hasPathSum(root, tmp, sum);

	//printf("�������������ȣ�");
	//cout << maxDepth(root) << endl;

	printf("��֤������������");
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

�����������ݣ�

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

	ջ�ڵ� = ���ڵ� + IsFirst��־λ + ջ��nextָ��

*/



//#include  <stdio.h>
//#include  <stdlib.h>
///*
//��(tree):��һ�ַ����Խṹ,��n(n>=0)���ڵ���ɽṹ,�ṹ������ֻ�ܴ���һ���ڵ�Ϊ��,
//�����Ľڵ�Ϊ�ӽڵ�,n-1���ڵ�Ҳ��һ��������,��һ�ֵݹ鶨��
//���ŵ�:
//1.��߲�ѯЧ��
//�����õĸ���:
//���ڵ�:ֻ��ֱ�ӵ��������ڵ�,һ�������������.������ֻ�ܴ���һ�����ڵ�
//�ӽڵ�:���и��ڵ�Ҳ���ӽڵ�,һ�����������м��
//Ҷ�ӽڵ�:û���ӽڵ�,Ҳ��Ϊ�ն˽ڵ�,�������һ���ڵ�
//�����:�Ӹ��ڵ㵽���ն�Ҷ�ӽڵ�����·��ֵ
//�����:�ӽڵ�ӵ���ӽڵ�����ֵ
//������(binary tree):���Ϊ2����,���ڵ�ֻ�������������ӽڵ�
//3���ڵ������ɼ��ֶ�����:
//1.����
//2.�� ��  ��(����)
//3.�� �� ��
//4.�� �� ��
//5.�� �� ��
//6.�� �� ��(����)
//�������ص�:
//1.���Ϊn�Ķ�����,�ڵ��������:2^n-1
//2.���Ϊn�Ķ�����,���ն�Ҷ�ӽڵ��������:2(n-1)
//3.�������һ�ö�����,��Ϊ0�Ľڵ���Ϊn0,��Ϊ1�Ľڵ���Ϊn1,��Ϊ2�Ľڵ���Ϊn2
//n0 n1 n2֮�����������ϵ:n0=n2+1(�����ܽ����:n0+n1+n2=n0*0+n1*1+n2*2+1(���ڵ�))
//
//��������:�����ն�Ҷ�ӽڵ�֮���������нڵ��ȶ�Ϊ2,
//������ڵ���Ϊi,��ڵ���Ϊ2*i,�ҽڵ���Ϊ2*i+1
//��ȫ������:�����ն�Ҷ�ӽڵ�֮���������нڵ�֮�бض�����һ���ڵ�Ĺ��С��2,��ڵ��ű������Ӧ�����������һ��.(��������������)
//�������һ����n���ڵ������,��������ֵ��:n-1
//�������һ����n���ڵ���ȫ������,��������ֵ��:log2(n)+1
//����������:
//1.ǰ�����:�� ��  ��
//2.�������:�� �� ��
//3.�������:�� �� ��
//
//*/
////���ڵ㶨��:
//typedef  struct tree_node
//{
//	char  ch;
//	//struct tree_node *parent;//ָ����ڵ�
//	struct tree_node *right;//ָ���Һ���
//	struct tree_node *left;//ָ������
//}tree_node;
//
////ջ�ڵ㶨��
//typedef struct stack_node
//{
//	tree_node tree_node_value;
//	int  is_first;//1:��һ�η��ʽڵ�, 2:�ڶ��η��ʽڵ�
//	struct stack_node* next;
//}stack_node;
////ջ����
//typedef struct stack
//{
//	stack_node * top;
//}stack;
////��ʼ��ջ
//void   init_stack(stack* st)
//{
//	st->top = NULL;
//}
////��ջ
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
////�ж�ջ�Ƿ�Ϊ��
//int  is_stack_empty(stack* st)
//{
//	if (st->top == NULL)
//	{
//		return 1;
//	}
//	return 0;
//}
////��ջ
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
////��ȡջ��ֵ
//stack_node*  get_stack_top_value(stack * st)
//{
//	if (!is_stack_empty(st))
//	{
//		return  st->top;
//	}
//}
////������
//tree_node *  init_binary_tree()
//{
//	tree_node * root;
//	char ch_value;
//	scanf_s("%c", &ch_value);//ѭ����������������ַ�,��ʱ������¼��һ�������ַ�,����ֹͣ����
//	getchar();//��ջ���
//	if (ch_value == 'q')
//	{
//		return NULL;
//	}
//	root = (tree_node*)malloc(1 * sizeof(tree_node));
//	root->ch = ch_value;
//	root->left = init_binary_tree();//�ݹ鹹��������
//	root->right = init_binary_tree();//�ݹ鹹��������
//	return root;
//}
////�ݹ�������
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
////���������������������Ľڵ�(��ǰ�����)
////�������Ĺ�����������Ľڵ�
