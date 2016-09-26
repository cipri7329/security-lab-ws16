#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>
void afiseaza(char *nume,int grp, int oth)
{
	DIR *path;
	struct dirent *fld;
	struct stat buf,buf1;
	char *path_nou;
	int group=0,other=0,group1=0,other1=0;
	if(lstat(nume,&buf1)==-1)
	{
		printf("Eroare la lstat!\n");
		exit(1);
	}
	if((path=opendir(nume))==NULL)
	{
		printf("Eroare la deschiderea directorului!\n");
		exit(1);
	}
	if(S_IXGRP & buf1.st_mode)
		group=1;
	if(S_IXOTH & buf1.st_mode)
		other=1;
	if(grp!=1)
		group=0;
	if(oth!=1)
		other=0;
	while((fld=readdir(path))!=NULL)
	{
		path_nou=(char *)malloc(strlen(nume)+strlen(fld->d_name)+2);
		sprintf(path_nou,"%s/%s",nume,fld->d_name);
		if(lstat(path_nou,&buf)==-1)
		{
			printf("Eroare la lstat!\n");
			exit(1);
		}
		if(group==1||other==1)
			if(S_ISDIR(buf.st_mode))
			{
				if((strncmp(fld->d_name,".",2)==0)||(strncmp(fld->d_name,"..",2)==0))
					continue;
				printf("Subdirector:%s\n",path_nou);
				group1=0;other1=0;
				if(S_IXGRP & buf.st_mode)
					group1=1;
				if(S_IXOTH & buf.st_mode)
					other1=1;
				if(group!=1)
					group1=0;
				if(other!=1)
					other1=0;
				if(group1==1||other1==1)
					afiseaza(path_nou,group1,other1);
			}
			else
				{
					if((S_IWGRP & buf.st_mode) && group==1)
					{
						printf("Scriere:\n");
						printf("%s\n",path_nou);
					}
					else
						if((S_IWOTH & buf.st_mode) && other==1)
						{
							printf("Scriere:\n");
							printf("%s\n",path_nou);
						}
					group1=0;other1=0;
					if(S_IWGRP & buf1.st_mode)
						group1=1;
					if(S_IWOTH & buf1.st_mode)
						other1=1;
					if(group!=1)
						group1=0;
					if(other!=1)
						other1=0;
					if((S_IWGRP & buf.st_mode) && group1==1)
					{
						printf("Stergere:\n");
						printf("%s\n",path_nou);
					}
					else
						if((S_IWOTH & buf.st_mode) && other1==1)
						{
							printf("Stergere:\n");
							printf("%s\n",path_nou);
						}
				}
	}
	free(path_nou);
	closedir(path);
}
int main(int argc, char *argv[])
{
	int group, other;
	struct stat buf;
	if(argc!=2)
	{
		printf("Numar incorect de parametrii!\n");
		exit(1);
	}
	if(lstat(argv[1],&buf)==-1)
	{
	printf("Eroare la lstat!\n");
	exit(1);
	}
	if(S_IXGRP & buf.st_mode)
		group=1;
	if(S_IXOTH & buf.st_mode)
		other=1;
	afiseaza(argv[1],group,other);
	return 0;
}
