#ifndef BINARY_TREE_INFORM_H
#define BINARY_TREE_INFORM_H

typedef struct s_TreeBody {
    double number;
}BODY;

typedef struct s_TreeNode{
    BODY info;
    struct s_TreeNode * left, * right;
}NODE;

//!file.c
int OpenFile(void);
double ReadDataFromFile(void);
void CloseFile(void);

//!tree.c
NODE * CreateNewNode(void);
void AddNode(NODE*, NODE**);
void PrintTree(NODE*);
int TreeHeight(NODE*);
void ShowTree(NODE*, int);
double CalcAverage(NODE*);
void DeleteTree(NODE*);
void FreeNodeMemory(NODE *element);

#endif //BINARY_TREE_INFORM_H
