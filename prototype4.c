//code by JJ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

int _cry(char* vvbuf,char* arg,char* vbuf)
{
        char* pResult;
	FILE* IN;
	int i;
	char* out;

        if(!(IN=fopen(arg,"r"))){
                perror("fopen");
                return 1;
        }
	for(i=0;!feof(IN);i++){
		out=(char*)malloc(100);
		fscanf(IN,"%s",out);
       		pResult=crypt(out,vvbuf);
		printf("%s\n",out);
		if(!strcmp(pResult,vbuf)){
			printf("PW is %s\n",out);
			free(out);
			return 0;
		}
	}
	free(out);
        return 0;
}


int _parse2(char* vbuf,char* vvbuf){
	char* tmp;
	int j,i;
	int l=0;
	
	for(j=0;*(vbuf+j);j++){
		if(*(vbuf+j)=='$'){
			l++;
		}
		if(l==3){
			break;
		}
	}
	tmp=(char*)malloc(j+2);
	for(i=0;i<=j;i++){
		*(tmp+i)=*(vbuf+i);
		if(i==j){
			*(tmp+j+1)='\0';
			break;
		}
	}
	for(i=0;i<=j;i++){
		*(vvbuf+i)=*(tmp+i);
		if(i==j){
			*(vvbuf+j+1)='\0';
			break;
		}
	}
	free(tmp);
	return j;
}

int _parse(char* out,char* vbuf[],char* buf,char* arg){

	char* vvbuf;
	int j,k,m=0;
	int n=0;
	int t=0;

	vvbuf=(char*)malloc(30);
	
	for(j=0;*(out+j);j++){
		if(*(out+j)==':'){
			vbuf[m]=(char*)malloc(n);
			for(k=0;k<=n;k++){
				if(*(out+(j-n+k))!=':'){	
					*(vbuf[m]+t)=*(out+(j-n+k));
					t++;
				}
				if(k==n){
					*(vbuf[m]+t)='\0';
					break;
				}	
			}
			t=0;
			n=0;
			m++;
		}
		n++;
	}
	if(!strcmp(buf,vbuf[0])){
		_parse2(vbuf[1],vvbuf);
		_cry(vvbuf,arg,vbuf[1]);
		free(vvbuf);
	}
	return m;
}

int _parse_free(char* vbuf[],int m){
	int j;
	for(j=0;j<m;j++){
		free(vbuf[j]);
	}	
	return 0;
}
	

int main(int argc,char* argv[]){
        FILE* in;
	char* buf;
	char* vbuf[100];
	int j,i;
        char* out[100];
	char* arg;

	if(argc!=4){
		printf("Useage ./prototype id pwfile dic\n");
		exit(0);
	}
	buf=argv[1];
	arg=argv[3];

        if(!(in=fopen(argv[2],"r"))){
                perror("fopen");
                return 1;
        }
	for(i=0;!feof(in);i++){
		out[i]=(char*)malloc(200);
		fscanf(in,"%s",out[i]);
	}
	fclose(in);
	
	//parsing & free 
	for(j=0;j<i;j++){
		_parse_free(vbuf,_parse(out[j],vbuf,buf,arg));
	}

	for(j=0;j<i;j++){
		free(out[j]);
	}	
	return 0;
}

