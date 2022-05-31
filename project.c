// We assume the user to be root
// As we consider the user to be root we don't need to use sudo
// ex: ./a.exe delgroup group_name
// Sometimes the program does not work for long group names[23-32 chars].

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header_file.h"

int main(int argc,char *argv[]) //Accepting command line arguments
{
    putenv("PFILE=PFILE"); // Setting the environment variable to a folder which contains group and gshadow files
    char* group_name;
    char* group_file = (char*)malloc(sizeof(getenv("PFILE"))+6);
    strcpy(group_file,getenv("PFILE"));
    strcat(group_file,"\\group"); //path to group file
    char* gshadow_file = (char*)malloc(sizeof(getenv("PFILE"))+8);
    strcpy(gshadow_file,getenv("PFILE"));
    strcat(gshadow_file,"\\gshadow"); //path to gshadow file
    char *command = (char*)malloc(sizeof(argv[1]));
    strcpy(command,argv[1]); // Take the command to check for syntax
    if (argc > 3) // When command is too long
    {   if(check_syn(command) != -1)
            printf("The user `%s' does not exist.\n",argv[2]); 
        else
            printf("syntax error near unexpected token.\n");
        
    }
    else
    {
        if(argc == 2)
        {
            group_name = (char*)malloc(200*sizeof(char)); // Way of taking the group name
            printf("Enter a group name to remove: ");
            scanf("%[^\n]",group_name);
        }
        else if(argc == 3)
        {
            group_name = (char*)malloc(sizeof(argv[2]));
            strcpy(group_name,argv[2]);
        }

        if(check_syn(command) != -1) // Checks the syntax
        {
            if(strlen(group_name) <= 32) // Checks the group name condition
            {
                del_(group_file,gshadow_file,group_name); // Deletes from the file
            }
            else
                printf("groupadd: '%s' is not a valid group name.\n",group_name);
        }
        else
            printf("syntax error near unexpected token.\n");   
    }
    

    return(0);
}