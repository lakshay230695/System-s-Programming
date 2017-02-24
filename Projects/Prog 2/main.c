/* Lakshay anand
	001269497
	lanand@albany.edu */

#include<stdio.h>			//header files
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "headerboiz.h"
#include<sys/types.h>
#include<sys/stat.h>      

int main(int argc, char **argv)		//main function
{
	DIR *dir;				//dir pointer
	struct dirent *ent;		//structure for dirent
	int i = 0;				//not used
	char mp3dir[MAXLENGTH];	//mp3 directory
	char *token;			//token pointer
	const char s[2] = "-";	// - to divide the filename into tokens
	char tracknumber[1000];	//saves the tracknumber taken out of filename using token
	char artist[30];		//saves the artist name taken out of filename using token
	char year[5];			//saves the year taken out of filename using token
	char album[30];			//saves the album name taken out of filename using token
	char mp3name[50];		//name of mp3file
	char backdir[1000];		// ../../ to move directory backwards
	char filename[1000];	//full filename

	if(argc>2)
	{
		fprintf(stderr,"incorrect number of arguments");
		exit(1);
	}
	if(argv[1]!=NULL)			//if a organizer (path) is not null
	{
		if(chdir(argv[1])==-1)
		{
			fprintf(stderr,"The directory doesn't exist");
			exit(1);
		}	
		else
		{
			getcwd(mp3dir, MAXLENGTH);  	//makes that path current dir and moves there
		}
	}
	else
	{
		getcwd(mp3dir, MAXLENGTH);	//if just organize is there without path
	}


	if ((dir = opendir (mp3dir)) != NULL) 		//if directory isnt empty
	{
		while ((ent = readdir (dir)) != NULL)	//while loop to read dir
		{
			if(strstr(ent->d_name, ".mp3") != NULL) //substring of filename is mp3
			{
				// File is an mp3 file
				strcpy(backdir, "../../../");		
				strcpy(filename, ent->d_name);	//copies d_name to fiename (as token modifies ent->d_name)

				token = strtok(ent->d_name, s); 	//tokens taking value in them and separating with - (s)
				strcpy(tracknumber, token);

				token = strtok(NULL, s);
				strcpy(artist, token);

				token = strtok(NULL, s);
				strcpy(year, token);

				token = strtok(NULL, s);
				strcpy(album, token);

				token = strtok(NULL, s);
				strcpy(mp3name, token);

				/*printf("%s\n", tracknumber);
				printf("%s\n", artist);
				printf("%s\n", year);
				printf("%s\n", album);
				printf("%s\n\n", mp3name);*/


				mkdir(artist, 0700);			//making directories and changing the current dir to them
				chdir(artist);
				mkdir(year, 0700);
				chdir(year);
				mkdir(album, 0700);
				chdir(album);
				
				strcat(backdir, filename);		//concatinating filenames(original) to the path
				strcat(tracknumber, " - ");
				strcat(tracknumber, mp3name);	

				movefunc(backdir, tracknumber);	//calling a movefunc to rename and move mp3 file to the proper folders

				chdir("../../../");		//changes directory back to the home directory
			}
		}

		closedir (dir);
	}

	else
	{
		perror ("Could not open the directory");	//displays and error if couldnt open directory
		exit(1);
	}

	return 0;
}