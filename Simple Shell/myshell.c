#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/file.h>

int fg_id = 0;

void sigchldHandler(int status) 
{
    int pid = wait(&status);
    
    if(pid == fg_id)
        fg_id = 0;
    
    signal(SIGCHLD, sigchldHandler);
}

int main()
{
    char input[256];
    char *tkn;
    char *argv[25];
    char *dosCT[] = {"exit","type","dir","md","delete","copy","sort","|",">",">>","&"};
    char *unixCT[] = {"exit","cat","ls","mkdir","rm","cp","sort"};
    int filedes[2];
    int i, new_cid, fd, j = 0, pipepos = 0, redir1 = 0, redir2 = 0, isfg;
    
    signal(SIGCHLD, sigchldHandler);
 
    while(1)
    {
        i = 0, new_cid = 0, fd = 0, j = 0, pipepos = 0, redir1 = 0, redir2 = 0, isfg = 1;
        printf("myShell> ");
        gets(input);
        
        tkn = strtok(input, " \n");
        
        if (tkn==NULL) 
            continue;
        
        while(tkn != NULL) 
        {
        	j = 0;
        	while(j < 11)
        	{
        	    if(strcmp(tkn, dosCT[j]) == 0)
        	        break;
		    j++;
        	}    
      
        	switch(j)
        	{
        	    case 0: exit(0);
        	    case 1:
        	    case 2:
        	    case 3:
        	    case 4:
        	    case 5:
        	    case 6: argv[i] = unixCT[j]; 
                            break;
        	    case 7: argv[i] = NULL; 
                            pipepos = i + 1; 
                            break;
        	    case 8: argv[i] = NULL; 
                            redir1 = i + 1; 
                            break;
        	    case 9: argv[i] = NULL; 
                            redir2 = i + 1; 
                            break;
        	    case 10: argv[i] = NULL; 
                             isfg = 0; 
                             break;
        	    default: argv[i] = tkn;
        	}
	    
            	tkn = strtok(NULL, " \n");

           	i++;
	}

	argv[i] = NULL;

        if(pipepos)
        {
            if (pipe(filedes) == -1) {
		perror("pipe"); return -1; 
	    }
            if(fork() == 0)
            {
                close(filedes[0]);
                dup2(filedes[1],1);
                execvp(argv[0], argv);
            }
            if((new_cid = fork()) == 0)
            {
                close(filedes[1]);
                dup2(filedes[0],0);
                execvp(argv[pipepos], argv+pipepos);
            }
	    close(filedes[0]);
	    close(filedes[1]);
        } else {
            if((new_cid = fork()) == 0)
            {
                if(redir1)
                   fd = open(argv[redir1], O_CREAT | O_WRONLY, 0600);
                if(redir2)
                   fd = open(argv[redir2], O_WRONLY | O_CREAT | O_APPEND,0600);
                if(fd) 
                    dup2(fd,1);
                execvp(argv[0], argv);
            }
        }
        if(isfg)
        {
             fg_id = new_cid;
             while(fg_id);
        }
     }
}
