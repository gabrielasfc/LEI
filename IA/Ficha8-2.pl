%Exercicio 2

%biblioteca(id, nome, localidade)
biblioteca(1, uminhogeral, braga).
biblioteca(2, luciocracveiro, braga).
biblioteca(3, municipal, porto).
biblioteca(4, publica, viana).
biblioteca(5, ajuda, lisboa).
biblioteca(6, cidade, coimbra).


%livros( id, nome, biblioteca)
livros(1, gameofthrones, 1). 
livros(2, codigodavinci, 2).
livros(3, setimoselo, 1).
livros(4, fireblood, 4).
livros(5, harrypotter, 6).
livros(6, senhoradosneis, 7).
livros(7, oalgoritmomestre, 9).

%leitores(id, nome, genero)
leitores(1, pedro, m).
leitores(2, joao, m).
leitores(3, lucia, f).
leitores(4, sofia, f).
leitores(5, patricia, f).
leitores(6, diana, f).

%requisicoes(id_requisicao,id_leitor, id_livro, data(A,M,D)
requisicoes(1,2,3,data(2022,5,17)).
requisicoes(2,1,2,data(2022,7,10)).
requisicoes(3,1,3,data(2021,11,2)).
requisicoes(4,1,4,data(2022,2,1)).
requisicoes(5,5,3,data(2022,4,23)).
requisicoes(6,4,2,data(2021,3,9)).
requisicoes(7,4,1,data(2022,5,5)).
requisicoes(8,2,6,data(2021,7,18)).
requisicoes(9,5,7,data(2022,4,12)).


%devolucoes(id_requisicao, data(A,M, D))
devolucoes(2, data(2022, 7,26)).
devolucoes(4, data(2022,2,4)).
devolucoes(5, data(2022, 6, 13)).
devolucoes(1, data(2022, 5, 23)).
devolucoes(6, data(2022, 4, 9)).


%i
leitoresFeminino(R) :- findall(_, leitores(_,_,f), L), length(L,R).

%ii
livroDesassociado(ID) :- requisicoes(_,_,ID,_) , livros(ID,_,B) , \+biblioteca(B,_,_).
livrosDesassociados(R) :- findall(ID, livroDesassociado(ID) , R).

%iii
requisicaoBraga(LV,LT) :- livros(LV,_,B) , leitores(LT,_,_) , biblioteca(B,_,braga) , requisicoes(_,LT,LV,_).
requisicoesBraga(R) :- findall((LV,LT), requisicaoBraga(LV,LT), R).

%iv
livroSemRequisicao(ID) :- livros(ID,_,_) , \+requisicoes(_,_,ID,_).
livrosSemRequisicao(R) :- findall(ID, livroSemRequisicao(ID), R).

%v
requisicaoValida(ID,data(A,M,D)) :- livros(ID,_,_) , requisicoes(_,_,ID,data(A,M,D)).
requisicoesEm2022(R) :- findall((ID,data(2022,M,D)), requisicaoValida(ID,data(2022,M,D)), R).

%vi
dataVerao(data(_,M,_)) :- M>6 , M<10.
requisicaoVerao(ID,data(A,M,D)) :- livros(ID,_,_) , requisicoes(_,_,ID,data(A,M,D)) , dataVerao(data(_,M,_)).
requisicoesVerao(R) :- findall((ID,data(A,M,D)), requisicaoVerao(ID,data(A,M,D)), R).