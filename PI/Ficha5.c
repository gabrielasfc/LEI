//Codeboard: https://codeboard.io/projects/231790

#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int numero;
    char nome[100];
    int miniT[6];
    float teste;
} Aluno;


//1
int nota(Aluno a){
    int r, i, mt = 0;
	float nota, mediaMT;
	for (i=0; i<6; i++) mt += a.miniT[i] * 10;
	mediaMT = mt/6;
	nota = mediaMT * 0.3 + a.teste * 0.7;
	if (mediaMT < 8 || a.teste < 8 || nota < 9.5) return 0;
	else return round(nota);
}


//2
int procuraNum(int num, Aluno t[], int N){
    int i;
    for (i=0; t[i].numero < num && i<N; i++);
    if (t[i].numero == num) return i;
    else return -1;
}


//3
void swap(Aluno v[], int i, int j){
    Aluno aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void ordenaPorNum(Aluno t[], int N){
    int i, j;
    for (i=0; i < N-1; i++){
        for (j=0; j < N-i-1; j++){
            if (t[j].numero > t[j+1].numero) swap(t, j, j+1);
        }
    }
}


//4
void swapInt(int v[], int i, int j){
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void criaIndPorNum(Aluno t[], int N, int ind[]){
	int i, j;
	for (i=0; i < N; i++) ind[i] = i;
	for (i=0; i < N-1; i++){
		for (j=0; j < N-i-1; j++){
			if (t[ind[j]].numero > t[ind[j+1]].numero) swapInt(ind, j, j+1);
        }
    }
}


//5
void imprimeAluno(Aluno *a){
    int i;
    printf("%d %s (%d", a->numero, a->nome, a->miniT[0]);
    for(i=1; i<6; i++) printf(", %d", a->miniT[i]);
    printf(") %5.2f %d\n", a->teste, nota(*a));
}

void imprimeTurma(int ind[], Aluno t[], int N){
	int i;
	for (i=0; i<N; i++) imprimeAluno(&(t[ind[i]]));
}


//6
int procuraNum2(int num, int ind[], Aluno t[], int N){
	int i;
    for (i=0; i < N && num < t[ind[i]].numero; i++);
    if (t[ind[i]].numero == num) return ind[i];
    else return -1;
}


//7
void criaIndPorNome(Aluno t [], int N, int ind[]){
    int i, j;
    for (i=0; i < N; i++) ind[i] = i;
    for (i=0; i < N-1; i++){
    	for (j=0; j < N-i-1; j++){
    		if (strcmp(t[ind[j]].nome, t[ind[j+1]].nome) > 0) swap(t, j, j+1);
    	}
    }
}