%% MODELO LINEAR NAO POLINOMIAL
clear all

%valores da tabela
x = [1.5 2.0 3.0 4.0];
f = [4.9 3.3 2.0 1.5];

%aproximação inicial aos parametros
%se houver mais c's acrescentar mais 1's
ap = [1 1];

%determine os coeficientes do modelo
[c, RESNORM] = lsqcurvefit(@func, ap, x, f)

%soma dos quadrados dos resíduos - erro
%RESNORM

%calcular valor do polinomio no ponto x = pt
pt = 2.5;
valor = func(c , pt)

%funcao
function [m] = func(c, x)
m = c(1)./x+c(2).*x;
end