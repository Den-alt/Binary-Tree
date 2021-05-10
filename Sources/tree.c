#include <stdio.h>
#include <stdlib.h>
#include "../Headers/inform.h"

//!Create new node for tree and set data
//!Return: address in dynamic memory of the node
NODE * CreateNewNode(void)
{
    NODE * temp;
    double number;
    if( (number = ReadDataFromFile() ) <= 0)             //!Get number from file
        return NULL;
    temp = (NODE*) malloc(sizeof (NODE));               //!Allocate memory for new node
    temp->info.number = number;                         //!Set data in tree
    temp->left= temp->right = NULL;                     //!New node becomes a leaf
    return temp;
}

//!Add new node to the tree
//!Parameters: the node to add to the tree and the address of the node to add to
void AddNode(NODE * new, NODE **root)
{
    NODE * p_root = *root;                                  //!Pointer to the root
    if(p_root == NULL)
    {
        *root = new;                    //!Set new node as a root
        return;
    }
    if(p_root->info.number == new->info.number)             //!If new node has already existing - delete one
        FreeNodeMemory(new);
    else if (p_root->info.number > new->info.number)        //!If new value is less than current set in left
        AddNode(new, &p_root->left);
    else AddNode(new, &p_root->right);                      //!If new value is more than current set in right
}

//!Print tree (from left to right)
//!Parameters: pointer to node
void PrintTree(NODE* pRoot)
{
    if(pRoot == NULL)
        return;
    PrintTree(pRoot->left);
    printf("%.1lf\n", pRoot->info.number);
    PrintTree(pRoot->right);
}

//!Calc height of the tree
//!Parameters: pointer to root of the tree
//!Return: height of the tree
int TreeHeight(NODE* pRoot)
{
    int leftHeight = 0, rightHeight = 0;            //!Compare height of the right and left subtrees
    if(pRoot == NULL)
        return 0;
    leftHeight = TreeHeight(pRoot->left);
    rightHeight = TreeHeight(pRoot->right);
    return rightHeight > leftHeight ? rightHeight+1 : leftHeight+1;
}

//!Show tree as a graph
//!Parameters: pointer to the tree
void ShowTree(NODE* pRoot, int level)
{
    if(pRoot == NULL)
        return;
    ShowTree(pRoot->left, level+1);
    for (int i = 1; i < level*9 ; ++i)
        printf(" ");
    printf("%.1lf\n", pRoot->info.number);
    ShowTree(pRoot->right, level+1);
}

//!Calc average sum of all numbers in tree
//!Parameters: pointer to root of the tree
//!Return: average number
double CalcAverage(NODE* pRoot)
{
    if(pRoot == NULL)
        return -1;
    NODE ** stack;                                                  //!Pointer to the start of the stack of the roots
    NODE* current = pRoot, *pNext;
    int kst = 0;
    double sum = 0;
    stack = (NODE**)calloc(TreeHeight(pRoot), sizeof(NODE*));                       //!Allocate memory for stack of the address
    if(stack == NULL)
    {
        printf("Not enough memory\n");
        return -1;
    }
    int i = 0;
    stack[i] = NULL;
    do {
        if(current->right != NULL)
        {
            pNext = current->right;                            //!Move on right branch
            if(current->left != NULL)
                stack[++i] = current->left;                    //!Save address of the subtree
        } else
        {
            if(current->left != NULL)
                pNext = current->left;                        //!Switch on left branch
            else
                pNext = stack[i--];
        }
        kst++;
        sum += current->info.number;
        current = pNext;                                      //!Switch on next branch
    } while (current != NULL);
    return sum/kst;
}

//!Delete tree from memory
//!Parameters: pointer to root
void DeleteTree(NODE* pRoot)
{
    if(pRoot == NULL)
        return;
    NODE ** stack;                                                  //!Pointer to the start of the stack of the roots
    NODE* toDelete = pRoot, *pNext;
    stack = (NODE**)calloc(TreeHeight(pRoot), sizeof(NODE*));                       //!Allocate memory for stack of the address
    if(stack == NULL)
    {
        printf("Not enough memory\n");
        return;
    }
    int i = 0;
    stack[i] = NULL;
    do {
        if(toDelete->right != NULL)
        {
            pNext = toDelete->right;                            //!Move on right branch
            if(toDelete->left != NULL)
                stack[++i] = toDelete->left;                    //!Save address of the subtree
        } else
        {
            if(toDelete->left != NULL)
                pNext = toDelete->left;                        //!Switch on left branch
            else
                pNext = stack[i--];
        }
        FreeNodeMemory(toDelete);                              //!Delete root element
        toDelete = pNext;                                      //!Switch on next branch
    } while (toDelete != NULL);
}

//!Delete selected node
//!Parameters: element to delete
void FreeNodeMemory(NODE* element)
{
    free(element);
}