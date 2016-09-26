#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>

/* 
    Scrieţi în C un program care pentru fişierul dat ca argument pe linia de comandă 
    afişează drepturile de acces, in forma: 
    nume_utilizator: read, write, execute (se afiseaza doar cele existente) 
    nume_grup: idem 
    others: idem 

    de exemplu:
       steve: read, write, execute
       staff: read, execute
       others: read, execute

Pentru a afla numele unui utilizator respectiv grup pornind de la identificatorul său numeric, 
folosiţi funcţiile getpwuid şi respectiv getgrgid.
*/

int main(int argc, char *argv[]) 
{
      if(argc != 2)    
      return 1;

      int gid;
      struct group *g;
      struct stat fileStat;
      struct passwd *pw;
      uid_t uid;
    
      if(stat(argv[1],&fileStat) < 0)    
        return 1;

	printf("Information for %s\n",argv[1]);

	gid = atoi(argv[1]);
	g = getgrgid(gid);

	if (g == NULL) {
	    fprintf(stderr, "gid %d not found\n", gid);
	    return 1;
	}
	printf("Group name: %s\n", g->gr_name);

	uid = geteuid ();
	    pw = getpwuid (uid);
	    if (pw)
	{
	    printf("User name: %s\n", pw->pw_name);      	
	} 
	else 
	{
	    return 1;
	}
    

	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");
	
	return 0;
}