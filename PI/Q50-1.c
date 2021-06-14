#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



//1
void max(){
	int x, max;
	scanf("%d", &x);
	max = x;
	while (x != 0){
		if (x>max) max=x;
		scanf("%d", &x);
	}
	printf("%d\n", max);
}



//2
void media(){
	int x, i, s=0;
	float media;
	scanf("%d", &x);
	for (i=0; x!=0; i++){
		scanf("%d", &x);
		s = s+x;
	}
	media = (float)s/(float)(n-1);
	printf("%f\n", media);
}



//3
void sndmax(){
	int x, max, sndmax;
    scanf("%d", &x);
    max = x;
    scanf("%d", &x);
    if (sndmax > x) {
        max = sndmax;
        sndmax = x; 
    }
    while (x != 0) {
        scanf("%d", &x);
        if (x > max){
            sndmax = max;
            max = x;
        }
        else if (x > sndmax) sndmax = x;
    }
    printf("%d", sndmax);
}



//4
int bitsUm(unsigned int n){
    int r;
    r = 0;
    while (n != 0) {
           if (n%2 == 1) r++;
           n = n / 2;
    }
    return r;
}



//5
int trailingZ(unsigned int n){
	int r=0;
	if (n==0) r=32;
	else{
		while (n%2 == 0){
        	r++;
        	n = n / 2;
   		}
   }
   return r;
}



//6
int qDig(unsigned int n){
	int r=0;
	while (n != 0){
		r++;
		n = n/10;
	}
   	return r;
}



//STRINGS

//7
char *mystrcat(char s1[], char s2[]){
	while (*s1 != '\0') s1++;
	while (*s2 != '\0'){
		*s1 = *s2;
		s1++; s2++;
	}
	*s1='\0';
	return s1;
}



//8
char *mystrcpy(char *dest, char source[]){
	int i;
	for (i=0; source[i] != '\0'; i++) dest[i] = source[i];
	dest[i] = '\0';
	return dest;
}



//9
int mystrcmp (char s1[], char s2[]){
	int i;
	for (i=0; s1[i]==s2[i] && s1[i] != '\0'; i++);
	return (s1[i]-s2[i]);
}



//10
char *mystrstr(char s1[], char s2[]){
	int i, pos;
	int j=0;
	if (s1[0]=='\0' && s2[0]=='\0') return s1;
	for (i=0; s1[i] != '\0'; i++){
		if (s1[i]==s2[0]) pos=i;
		if (s1[i]==s2[j]) j++;
		if (s2[j]=='\0') return s1+pos;
	}
	return NULL;
}



//11
void strrev(char s[]){
	int i;
	int l = strlen(s);
	char aux;
	for(i=0; i < l/2; i++){
		aux = s[i];
		s[i] = s[l-i-1];
		s[l-i-1] = aux;
	}
}



//12
void strnoV(char s[]){
	char *vogais = "aeiouAEIOU";
	int i, j=0;
	for (i=0; s[i] != '\0'; i++){
		if (!strchr(vogais, s[i])){
			s[j] = s[i];
			j++;
		}
	}
	s[j] = '\0';
}



//13
void truncW(char t[], int n){
	int i, j=0;
	int plength=0;
	for (i=0; t[i] != '\0'; i++){
		if (t[i] != ' ' && plength<n){
			t[j] = t[i];
			plength++;
			j++;
		}
		else if (t[i] == ' '){
			plength=0;
			t[j] = t[i];
			j++;
		}
	}
	t[j]='\0';
}



//14
int conta(char c, char s[]){
	int i, r=0;
	for (i=0; s[i] != '\0'; i++){
		if (s[i] == c) r++;
	}
	return r;
}

char charMaisfreq(char s[]){
	int i, max=0;
	char r;
	for (i=0; s[i] != '\0'; i++){
		if (conta(s[i], s) > max){
			max = conta(s[i], s);
			r = s[i];
		}
	}
	return r;
}



//15
int iguaisConsecutivos(char s[]){
	int i, conta=1, max=0;
	for (i=0; s[i] != '\0'; i++){
		if (s[i] == s[i+1]) conta++;
		else{
			if (conta > max){
				max = conta;
				conta=1;
			}
		}
	}
	return max;
}



//16
int diferente(int i, int j, char s[]) {
   	for(; i<j; i++){
   		if (s[i]==s[j]) return 0;
   	}
   	return 1;
}

int difConsecutivos(char s[]){
	int i, j, max=0, conta=0;
	for(i=0; s[i] != '\0'; i++){
	    for(j=i; s[j] != '\0' && diferente(i,j,s); j++) conta++;
	    if (conta>max) max=conta;
		conta=0;
	}
	return max;
}



//17
int maiorPrefixo(char s1 [], char s2 []){
	int i, r=0;
	for (i=0; s1[i] != '\0' && s2[i] != '\0' && s1[i]==s2[i]; i++)
		r++;
	return r;
}



//18
int maiorSufixo(char s1 [], char s2 []){
	int r=0, l1 = strlen(s1), l2 = strlen(s2);
	while (s1[l1-1] == s2[l2-1]){
		l1--;
		l2--;
		r++;
	}
	return r;
}



