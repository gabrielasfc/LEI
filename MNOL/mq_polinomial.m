%% POLINOMIOS
clear all

%grau do polinomio
N = 3;

%valores da tabela
x = [1 3 4 5 9 10 12];
f = [8 10 11 13 18 20 26];

[p,S] = polyfit(x, f, N)

%soma do quadrados do resíduos - erro
sqr = S.normr^2
%normr -> norma dos residuos

%calcular valor do polinomio no ponto x = pt
pt = 2.5;
valor = polyval(p, pt)