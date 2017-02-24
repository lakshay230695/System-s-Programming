
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct_def.h"
#include "headerboiz.h"

tree_node *insert(tree_node *t_node, char str[])
{
	if(t_node==NULL) //if the tree is empty
    {
		tree_node *new_node = malloc( sizeof(struct tree_node)); //memory allocation for the tree
		strcpy(new_node->string, str); //puts the first word in string as the root
		new_node->left_child = new_node->right_child = NULL; //assigns null value to left and right trees
		return new_node; //Returns the tree.
    }
    else
    {
        if(strcmp(str, t_node->string)<0) //the string comes before the cuurent one
        {
            t_node->left_child=insert(t_node->left_child, str); //inserts in left tree
        }
        else if(strcmp(str, t_node->string)>0) //the string comes after the current one
        {
            t_node->right_child=insert(t_node->right_child, str); //inserts in right tree
        }
    }	
	return t_node;
}

int countLeft(tree_node *tree)	//counts the strings on left subtree
{
	if (tree==NULL) //If the tree is empty, returns 0 because there are no nodes in the left subtree
		return 0;
	else
	{
		if (tree->left_child==NULL) //If the left subtree is null, then also returns 0
			return 0;
		else
			return countNodes(tree->left_child); //Calls on the count function which computes the # recursively. 
	}
}

int countRight(tree_node *tree) //function to count nodes in right side of the tree
{
	if (tree==NULL) //if tree is empty
		return 0;
	else
	{
		if (tree->right_child==NULL) //If the right subtree is null, then also returns 0
			return 0;
		else
			return countNodes(tree->right_child); //Calls on the count function which computes the # recursively. 
	}
}

int countleaves(tree_node *tree) //function to count leaves
{
	if(tree == NULL) //If the tree is empty, there are no leaves in the tree so returns 0;
		return 0;
	if (tree->left_child == NULL && tree->right_child==NULL)
		return 1;
	else
		return countleaves(tree->left_child) + countleaves(tree->right_child); //Recursively computes the leaves of each subtree, then adds them together to return results.
}

int countNodes(tree_node *tree)  //fucntion to count nodes
{
	if (tree==NULL) //If the tree has no nodes, returns 0
		return 0;
	else 
	{
		if (tree->left_child == NULL && tree->right_child ==NULL) //returns 1 only for the root 
			return 1;
		else
			return (1 + (countNodes(tree->left_child)) + countNodes(tree->right_child)); //root + right tree + left tree
	}
}

int treeHeight(tree_node *tree)      //calculates the height of the tree
{	
	if (tree == NULL) //if the tree is empty
		return NULL_TREE_HEIGHT; //return -1
	else
	{
		int right_height = treeHeight(tree->right_child); 
		int left_height = treeHeight(tree->left_child); 
		if(left_height > right_height)
			return left_height+1; //if left side is large, adds 1 and returns
		else 
			return right_height+1; //if right side is large, adds 1 and returns
	}
}

int leftHeight(tree_node *tree) //computes the left height of the tree
{
	int left_height = treeHeight(tree->left_child); //stores the left node height of the tree in left_height variable
	if(left_height == NULL_TREE_HEIGHT) //null_tree_height = -1
		return 0;
	else
		return left_height;
}

int rightHeight(tree_node *tree) //computes the right hright of the tree
{
	int right_height = treeHeight(tree->right_child); //stores the right node height of the tree in right_height variable
	if(right_height == NULL_TREE_HEIGHT) //null_tree_height = -1
		return 0;
	else
		return right_height; 
}
