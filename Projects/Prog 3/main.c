#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "headerboiz.h"


int main(int argc, char** argv)  //we are taking in two arguments after indexer
{
	char* spath; //file path from where the file/dir will be taken from
	char* wpath; //path to be written on

	if(argc < 3)		//if less than 2 arguments, then invalid input and exit
	{
		fprintf(stderr, "incorrect number of arguments\n");
		return 1;
	}

	wpath = argv[1]; //path to be written on
	spath = argv[2]; //file path from where the file/dir will be taken from

	int wordcount = 0;
	int filecount = 0;
	int maxlen = 0;
	root = buildNode('$',-1,-1); //$ wont matter as it' a different sybol

	if(dircheck(spath)) //in case of directory
	{
		fileRoot = buildFileNode("$"); //declare and initialize file linked list root
		fileTemp = fileRoot;
		directcall(spath);
		addFileLL();
		writeCounts(wpath);
	}

	else //in case of file
	{
		filecount++;
		filecall(spath,0); //filecount passed as one and file index passed as 0 since there is only one file
		writeCounts(wpath);
		
	}

	deleteTree(root);

	return 0;
}