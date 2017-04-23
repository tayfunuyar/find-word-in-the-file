#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define BUFF 50
struct thr{
	char *input;
	char *word;
};

int comp(char* path,char * word)
{
	FILE * file;
	char*buf=malloc(sizeof(char)*BUFF);
	int c,a;
	file=fopen(path,"r");
	while((c= fscanf(file,"%s",buf) ) != EOF)
	{
		if((a=strcmp(word,buf))==0)
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}
void * finder(void *t)
{
	struct thr *ca=(struct thr *) t;
	int *val=malloc(sizeof(int));
	*val=comp(ca->input,ca->word);	
	pthread_exit((void *) val);	
}
int main()
{
	pthread_t tid[5];
	int i,tt,num;
	int *val=malloc(sizeof(int));
	struct thr thr_val;
	char term[BUFF];
	char filename[BUFF];
	char *temp=malloc(sizeof(char));
	printf("File #? ");
	scanf("%d",&num);
	printf("\nWord? ");
	scanf("%s",term);
	printf("\n");
	thr_val.word=term;
	printf("\n");
	for(i=0;i<num;i++)
		{
		strcpy(filename,"inputs/inputThread");
		sprintf(temp,"%d",i+1);
		strcat(filename,temp);
		strcat(filename,".txt");
		thr_val.input=filename;
		tt=pthread_create(tid+i,NULL,finder,(void *)&thr_val);
		if (tt)
		{
			printf("ERROR; return code from pthread_create() is %d\n", tt);
			exit(-1);
		}
		pthread_join((*(tid+i)),(void**) &val);
		if((*val)==1)
			{
				printf("inputThread%d.txt -> True\n",i);
			}
		else
			{
				printf("inputThread%d.txt -> False\n",i);
			}
		}
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}
