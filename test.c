#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
	FILE *f1,*f2;
	f1=fopen(argv[1],"r");
	f2=fopen("out.txt","w");
	char s[1005];
	while(fgets(s,sizeof s,f1)!=NULL)
	{
		int i=0;
		for(;i<strlen(s);i++)
		{
			int f=1;
			for(int j=0;j<strlen(argv[2]))
			{
				if(s[i+j]!=argv[2][j]){
					f=0;
				}
			}
			if(f){
				for(int t=0;t<strlen(argv[3]);t++)
					fputc(argv[3][i],f2);
				i+=strlen(argv[2]);
				i--;
			}
			else fprintf(f2,"%s",s);
		}
	}
	return 0;
}