//19
int sufPref(char s1[], char s2[]){
	int i, j=0, r=0;
	for (i=0; s1[i] != '\0' && s2[j] != '\0'; i++){
		if (s1[i] == s2[j]){
			j++;
			r++;
		}
	}
	if (s1[i] != '\0') r=0; //se s2 já estiver vazia mas s1 não
	return r;
}



//20
//teste da codeboard falha porque falta acresentar os casos de \n
int contaPal(char s[]){
    if (s[0] == '\0') return 0;
	int i, j=0, conta=0;
	for (i=0; s[i] != '\0'; i++){
	    if (s[0] == ' ') s++;
		if (s[i] != ' ' && s[i+1] == ' ') conta++;
	}
	if (s[i-1] != ' ') conta++;
	return conta;
}



//21
int contaVogais(char s[]){
	char *vogais = "aeiouAEIOU";
	int i, conta=0;
	for (i=0; s[i] != '\0'; i++){
		if (strchr(vogais, s[i])) conta++;
	}
	return conta;
}



//22
int contida(char a[], char b[]){
	int i, j=0;
	for (i=0; a[i] != '\0'; i++){
		if (!strchr(b, a[i])) return 0;
	}
	return 1;
}



//23
int palindrome(char s[]){
	int i, l = strlen(s);
	for (i=0; i < l/2; i++){
		if (s[i] != s[l-i-1]) return 0;
	}
	return 1;
}



//24
int remRep(char x[]){
	int i, j=0;
	for (i=0; x[i] != '\0'; i++){
		if (x[i] != x[i+1]){
			x[j] = x[i];
			j++;
		}
	}
	x[j] = '\0';
	return j;
}



//25
int limpaEspacos(char t[]){
	if (t[0] == '\0') return 0;
	int i, j=0;
	for (i=0; t[i] != '\0'; i++){
		if (t[i] != ' ' || t[i] == ' ' && t[i+1] != ' '){
			t[j] = t[i];
			j++;
		}
	}
	t[j] = '\0';
	return j;
}



//ARRAYS

//26
void insere(int v[], int N, int x){
	while (x < v[N-1] && N > 0){
		v[N] = v[N-1];
		N--;
	}
	v[N]=x;
}



//27
void merge(int r [], int a[], int b[], int na, int nb){
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
	while (i < na){
		r[k] = a[i];
		i++; k++;
	}
	while (j < nb){
		r[k] = b[j];
		j++; k++;
	}
}



//28
int crescente(int a[], int i, int j){
	int k;
	for (k=i; k<j; k++){
		if (a[k] > a[k+1]) return 0;
	}
	return 1;
}



//29
int retiraNeg(int v[], int N){
	int i, j=0;
	for (i=0; i<N; i++){
		if (v[i] >= 0){
			v[j] = v[i];
			j++;
		}
	}
	return j;
}



//30
int contavezes(int v[], int N, int x){
	int i=0, conta=0;
	while (i<N){
		if (v[i] == x) conta++;
		i++;
	}
	return conta;
}

int menosFreq(int v[], int N){
	int i, min=N;
	char c=v[0];
	for (i=0; i<N; i++){
		if (contavezes(v, N, v[i]) < min){
			min = contavezes(v, N, v[i]);
			c = v[i];
		}
	}
	return c;
}



//31
int maisFreq(int v[], int N){
	int i, max=0;
	char c = v[0];
	for (i=0; i<N; i++){
		if (contavezes(v, N, v[i]) > max){
			max = contavezes(v, N, v[i]);
			c = v[i];
		}
	}
	return c;
}



//32
int maxCresc(int v[], int N){
	int i=0, conta=1, max=1;
	if (N==0) return 0;
	while (i<N){
		while (v[i] <= v[i+1]){
			conta++;
			i++;
		}
		if (conta > max){
			max = conta;
		}
		conta = 1;
		i++;
	}
	return max;
}



//33
int rep(int v[], int n, int x){
	int i;
	for (i=0; i<n; i++){
		if (x==v[i]) return 1;
	}
	return 0;
}

int elimRep(int v[], int n) {
    int i, j;
    for (i=0; i<n; i++) {
        if (rep(v, i, v[i])){
            for (j=i; j<n; j++){
                v[j] = v[j+1];
            } //elimina a 1ª ocorrencia e passa tudo 1 para a esquerda
            n--;
            i--; //voltar ao mesmo indice porque v[i+1] agora está na posição i
        }
    }
    return n;
}



//34
int elimRepOrd(int v[], int n){
	int i, j=0;
	for (i=0; i<n; i++){
		while (v[i] == v[i+1]){
			i++;
		}
		v[j] = v[i];
		j++;
	}
	return j;
}



//35
int comunsOrd(int a[], int na, int b[], int nb){
	int i=0, j=0, r=0;
	while (i<na && j<nb){
		if (a[i] > b[j]){
			j++;
		}
		else if (a[i] < b[j]){
			i++;
		}
		else if (a[i] == b[j]){
			r++; i++; j++;
		}
	}
	return r;
}



