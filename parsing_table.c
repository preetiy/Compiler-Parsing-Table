#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void find_follow(char);
void find_first(char,int,int);
void follow(char,int,int);

int count=0, n=0,m=0,k,e;
char ch1,prod[20][20]={}, first[20],foll[20], final_first[20][100],final_follow[20][100];


int main(){
	
	int l=0,z=0,i,opt;
	char c, ch;
	printf("ASSUMPTIONS:\n");
	printf("1. Rules are in\n A=XY\n A=B\n format only\n\n2.& is used for epsilon\n\n");
	
	char init[10][10];
	char cop[10],cop2[10];
	char explored[10]={};
	char fc;
	int flag=0;
	char recur='X';
	int ct,i2,j2,k1,k2,e2=0,pro=0;
	
	int lineno=0;
	FILE *fp;
	int lsize = 255;
	char line[lsize];
	fp = fopen("toread.txt","r");
	while(fgets(line,lsize,fp)){
		line[strlen(line)-1]='\0';
		strcpy(init[lineno],line);
		lineno++;
	}
	ct=lineno;
	
	for(i2=0;i2<ct;i2++){
		strcpy(cop,init[i2]);
		fc=cop[0];
		int flag=0;
		for(j2=0;j2<e2;j2++){
			if(fc==explored[j2]){
				flag=1;
				break;
			}
		}
		if(flag==1){
			continue;
		}
		if(fc!=cop[2])
			strcpy(prod[pro++],cop);
			
		if(fc==cop[2]){ // checking if left recursion is present
			
			explored[e2++]=fc;
			
			
			char sub[10]={};
			for(k1=3;k1<strlen(cop);k1++){
				sub[k1-3]=cop[k1];
			}
			for(j2=0;j2<ct;j2++){
				
				if(i2!=j2 && init[j2][0]==fc){
					strcpy(cop2,init[j2]);
					char sub2[10]={};
					for(k1=2;k1<strlen(cop2);k1++){
						sub2[k1-2]=cop2[k1];
					}
					
					k1=0;
					prod[pro][k1++]=fc;
					prod[pro][k1++]='=';
					k2=0;

					while(k2<strlen(sub2)){
						prod[pro][k1++]=sub2[k2++];

					}
					prod[pro++][k1]=recur;
					
					k1=0;
					prod[pro][k1++]=recur;
					prod[pro][k1++]='=';
					k2=0;
					while(k2<strlen(sub)){
						prod[pro][k1++]=sub[k2++];
					}
					prod[pro++][k1]=recur;
					k1=0;
					prod[pro][k1++]=recur;
					prod[pro][k1++]='=';
					prod[pro++][k1]='&';
					recur++;
					
				}
			}
		}
		
	}
	
	printf("\nRules after removing left recursion(if any)\n");
	for(i2=0;i2<pro;i2++)
		printf("%s\n",prod[i2]);
	
	count=pro;
	
	int g;
	char finish[count];
	int ptr=-1;
	for(k=0;k<count;k++){
		for(g=0;g<100;g++){
			final_first[k][g]='#';
		}
	}
	int pt1 = 0, pt2, d;
	printf("\nFirst\n");
	for(k=0;k<count;k++){
		c = prod[k][0];
		pt2= 0;
		d=0;
		for(g=0;g<=ptr;g++){
			if(c==finish[g]){ //checking if first of c has already been calculated
				d=1;
			}
		}
		if(d==1){
			continue;
		}
		find_first(c,0,0); // function call
		ptr+=1;
		finish[ptr]=c;
		printf("\n%c =  ",c);
		final_first[pt1][pt2++]=c;
		for(i=0+l;i<n;i++){
			int v1=0,v2=0;
			for(v1=0;v1<pt2;v1++){
				if(first[i]== final_first[pt1][v1]){
					v2=1;
					break;
				}
			}
			if(v2==0){
				printf("%c  ",first[i]);
				final_first[pt1][pt2++] = first[i];
			}
		}
		
		l=n;
		pt1++;
	}
	printf("\n");
	char finished[count];
	ptr=-1;
	for(k=0;k<count;k++){
		for(g=0;g<100;g++){
			final_follow[k][g] = '#';
		}
	}
	pt1=0;
	int s=0;
	printf("\nFollow\n");
	for(e=0;e<count;e++){
		ch1= prod[e][0];
		pt2=0;
		d=0;
		for(g=0;g<=ptr;g++){
			if(ch1 == finished[g]){
				d=1;
			}

		}
		if(d==1){
			continue;
		}
		s+=1;
		find_follow(ch1);
		ptr+=1;
		finished[ptr]=ch1;
		printf("\n%c =  ",ch1);
		final_follow[pt1][pt2++] = ch1;
		for(i=0+z;i<m;i++){
			int v1=0,v2=0;
			for(v1=0;v1<pt2;v1++){
				if(foll[i]==final_follow[pt1][v1]){
					v2=1;
					break;
				}
			}
			if(v2==0){
				printf("%c ",foll[i]);
				final_follow[pt1][pt2++]= foll[i];
			}
		}
		
		z=m;
		pt1++;

	}
	char terminal[20]={};
	int py,kg,kp=0;
	for(k=0;k<count;k++){ //obtaining terminals
		for(g=0;g<strlen(prod[k]);g++){
			if(!isupper(prod[k][g]) && prod[k][g]!='&' && prod[k][g]!='=' && prod[k][g]!= '\0'){
				kg = 0;
				for(py =0;py< kp;py++){
					if(prod[k][g]==terminal[py]){
						kg=1;
						break;
					}
				}
				if(kg==0){
					terminal[kp] = prod[k][g];
					kp++;
				}

			}
		}
	}
	terminal[kp]='$';
	kp++;
	
	char table_first[count][kp];
	for(py=0;py<count;py++){
		int f=0, q=0;
		char pseudo[100];
		k=2;
		while(prod[py][k] != '\0'){
			if(!isupper(prod[py][k])){ //storing first of each production rule  in format of a%b%
				pseudo[q++] = prod[py][k];
				pseudo[q++] = '%';
				pseudo[q++] = '\0';
				k++;
				break;
			}
			else{
				int foo=0, loo=0;
				for(foo=0;foo<count;foo++){
					if(final_first[foo][0]==prod[py][k]){
						for(loo=1;loo<100;loo++){
							if(final_first[foo][loo]!= '#'){
								pseudo[q++] = final_first[foo][loo];
							}
							else{
								break;
							}

						}
					break;
					}
				}
				pseudo[q++] = '%';
			}
			k++;
		}
		int foo= 0, loo;
		for(loo =0;loo< q;loo++){
			if(pseudo[loo]=='&'){
				foo=1;
			}
			else if(pseudo[loo]=='%'){
				if(foo==1){
					foo =0;

				}
				else{
					break;
				}
			}
			else{
				table_first[py][f++] = pseudo[loo];
			}
			table_first[py][f]='\0';
		}


	}
	char table[s][kp+1];
	ptr = -1;
	for(py=0;py<s;py++){
		for(g=0;g<(kp+1);g++){
			table[py][g] = '#';
		}
	}
	for(py=0;py<count;py++){
		ch1= prod[py][0]; 
		d=0;
		for(g=0;g<=ptr;g++){
			if(ch1 == table[g][0]){
				d=1;
			}
		}
		if(d==1){
			continue;
		}
		else{
			ptr = ptr+1;
			table[ptr][0] = ch1;
		}
	}
	for(py=0;py<count;py++){
		int loo=0;
		while(table_first[py][loo] != '\0'){
			int b, h=0;
			for(b=0;b<kp;b++){
				if(table_first[py][loo] == terminal[b]){
					h=1;
				}
			}
			if(h==1){
				char jk = prod[py][0];
				int w=0;
				while(table[w][0] !=jk){
					w = w+1;
				}
				int v=0;
				while(terminal[v] != table_first[py][loo]){
					v=v+1;
				}
				
				//storing ith number of production rule in each cell
				if(table[w][v+1]=='#')
					table[w][v+1] =py + 48; 
				else{
					int place=table[w][v+1] - '0';
					int total = py*10 + place ;
					table[w][v+1] = total + 48;
				}
				
				
			}
			loo++;
		}
	}
	for(k=0;k<s;k++){
		for(g=0;g<100;g++){
			if(final_first[k][g]=='#'){
				break;
			}
			else if(final_first[k][g]=='&'){
				int u=1;
				while(final_follow[k][u] != '#'){
					char jk = prod[k][0];
					int w=0;
					while(table[w][0]!= jk){
						w = w+1;
					}
					int v=0;
					while(terminal[v] != final_follow[k][u]){
						v=v+1;
					}
					table[k][v+1] = '&';
					u++;
				}
				break;
			}
		}
	}
	printf("\n\nPARSING TABLE:\n   ");
	printf("\t\t");

	for(py=0;py<kp;py++){
		printf("%c\t\t",terminal[py]);
	}
	printf("\n\n");
	for(py=0;py<s;py++){
		printf("   %c\t\t", table[py][0]);
		for(g=1;g<(kp+1);g++){
			if(table[py][g] == '#'){
				printf("\t\t");

			}
			else if(table[py][g] =='&'){
				printf("%c=&\t\t",table[py][0]);
			}
			else{
				
				int bn = table[py][g];
				bn-= 48;
				if (bn<=9){//if only one production rule
					printf("%s\t\t",prod[bn]);
				}
				else{ // if more than one production rule in a cell of a table
					printf("%s & ",prod[bn%10]);
					printf("%s\t",prod[bn/10]);
				}
			}
		}
	printf("\n\n");
	}



}




