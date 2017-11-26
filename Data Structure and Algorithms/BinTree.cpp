#include "../pub.h"

#include "BinTree.h"

using namespace std;

int PreOrder_Recursive(BinTree root)
{
    if(root == NULL)
		return OK;

	printf("%d ",root->data);
	PreOrder_Recursive(root->lchild);
	PreOrder_Recursive(root->rchild);
}

int InOrder_Recursive(BinTree root)
{
    if(root == NULL)
		return OK;
	
	PreOrder_Recursive(root->lchild);
	printf("%d ",root->data);
	PreOrder_Recursive(root->rchild);
}

int PostOrder_Recursive(BinTree root)
{
    if(root == NULL)
		return OK;
	
	PreOrder_Recursive(root->lchild);
	PreOrder_Recursive(root->rchild);
	printf("%d ",root->data);
}

int PreOrder_NonRecursive(BinTree root)
{
    stack<BinNode*> stackBinNode;
	BinNode        *pstBinNode;
    if(root == NULL)
		return OK;
	
	stackBinNode.push(root);
	while(!stackBinNode.empty())
	{
#if 1
        pstBinNode = stackBinNode.top();
		stackBinNode.pop();
		printf("%d ", pstBinNode->data);
		if (pstBinNode->rchild != NULL)
			stackBinNode.push(pstBinNode->rchild);
		if (pstBinNode->lchild != NULL)
			stackBinNode.push(pstBinNode->lchild);
#endif		
#if 0
		if (pstBinNode != NULL )
		{
			printf("%d ", pstBinNode->data);
			stackBinNode.push(pstBinNode);
			pstBinNode = pstBinNode->lchild;
		}
		else
		{	
			pstBinNode = stackBinNode.top();
			stackBinNode.pop();
			pstBinNode = pstBinNode->rchild;
		}
#endif
	}
}


int PostOrder_NonRecursive(BinTree root)
{
	stack<BinNode*> stackBinNode;
	BinNode        *pstBinNode = root;
	if (root == NULL)
		return 0;

	while (pstBinNode != NULL || !stackBinNode.empty())
	{
		if (pstBinNode != NULL)
		{
			stackBinNode.push(pstBinNode);
			pstBinNode = pstBinNode->lchild;
			
		}
		else
		{
		    pstBinNode = stackBinNode.top();
			if (pstBinNode->flag == 1 ||
				pstBinNode->rchild == NULL)
			{
				printf("%d ", pstBinNode->data);
				pstBinNode = NULL;
			}
			stackBinNode.pop();
			if (pstBinNode != NULL && pstBinNode->rchild != NULL)
			{
				pstBinNode->flag = 1;
				stackBinNode.push(pstBinNode);
			}
			if(pstBinNode != NULL )
			pstBinNode = pstBinNode->rchild;
		}
	}
}


int main(int argc, char* argv[])
{
	BinNode *root = new BinNode;
	BinNode *A, *B, *C, *D, *E;
	A = new BinNode;
	B = new BinNode;
	C = new BinNode;
	D = new BinNode;
	E = new BinNode;
	A->data = 5;
	B->data = 6;
	C->data = 4;
	D->data = 2;
	E->data = 7;

	root = A;
	A->lchild = B;
	A->rchild = E;
	B->lchild = C;
	B->rchild = D;
	C->lchild = NULL;
	C->rchild = NULL;
	D->lchild = NULL;
	D->rchild = NULL;
	E->lchild = NULL;
	E->rchild = NULL;

	PreOrder_NonRecursive(A);

	return 0;
}