//36
int comuns(int a[], int na, int b[], int nb){
	int r=0, i, j;
	for (i=0; i<na; i++){
        for(j=0; j<nb; j++){
            if (a[i] == b[j]){
                r++;
                break;
            }
        }
    }
    return r;
}



//37
int minInd(int v[], int n){
	int i, min=v[0], r=0;
	for (i=0; i<n; i++){
		if (v[i] < min){
			min = v[i];
			r = i;
		}
	}
	return r;
}



//38
void somasAc(int v[], int Ac [], int N){
	Ac[0] = v[0];
	int i;
	for (i=0; i+1<N; i++){
		Ac[i+1] = Ac[i] + v[i+1];
	}
}



//MATRIZES

//39
int triSup(int N, float m [N][N]){
	int l, c, r=1;
	for (l=0; l<N; l++){
		for (c=0; c<N; c++){
			if (l>c){
				if (m[l][c] != 0) r=0;
			}
		}
	}
	return r;
}



//40
void transposta(int N, float m [N][N]){
	int l, c;
	float aux[N][N];
	for (l=0; l<N; l++){
		for (c=0; c<N; c++){
			aux[l][c] = m[c][l];
		}
	}
	for (l=0; l<N; l++){
		for (c=0; c<N; c++){
			m[l][c] = aux[l][c];
		}
	}
}



//41
void addTo(int N, int M, int a [N][M], int b[N][M]){
	int l, c;
	for (l=0; l<N; l++){
		for (c=0; c<M; c++){
			a[l][c] = a[l][c] + b[l][c];
		}
	}
}



//CONJUNTOS DO TIPO {1, 4, 7} = {0,1,0,0,1,0,0,1,...}

//42
int unionSet(int N, int v1[N], int v2[N], int r[N]){
	int i, res=0;
	for (i=0; i<N; i++){
		if (v1[i] == 1 || v2[i] == 1){
			r[i]=1;
			res=1;
		}
	}
	return res;
}



//43
int intersectSet(int N, int v1[N], int v2[N], int r[N]){
	int i, res=0;
	for (i=0; i<N; i++){
		if (v1[i] == 1 && v2[i] == 1){
			r[i]=1;
			res=1;
		}
	}
	return res;
}



//CONJUNTOS DO TIPO {1, 1, 4, 7, 7, 7} = {0,2,0,0,1,0,0,3,...}

//44
int intersectMSet(int N, int v1[N], int v2[N], int r[N]){
	int i, res=0;
	for (i=0; i<N; i++){
		if (v1[i] > v2[i]) r[i]=v2[i];
		else r[i] = v1[i];
		res=1;
	}
	return res;
}



//45
int unionMSet(int N, int v1[N], int v2[N], int r[N]){
	int i, res=0;
	for (i=0; i<N; i++){
		if (v1[i] > v2[i]) r[i]=v1[i];
		else r[i] = v2[i];
		res=1;
	}
	return res;
}



//46
int cardinalMSet(int N, int v[N]){
	int i, r=0;
	for (i=0; i<N; i++){
		r = r + v[i];
	}
	return r;
}



typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;
typedef struct posicao{
	int x, y;
} Posicao;

//47
Posicao posFinal(Posicao inicial, Movimento mov[], int N){
	int i;
	for (i=0; i<N; i++){
		if (mov[i] == Norte) inicial.y++;
		else if (mov[i] == Sul) inicial.y--;
		else if (mov[i] == Oeste) inicial.x--;
		else inicial.x++;
	}
	return inicial;
}



//48
int caminho(Posicao inicial, Posicao final, Movimento mov[], int N){
	int r=0, i;
	for (i=0; inicial.x != final.x || inicial.y != final.y; i++){
		if (inicial.y > final.y){
			mov[i] = Sul;
			inicial.y--;
		}
		else if (inicial.y < final.y){
			mov[i] = Norte;
			inicial.y++;
		}
		else if (inicial.x > final.x){
			mov[i] = Oeste;
			inicial.x--;
		}
		else if (inicial.x < final.x){
			mov[i] = Este;
			inicial.x++;
		}
		r++;
	}
	if (r>N) r=-1;
	return r;
}



//49
int distancia(Posicao p){
	return (abs(p.x) + abs(p.y));
}

int maisCentral(Posicao pos[], int N){
	int i, r=0, min = distancia(pos[0]);
	for (i=0; i<N; i++){
		if (distancia(pos[i]) < min){
			min = distancia(pos[i]);
			r=i;
		}
	}
	return r;
}



//50
int vizinhos(Posicao p, Posicao pos[], int N){
	int i, r=0;
	for (i=0; i<N; i++){
		if ((pos[i].x == p.x+1) && (pos[i].y == p.y)) r++;
		else if ((pos[i].x == p.x-1) && (pos[i].y == p.y)) r++;
		else if ((pos[i].y == p.y+1) && (pos[i].x == p.x)) r++;
		else if ((pos[i].y == p.y-1) && (pos[i].x == p.x)) r++;
	}
	return r;
}