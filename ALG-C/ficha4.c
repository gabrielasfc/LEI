#include <stdio.h>
#include <stdlib.h>

#define NV 100

typedef struct aresta{
    int dest; 
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];



////////////////////////////  REPRESENTAÇÕES  ////////////////////////////

//1
//Melhor caso = Pior caso : V^2
void fromMat(GrafoM in, GrafoL out){
    int i, j;
    for(i=0; i<NV; i++) out[i] = NULL;
    for(i=0; i<NV; i++){
        for(j=NV-1; j>0; j--){
            if(in[i][j] != 0){
                LAdj new = malloc(sizeof(struct aresta));
                new->dest = j;
                new->custo = in[i][j];
                new->prox = out[i];
                out[i] = new;
            }
        }
    }
}


//2
//Pior caso = V+E
//Melhor caso = V -> não há adjacências
void inverte(GrafoL in, GrafoL out){
    int i;
    for(i=0; i<NV; i++) out[i] = NULL;
    for(i=0; i<NV; i++){
        for(LAdj l = in[i]; l != NULL; l = l->prox){
            LAdj new = malloc(sizeof(struct aresta));
            new->dest = i;
            new->custo = l->custo;
            new->prox = out[l->dest];
            out[l->dest] = new;
        }
    }
}


//3
int max(int v[], int N){
    int max = v[0];
    for(int i=i; i<N-1; i++){
        if(v[i] > max) max=v[i];
    }
    return max;
}

//Pior caso = V+E
//Melhor caso = V
int inDegree(GrafoL g){
    int count[NV] = {0};
    for(int i=0; i<NV; i++){
        for(LAdj l = g[i]; l != NULL; l = l->prox){
            count[l->dest]++;
        }
    }
    return (max(count, NV));
}

//4
//Pior caso = V+E
//Melhor caso = 1 -> caso em que não verifica logo a condição do if
int colorOK(GrafoL g, int cor[]){
    for(int i=0; i<NV; i++){
        for(LAdj l = g[i]; l != NULL; l = l->prox){
            if(cor[i] == cor[l->dest] && i != l->dest) return 0; //a 2ª condição verifica que não é um anel
        }
    }
    return 1;
}


//5
//Melhor caso = 1 -> procura uma aresta que não existe
//Pior caso = (V+E)*E
int procura(GrafoL h, int orig, int dest){
    for(LAdj l = h[orig]; l != NULL; l = l->prox){
        if(l->dest == dest) return 1;
    }
    return 0;
}

int homomorfOK(GrafoL g, GrafoL h, int f[]){
    for(int i=0; i<NV; i++){
        for(LAdj l = g[i]; l != NULL; l = l->prox){
            if(procura(h, f[i], f[l->dest]) == 0) return 0;
        }
    }
    return 1;
}



////////////////////////////  TRAVESSIAS  ////////////////////////////

//array v -> em cada posição coloca 0 ou 1, caso não tenha sido ou tenha sido visitado respetivamente
//array p -> coloca em cada posição o vértice pai dele (útil para ver o caminho)
//array l -> coloca em cada posição a iteração em que foi visitado (nível do vértice)
int DFRec (GrafoL g, int or, int v[], int p[], int l[]){
    int i=1;
    v[or]=-1;
    for (LAdj a = g[or]; a != NULL; a = a->prox){
        if (!v[a->dest]){
            p[a->dest] = or;
            l[a->dest] = 1 + l[or];
            i += DFRec(g, a->dest, v, p, l);
        }
    }
    v[or] = 1;
    return i;
}


int DF (GrafoL g, int or, int v[], int p[], int l[]){
    for(int i=0; i<NV; i++){
        v[i] = 0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1;
    l[or] = 0;
    return DFRec (g, or, v, p, l);
}


int BF (GrafoL g, int or, int v[], int p[], int l[]){
    int x;
    int q[NV], front, end;
    for (int i = 0; i < NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    front = end = 0;
    q[end++] = or; //enqueue
    v[or] = 1; p[or]=-1;l[or]=0;
    int i=1;
    while (front != end){
    x = q[front]; //dequeue
    front++;
    for (LAdj a = g[x]; a != NULL; a = a->prox)
        if (!v[a->dest]){
            i++;
            v[a->dest] = 1;
            p[a->dest] = x;
            l[a->dest] = 1 + l[x];
            q[end] = a->dest; //enqueue
            end++;
        }
    }
    return i;
}


//1
//distância -> tamanho do caminho mais curto

int max_indice(int v[], int N){
    int r=0, max=v[0];
    for(int i=1; i<N-1; i++){
        if(v[i]>max){
            max = v[i];
            r = i;
        }
    }
    return r;
}

int maisLonga(GrafoL g, int or, int p[]){
    int v[NV], pai[NV], l[NV];
    BF(g, or, v, pai, l);
    int vertice_max = max_indice(l, NV);
    int i = l[vertice_max]; //nível do vértice máximo
    for(int m = vertice_max; pai[i] != -1; i--){ //imprime o caminho desde a origem
        p[i] = m;
        m = pai[m];
    }
    p[i] = or;
    return i;
}


//2
void bf_comp(GrafoL g, int orig, int comp[], int count){
    int queue[NV], inic, fim;
    inic = fim = 0;
    comp[orig] = count;
    queue[fim] = orig; //enqueue
    fim++;
    while(inic != fim){
        int x = queue[inic]; //dequeue
        inic++;
        for(LAdj l = g[x]; l != NULL; l = l->prox){
            comp[l->dest] = count;
        }
    }
}   

int componentes(GrafoL g, int c[]){
    int i, count = 1;
    for(i=0; i<NV; i++) c[i] = 0; //inicializar o array das componentes a 0
    for(i=0; i<NV; i++){
        if(c[i] == 0){
            bf_comp(g, i, c, count);
            count++;
        }
    }
    return count;
}


//3
int ordTop_DFRec(GrafoL g, int orig, int v[], int ord[], int pos){
    v[orig] = 1;
    for (LAdj a = g[orig]; a != NULL; a = a->prox){
        if (v[a->dest] == 0){
            pos += ordTop_DFRec(g, a->dest, v, ord, pos);
        }
    }
    ord[pos] = orig;
    return pos+1;
}


int ordTop(GrafoL g, int ord[]){
    int v[NV], pos=0;
    for(int i = 0; i<NV; i++) v[i] = 0; //inicializa array de visitados a 0
    for(int j = 0; j<NV; j++){
        if(v[j]==0){
           pos += ordTop_DFRec(g, j, v, ord, pos); 
        }
    }
    return pos;
}
