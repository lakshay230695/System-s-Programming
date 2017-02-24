/*
Lakshay Anand
LA436231
001269497
*/
//variables

#define MAXLEN 15 //maximum lenght of a string in 1 line i.e. per line
#define NULL_TREE_HEIGHT -1 //if it's a null tree, assigns -1 so it returns -1

//function definitions 
int countNodes(tree_node *tree);
int countLeft(tree_node *tree);
int countRight(tree_node *tree);
int countleaves(tree_node *tree);
int treeHeight(tree_node *tree);
int leftHeight(tree_node *tree);
int rightHeight(tree_node *tree);
struct tree_node *insert(tree_node *t_node, char[]);