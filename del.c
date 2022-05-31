#include"header_file.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct rewrite
{
    char name[33];
    char other_fields[200];
};
int del_(char *group_file, char *gshadow_file, char *group_name)
{
    char *file_array[2]={gshadow_file,group_file};
    char name_in_file[33], other_fields_in_file[200],ch;
    int line_input=0, found=0,file=0;
    FILE *fpg , *fpgs ;
    fpg = fopen(group_file,"r");
    fpgs = fopen(gshadow_file,"r");
    FILE *pointer_array[2]={fpgs,fpg};
    for(file = 0;file<2;file++)               // Two files : group and gshadow
    {
        int no_of_lines = 0;
        fseek(pointer_array[file],0,SEEK_SET);
        for(ch = fgetc(pointer_array[file]) ; ch != EOF ; ch = fgetc(pointer_array[file]))
        {
            if (ch == '\n')
                no_of_lines += 1 ;
        }                                    // To check number of lines
        no_of_lines += 1;
        fseek(pointer_array[file],0,SEEK_SET);
        struct rewrite all_line[no_of_lines]; // Array fo structures of that many lines
        for(line_input = 0 ; line_input < no_of_lines ; line_input++)
        {
            fscanf(pointer_array[file],"%[^:]%[^\n]",name_in_file,other_fields_in_file);
            strcpy(all_line[line_input].name , name_in_file);
            strcpy(all_line[line_input].other_fields , other_fields_in_file);
  
    
        }
                                          // Stores all the lines in the structures
        fclose(pointer_array[file]);
        pointer_array[file] = fopen(file_array[file],"w+");
        fseek(pointer_array[file],0,SEEK_SET);
                                          //To search for the given group name
        for(line_input = 0 ; line_input < no_of_lines ; line_input++)
        {
            if(all_line[line_input].name[0] == '\n')
            {
                if(strcmp(all_line[line_input].name+1 , group_name) == 0)
                    found=1;
                else
                {
                    fprintf(pointer_array[file],"%s%s",all_line[line_input].name,all_line[line_input].other_fields);   
                }
                
            }
            else
            {
                if(strcmp(all_line[line_input].name, group_name) == 0)
                    found = 1;
                else
                {
                    fprintf(pointer_array[file],"%s%s",all_line[line_input].name,all_line[line_input].other_fields);
                }
                
            }
            
        }
        if (found == 0)
        {
            printf("The group '%s' does not exist.",group_name);
            break;
        }
        
    }
    if (file == 2)
        printf("Removing group `%s' ...\nDone.",group_name);
    //If removed from both groups successfully then prints this result
    return(0);
}