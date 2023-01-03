%Exercicio 1

%aluno(nr,nome,sexo)
aluno(1,joao,m).
aluno(2,antonio,m).
aluno(3,carlos,m).
aluno(4,luisa,f).
aluno(5,maria,f).
aluno(6,isabel,f).

%curso(cod,sigla)
curso(1,lei).
curso(2,miei).
curso(3,lcc).

%disciplina(cod, sigla, ano, curso)
disciplina(1,ed,2,1).
disciplina(2,ia,3,1).
disciplina(3,fp,1,2).

%inscrito(nr aluno, cod disciplina)
inscrito(1,1).
inscrito(1,2).
inscrito(5,3).
inscrito(5,5).
inscrito(2,5).

%nota(nr aluno, cod disciplina, nota)
nota(1,1,15).
nota(1,2,16).
nota(1,5,20).
nota(2,5,10).
nota(3,5,8).
nota(5,3,8). % para testar media acima/abaixo

%copia
copia(1,2).
copia(2,3).
copia(3,4).


%i
naoInscrito(NR) :- aluno(NR,_,_) , \+(inscrito(NR,_)).
naoInscritos(R) :- findall(NR, naoInscrito(NR), R).

%ii
naoInscrito2(NR) :- (aluno(NR,_,_) , \+(inscrito(NR,_))) ; (inscrito(NR,D) , \+(disciplina(D,_,_,_))). 
naoInscritos2(R) :- findall(NR, naoInscrito2(NR), R).

%iii
notaAluno(NR,D,NOTA) :- aluno(NR,_,_) , inscrito(NR,D) , disciplina(D,_,_,_) , nota(NR,D,NOTA).
notasAluno(NR, R) :- findall(NOTA, notaAluno(NR,_,NOTA) , R).
media(NR,R) :- notasAluno(NR,L) , sum_list(L, S) , length(L,LEN) , R is S/LEN.

%iv
mediaGlobal(R) :- findall(N, notaAluno(_,_,N), L), length(L,LEN) , sum_list(L,S) , R is S/LEN.
alunoAcima(NR) :- mediaGlobal(G) , notaAluno(NR,_,_) , media(NR,M) , M>G , !.
alunosAcima(R) :- findall(NR, alunoAcima(NR), R).
alunoAbaixo(NR) :- mediaGlobal(G) , notaAluno(NR,_,_) , media(NR,M) , M<G.
alunosAbaixo(R) :- findall(NR, alunoAbaixo(NR), R).

%v
nomeCopiao(NR,NOME) :- aluno(NR,NOME,_) , copia(NR, _).
nomesCopioes(R) :- findall(NOME , nomeCopiao(_,NOME), R).

%vi
copiouPor(NR,NOME_COPIAO) :- aluno(NR,_,_) , aluno(NR_COPIAO,NOME_COPIAO,_) , copia(NR_COPIAO,NR).
copiaramPor(NR, R) :- findall(NOME, copiouPor(NR, NOME), R).

%vii
nrToNome(NR,R) :- aluno(NR,R,_).
mapToNome([],[]).
mapToNome([NR|T],R) :- mapToNome(T,R1) , nrToNome(NR,NOME) , R=[NOME|R1] , !.
mapToNome([NR|T],R) :- \+(aluno(NR,_,_)) , mapToNome(T,R).