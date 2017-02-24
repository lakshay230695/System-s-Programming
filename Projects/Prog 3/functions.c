/* 
Lakshay Anand 
LA436231
001269497
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "headerboiz.h"
int dircheck(char* filepath) //to check it it's a file or a directory
{
	struct stat buf;
	stat(filepath, &buf);
	return S_ISDIR(buf.st_mode); //stat command to return current dir with st.mode
}


int filecall(char* path, int fileindex)	//single file called multiple times by directory
{
	int size = 0; 
	char* fbuf; 
	char c = '0';
	int i = 0;

	FILE* fd = fopen(path, "r");

	if(fd == NULL)
	{
			fprintf(stderr, "can't open file\n");
			return 0;
	}

	fseek(fd,0L,SEEK_END);
	size = ftell(fd); 
	fseek(fd,0L,SEEK_SET);
	fbuf = (char*)calloc(size + 1,sizeof(char));

	while((c = fgetc(fd)) != EOF)
	{
		fbuf[i] = c;
		i++;
	}

	fclose(fd);

	buildTree(fbuf,size,filecount,fileindex,path);

	if(fWordCount == 0)
	{
		printf("'%s' no tokens are there\n", path);
		return 0;
	}

	fWordCount = 0;
	free(fbuf);
	return 1;
}

void directcall(char* filepath)
{	
	
	DIR* dir;
	struct dirent* ent;

		if ((dir = opendir(filepath)) != NULL)
		{
			while ((ent = readdir(dir)) != NULL)
			{
				if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) //no endless loop because of . and ..
				{
					continue;
				}
				
				//find the length of the path and file name
				int pathlength = strlen(filepath);
				int filelength = strlen(ent->d_name);
				
				//add path and file name together and copy them into a buffer so filecall method works properly
				char buffer[pathlength+filelength+1];
				memcpy(buffer, filepath, pathlength);
				
				//chck if the last character is a '/' and if it is then proceed normally
				if (filepath[pathlength-1] == '/')
				{
					memcpy(buffer+pathlength, ent->d_name, filelength+1);  //copies memory area
				} 

				else 
				{
					buffer[pathlength] = '/'; //add a '/' if it is missing
					memcpy(buffer+pathlength+1, ent->d_name, filelength+1); //copies memory area
				}

				//if the what is found is a file then build a file node and attach it to the file path linked list. Also increment the global file count
				if (!dircheck(buffer))
				{
					buildFileLL(buffer);
					filecount++;
				} 

				//subdirectory found. process it through a recursive call
				else 
				{
					directcall(buffer);
				}
			}
			
			closedir(dir);
		} 

		//case where directory cannot be opened
		else 
		{
			fprintf(stderr, "couldn't open directory\n");
			return;
		}

	return;
}

fileNode* buildFileNode(char* path) //builds the node in file path linked list
{
	fileNode* node = (fileNode*)malloc(1*sizeof(fileNode)); //mem allocation for node
	node->path = (char*)malloc(1*(strlen(path)+1)); //for path
	memcpy(node->path,path,strlen(path)); //copies n bytes from memory area src to memory area dest
	node->path[strlen(path)] = '\0';
	node->next = NULL;
	return node;
}

void buildFileLL(char* path)
{
	fileTemp->next = buildFileNode(path);
	fileTemp = fileTemp->next;
	return;
}

void mergeSort(countNode** countarr, int lo, int hi) //taken from online to save time as it's just the same algo
{
	int mid;
	if(lo < hi)
	{
		mid = ((lo+hi)/2);
		mergeSort(countarr,lo,mid);
		mergeSort(countarr,mid+1,hi);
		merge(countarr,lo,mid,hi);
	}
	return;
}

void merge(countNode** countarr, int lo, int mid, int hi) //taken online to save time as it's the same algo
{
	int i,m,k,l;
	countNode* temp[filecount-1];

	l = lo;
	i = lo;
	m = mid + 1;
	
	while((l<=mid) && (m<=hi))
	{

		if(countarr[l]->count > countarr[m]->count)
		{
			temp[i] = countarr[l];
			l++;
		}

		else if(countarr[l]->count == countarr[m]->count)
		{
			int check = strcmp(countarr[l]->filepath,countarr[m]->filepath);

			if(check <= 0)
			{
				temp[i] = countarr[l];
				l++;
			}
		}

		else
		{
			temp[i] = countarr[m];
			m++;
		}
		i++;

	}

	if(l>mid)
	{
		for(k=m;k<=hi;k++)
		{
			temp[i] = countarr[k];
			i++;
		}
	}

	else{
		for(k=l;k<=mid;k++)
		{
			temp[i] = countarr[k];
			i++;
		}
	}

	for(k=lo;k<=hi;k++)
	{
		countarr[k] = temp[k];
	}

}

void writeBot(treeNode* scout, char* buffer, FILE* target)
{
	fprintf(target, "%s %s %s\n", "\t{\"" , buffer , "\" : [");
	int i;
	for(i = 0; i < filecount; i++)
	{
		
		if(scout->countarr[i]->count == 0)
		{
			continue;
		}

		if(i < filecount - 1)   //print a comma after since it isn't the last entry
		{
			fprintf(target, "%s %s %s %d %s\n", "\t\t{\"", scout->countarr[i]->filepath, "\" : ", scout->countarr[i]->count, "},");
		}
		else //no comma since it's the last entry
		{
			fprintf(target, "%s %s %s %d %s\n", "\t\t{\"", scout->countarr[i]->filepath, "\" : ", scout->countarr[i]->count, "}");
		}

	}

	fprintf(target, "%s\n", "\t]},");

	return;
}

void addFileLL()
{
	
	int index = 0;
	
	//traverse the linked list and increment to index so that the file count can properly be hashed to the correct spot in a count array in the tree. Free during
	while(fileRoot != NULL){
		fileTemp = fileRoot->next;
		
		if(fileTemp != NULL){
			filecall(fileTemp->path,index);
			index++;
		}

		free(fileRoot->path);
		free(fileRoot);
		fileRoot = fileTemp;
	}

	return;
}

void writeCounts(char* wpath)
{
	FILE* target;
	treeNode* scout;
	char* buffer;
	int index;

	if(wordcount == 0)
	{
		printf("%s", "There were no tokens to be printed");
		return;
	}

	target = fopen(wpath, "w");
	scout = root;
	index = 0;

	buffer = (char*)calloc(1,maxlen+1);
	buffer[maxlen] = '\0';

	fprintf(target, "%s\n", "{\"list\" : [");

	treeDFS(scout,buffer,&index,target);

	fprintf(target,"%s", "]}");

	fclose(target);

	free(buffer);

	return;
}

int treeDFS(treeNode* scout,char* buffer,int* index, FILE* target)
{
	int i=0;
	int x=0;
	if(scout->level > -1)
	{
		buffer[scout->level] = scout->data;
	}

	if(scout->isWord > -1)
	{
		buffer[(scout->level)+1] = '\0';

		//terrible runtime but needed to work. Fix implementation later
		for(x=0;x<filecount;x++)
		{
			if(scout->countarr[x] == NULL)
			{
				scout->countarr[x] = buildCountNode("$");
				scout->countarr[x]->count = 0;
			}
		}

		mergeSort(scout->countarr,0,filecount-1);
		writeBot(scout,buffer,target);

		scout->isWord = *index;

		(*index)++;
	}

	for(i = 0; i < 36; i++)
	{
		if(scout == NULL)
		{
			continue;
		}

		else if(scout->next != NULL)
		{
			if(scout->next[i] != NULL)
			{
				treeDFS(scout->next[i],buffer,index,target);
			}
			else
			{
				continue;
			}
		}
	}


	return 0;

}

//compare function for qsort to compare count value of two count nodes, currecntly not implemented. qsort chunks before merging to optimize to industry standard
int countNodeCompare(const void* a, const void* b)
{
	const int ca = ((countNode*)a)->count;
	const int cb = ((countNode*)b)->count;

	if(ca != cb)
	{
		return cb - ca;
	}

	else
	{
		return strcmp(((countNode*)a)->filepath,((countNode*)b)->filepath);
	}
}