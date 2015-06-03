
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 100


bool isblankspace(char a)
{
	if(a == ' ')
		return true;
	else
		return false;

}
bool isnumber(char a)
{
	if(a>=48&&a<=57)
		return true;
	else
		return false;

}


typedef struct http_data
{
	char remote[20], rfc931[2], authuser[2], datetime[30];
	char req[500], status[10], bytes[10];
	char ref[500], platform[500];
}http_data;


void generate();
void printline();

FILE *p;
http_data data[400];




void generate()
{
	int i, j, k=0;
	char X[500];

	for(i=0; i<399; i++)
	{
		fgets(X, 500, p);
		j=0;

		
		while(isnumber(X[j]) || X[j]=='.')
			data[i].remote[k++]=X[j++];
		k=0;

		while(isblankspace(X[j]))
			j++;

		
		while(!isblankspace(X[j]))
			data[i].rfc931[k++]=X[j++];
		k=0;

		while(isblankspace(X[j]))
			j++;

		
		while(!isblankspace(X[j]))
			data[i].authuser[k++]=X[j++];
		k=0;

		
		while(X[j]!='[')
			j++;
		while(X[j]!=']')
			data[i].datetime[k++]=X[j++];
		data[i].datetime[k]=X[j];
		k=0;

		
		while(X[j]!='"')
			j++;
		data[i].req[k++]=X[j++];
		while(X[j]!='"')
			data[i].req[k++]=X[j++];
		data[i].req[k]=X[j++];
		k=0;

		
		while(isblankspace(X[j]))
			j++;
		while(isnumber(X[j]))
			data[i].status[k++]=X[j++];
		k=0;

		
		while(isblankspace(X[j]))
			j++;
		if(X[j]=='-')
			data[i].bytes[0]='-';
		else
		{
			while(isnumber(X[j]))
				data[i].bytes[k++]=X[j++];
		}
		k=0;

		
		while(X[j]!='"')
			j++;
		data[i].ref[k++]=X[j++];
		while(X[j]!='"')
			data[i].ref[k++]=X[j++];
		data[i].ref[k]=X[j++];
		k=0;

		
		while(X[j]!='"')
			j++;
		data[i].platform[k++]=X[j++];
		while(X[j]!='"')
			data[i].platform[k++]=X[j++];
		data[i].platform[k]=X[j++];
		k=0;

		
		printf("\n\nLog No:%d\nUsername->\t %s\nrfc931->\t\t %s\nRemotehost->\t %s\nDate->\t\t %s\nRequest->\t %s",i+1,  data[i].authuser, data[i].rfc931, data[i].remote , data[i].datetime, data[i].req);
		printf("\nStatus->\t %s\nBytes->\t\t %s\nReferrer->\t %s", data[i].status, data[i].bytes, data[i].ref);
		printf("\nPlatform->\t %s", data[i].platform);
		
		cnt++;
		
	}
}


void printline()
{
	int i;
	for(i=0; i<80; i++)
		printf("_");
	printf("\n");
}

int main()
{
	char c, s[MAX];
	//clrscr();
	p=fopen("weblog.txt", "r");

	if(p==NULL)
	{
		printf("\n\tSource File not Found");
		//getch();
		exit(0);
	}

	generate();
	//getch();
	
	
	return 0;
	//getch();
}