/*
Lakshay Anand
LA436231
001269497
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct_def.h"
#include "headerboiz.h"
//This is th main fucntion || mainboiz
int main(int argc, char *argv[])  //bintree + 2 arguments infile and outfile
{
	FILE *infile, *outfile; //file pointers for input and output
	int strCount; //stores string count
	int leaf_count; //stores leaf count
	int height; //total heiht of the tree
	int lHeight; //height - left side
	int rHeight; //height - right side
	int left_strings; //no of strings on the left tree
	int right_strings; //no of strings on the right tree
	char string[MAXLEN]; //will store string with max length of 20
	tree_node *node; //node pointer for the tree
	node = NULL; //initializes tree as null

	if(argc != 3) //if arguments are not equal to 3, exit
	{
		fprintf(stderr, "Invalid no. of arguments.\n");
		exit(1);
	}
	
	if((infile = fopen(argv[1], "rwx"))==NULL)
	{
		fprintf(stderr, "Could not open the input file");
		exit(1);
	}
	
	if((outfile = fopen(argv[2], "rwx"))==NULL)
	{
		fprintf(stderr, "Could not open the output file");
		exit(1);
	}
	
	if( infile != NULL ) //input file isn't null
	{
	    while ( !feof(infile)) //till it reaches end of file it loops
	    {
			fscanf (infile, "%s", string); //stores the current string into a variable in every loop
			node = insert(node, string); //calls insert function to insert string
	    } 
	}
	//calling all the functions and assigning the values in different variables
	strCount=countNodes(node); 
	leaf_count = countleaves(node);
	left_strings = countLeft(node);
	right_strings = countRight(node);
	lHeight = leftHeight(node);
	rHeight = rightHeight(node);
	height = treeHeight(node); 

	fprintf(outfile, "No. of strings in the input file are %d\n", strCount); //Prints the stringCount into the output file
	fprintf(outfile, "No. of strings on the left side are %d\n", left_strings); //Prints the left_strings into the output file
	fprintf(outfile, "No. of strings on the right side are  %d\n", right_strings); //Prints the right_strings into the output file/
	fprintf(outfile, "No. of leaves in the tree are %d\n", leaf_count);//Prints the leaf_count into the output file
	fprintf(outfile, "Total height of the tree is %d\n", height); //Prints the height_count into the output file
	fprintf(outfile, "Height of the left side of the tree is %d\n", lHeight); //Prints the leftHeight_count into the output file
	fprintf(outfile, "Height of the right side of the tree is %d\n", rHeight); //Prints the rightHeight into the output file
	
	if (fclose(infile)==EOF)
	{
		fprintf(stderr, "-----------Could not close the input file-----------");
		exit(1);
	}

	if (fclose(outfile)==EOF)
	{
		fprintf(stderr, "-----------Couldn't close the output file-------------"); 
		exit(1);
	}
		
	return 0;
}
