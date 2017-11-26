#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stack>

typedef struct BinNode
{
    int data;
	struct BinNode *lchild, *rchild;
}BinNode, *BinTree;

#endif
