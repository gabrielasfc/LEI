%i O João é filho do José
filho(joao,jose).

%ii O José é filho do Manuel; 
filho(jose,manuel).

%iii O Carlos é filho do José;
filho(carlos,jose).

%iv O Paulo é pai do Filipe;
pai(paulo,filipe).

%v O Paulo é pai da Maria;
pai(paulo,maria).

%vi O António é avô da Nádia;
avo(antonio,nadia).

%vii O Nuno é neto da Ana;
neto(nuno,ana).

%viii O João é do sexo masculino;
masc(joao).

%ix O José é do sexo masculino;
masc(jose).

%x A Maria é do sexo feminino;
fem(maria).

%xi A Joana é do sexo feminino;
fem(joana).

%xii Construir a extensão de um predicado capaz de determinar que o indivíduo P é pai do indivíduo F se existir uma prova de que F seja filho de P;
pai(P,F) :- filho(F,P).

%xiii Construir a extensão de um predicado capaz de determinar que o indivíduo A é avô de N se existir um indivíduo X de quem N seja filho e de quem A seja pai;
avo(A,N) :- filho(N,X) , pai(A,X).

%xiv Construir a extensão de um predicado capaz de determinar que o indivíduo N é neto do indivíduo A se existir uma prova de que A seja avô de N;
neto(N,A) :- avo(A,N).

%xv Construir a extensão de um predicado que permita determinar se uma pessoa X descende de outra pessoa Y;
is_desc(X,Y) :- filho(X,Y) ; (pai(Z,X) , is_desc(Z,Y)).

%xvi Construir a extensão de um predicado que permita determinar o grau de descendência entre duas pessoas, X e Y;
desc(X,Y,1) :- filho(X,Y).
desc(X,Y,G) :- pai(Z,X) , desc(Z,Y,N) , G is N+1.

%xvii Construir a extensão de um predicado capaz de determinar se o indivíduo A é avô de N pela utilização do predicado que determina o grau de descendência entre dois indivíduos;
avo_desc(A,N) :- desc(N,A,2).

%xviii Construir a extensão de um predicado capaz de determinar se o indivíduo X é bisavô de Y;
bisavo(X,Y) :- desc(Y,X,3).

%xix Construir a extensão de um predicado capaz de determinar se o indivíduo X é trisavô de Y;
trisavo(X,Y) :- desc(Y,X,4).

%xx Construir a extensão de um predicado capaz de determinar se o indivíduo X é tetraneto de Y.
tetraneto(X,Y) :- desc(X,Y,5).