void find_first(char c, int x, int y ){
	int k;
	if(!(isupper(c))){ //when a terminal symbol is encountered
		first[n++]=c;
	}
	for(k=0;k<count;k++){
		if(prod[k][0]==c){
			if(prod[k][2]=='&'){
				if(prod[x][y]=='\0'){ // when encountered an epsilon and it is last symbol of that production rule
					first[n++]='&';
				}
				else if(prod[x][y]!='\0' && (x!=0 || y!=0)){ // resursion to find first of next non-terminal symbol after epsilon
					find_first(prod[x][y],x,(y+1));
				}
				else{
					first[n++]='&';
				}
			}
			else if(!isupper(prod[k][2])){// if encountered a terminal symbol after epsilon
				first[n++] = prod[k][2];
			}
			else{
				find_first(prod[k][2],k,3); // recursion to find first of non-terminal symbol found at beginning
			}
		}
	}
}

void follow(char c,int p,int q){
	int k;
	if(!(isupper(c))){ // when terminal symbol encountered
		foll[m++]=c;
	}
	else{
		int i=0, j=1;
		for(i=0;i<count;i++){
			if(final_first[i][0]==c)
				break;
		}
		while(final_first[i][j]!='#'){ // getting first set of the non-terminal encountered
			if(final_first[i][j]!='&'){
				foll[m++] = final_first[i][j];
			}
			else{
				if(prod[p][q]=='\0'){
					find_follow(prod[p][0]); // when we reach end of production
				}
				else{
					follow(prod[p][q],p,q+1); // recursion to next symbol if epsilon is encountered
				}
			}
			j++;
		}


	}
}




void find_follow(char c){
	int p,q;
	if(prod[0][0]==c){
		foll[m++]='$'; // adding $ to the follow of start symbol
	}
	for(p=0;p<20;p++){
		for(q=2;q<20;q++){
			if(prod[p][q]==c){
				if(prod[p][q+1]!='\0'){
					follow(prod[p][q+1],p,(q+2)); // getting the first of the next non-terminal symbol
				}
				if(prod[p][q+1]=='\0' && c!=prod[p][0]){
					find_follow(prod[p][0]); // getting follow of non-terminal at L.H.S. of the rule
				}
			}
		}
	}
}



