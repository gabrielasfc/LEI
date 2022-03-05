#include <stdio.h>
#include <string.h>

//STRINGS

//1
int contaVogais(char *s){
	char *vogais = "aeiouAEIOU";
	int i, conta=0;
	for (i=0; s[i] != '\0'; i++){
		if (strchr(vogais, s[i])) conta++;
	}
	return conta;
}



//2
int retiraVogaisRep(char *s){
	char *vogais = "aeiouAEIOU";
	int i, j=0, conta=0;
	for (i=0; s[i] != '\0'; i++){
		if (strchr(vogais, s[i]) && s[i]==s[i+1]) conta++;
		else{
			s[j] = s[i];
			j++;
		}
	}
	s[j]='\0';
	return conta;
}



//3
int duplicaVogais(char *s){
	char *vogais = "aeiouAEIOU";
	char aux [strlen(s) +  contaVogais(s) + 1];
	int i, j=0, conta=0;
	for (i=0; s[i] != '\0'; i++){
		if (strchr(vogais, s[i])){
			aux[j] = aux[j+1] = s[i]; 
			j = j+2;
			conta++;
		}
		else{
			aux[j] = s[i];
			j++;
		}
	}
	aux[j] = '\0';
	strcpy(s,aux);
	return conta;
}



//ARRAYS ORDENADOS

//1
int ordenado(int v[], int N){
	int i;
	for (i=0; i<N-1; i++){
		if (v[i] > v[i+1]) return 0;
	}
	return 1;
}



//2
void merge(int a[], int na, int b[], int nb, int r[]){
	int i=0, j=0, k=0;
	while (i<na && j<nb){
		if (a[i] < b[j]){
			r[k] = a[i];
			i++; k++;
		}
		else{
			r[k] = b[j];
			j++; k++;
		}
	}
	while (i<na){
		r[k] = a[i];
		i++; k++;
	}
	while (j<nb){
		r[k] = b[j];
		j++; k++;
	}
}



//3
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
	*y = temp;
}

void bubbleSort(int v[], int N){
	int i, j;
	for (i=0; i < N-1; i++){  
    	for (j=0; j < N-i-1; j++){
        	if (v[j] > v[j+1]){
              swap(&v[j], &v[j+1]);
        	}
    	}
   }
}

int partition(int v[], int N, int x){
	bubbleSort(v, N);
	int i=0;
	while (v[i] <= x && i<N){
		i++;
	}
	return i;
}