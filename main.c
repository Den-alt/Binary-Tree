#include <stdio.h>
#include "Headers/inform.h"

int main()
{
    NODE *root = NULL;                      //!Pointer to the root of the tree
    NODE *pNode = NULL;                     //!Temporary pointer for creating new node
    if(OpenFile() != 0)
    {
        printf("Program failed...\n");
        return -1;
    }
    while ( (pNode = CreateNewNode()) != NULL)                   //!Create node and add it to the tree
        AddNode(pNode, &root);
    CloseFile();                                                //!Close stream
    printf("Formed tree\nFrom left to right\n");
    PrintTree(root);
    printf("Average value of numbers in tree = %.2lf\n", CalcAverage(root));
    printf("Level:\t");
    for (int i = 1, size = TreeHeight(root); i <= size; ++i)            //!Print levels of the tree
        printf("%-10d", i);
    printf("\n");
    ShowTree(root, 1);                                                  //!Show data in tree form
    DeleteTree(root);
    return 0;
}
