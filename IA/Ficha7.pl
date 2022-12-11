%PARTE I
%i soma de 3 valores
sum(X,Y,Z,R) :- R is X+Y+Z.


%ii soma de um conjunto de valores
sumL([],0).
sumL([H|T],R) :- sumL(T,S) , R is H+S.


%iii maior valor entre 2 valores
max(X,Y,X) :- X>Y , !.
max(_,Y,Y).

%iv maior de um conjunto de valores
aux_max([],Max,Max).
aux_max([H|T],Max,R) :- H>Max , aux_max(T,H,R) , !.
aux_max([H|T],Max,R) :- H=<Max , aux_max(T,Max,R).

maxL([H|T],R) :- aux_max(T,H,R).


%v média aritmética de um conjunto de valores
avg(List, R) :- len(List,L) , sumL(List,S) , R is S/L.


%vi ordenar de modo crescente uma sequência de valores
insert_sorted(X,[],[X]) :- !.
insert_sorted(X,[H|T],R) :- X<H , R=[X,H|T] , !.
insert_sorted(X,[H|T],R) :- insert_sorted(X,T,R1), R=[H|R1].

sortL([],[]) :- !.
sortL([H|T], R) :- sortL(T,R1) , insert_sorted(H,R1,R).
   

%vii caracterizar os números pares
even(X) :- 0 is mod(X,2).

collect_even([],[]).
collect_even([H|T],R) :- even(H) , R=[H|XS] , collect_even(T,XS), !.
collect_even([H|T],R) :- not(even(H)) , collect_even(T,R).



%PARTE II
%viii verifica se um elemento existe dentro de uma lista de elementos
contains(X,[X|_]) :- !.
contains(X,[_|T]) :- contains(X,T).


%ix calcula o número de elementos existentes numa lista
len([],0).
len([_|T],R) :- len(T,L) , R is L+1.


%x calcula a quantidade de elementos diferentes existentes numa lista
count_diffs([],0) :- !.
count_diffs([H|T],R) :- contains(H,T) , count_diffs(T,R) , !.
count_diffs([H|T],R) :- not(contains(H,T)) , count_diffs(T,R1) , R is R1+1.


%xi apaga a primeira ocorrência de um elemento de uma lista
remove(_,[],[]) :- !.
remove(X,[X|T],T) :- !.
remove(X,[H|T],R) :- remove(X,T,R1) , R=[H|R1].


%xii apaga todas as ocorrências de um dado elemento numa lista
remove_all(_,[],[]) :- !.
remove_all(X,[X|T],R) :- remove_all(X,T,R) , !.
remove_all(X,[H|T],R) :- remove_all(X,T,R1) , R=[H|R1].


%xiii insere um elemento numa lista, sem o repetir
add(X,[],[X]) :- !.
add(X,[X|T],[X|T]) :- !.
add(X,[H|T],R) :- add(X,T,R1) , R=[H|R1].


%xiv concatenação dos elementos da lista L1 com os elementos da lista L2
concat([],[],[]) :- !.
concat([],L2,L2) :- !.
concat([H1|T1],L2,R) :- concat(T1,L2,R1) , R=[H1|R1]. 


%xv inverte a ordem dos elementos de uma lista
reverseL([],[]).
reverseL([H|T],R) :- reverseL(T,R1) , concat(R1,[H],R).


%xvi determina se uma lista S é uma sublista de outra lista L
sub_list([],_).
sub_list([H1|T1],[H2|T2]) :- H1==H2 , sub_list(T1,T2) , !.
sub_list([H1|T1],[_|T2]) :- sub_list([H1|T1],T2).