%% CALCULAR INTEGRAIS POR TRAPZ
clear all

%valores da tabela
a1 = [1 2 3];
b1 = [3 4 5];

area1 = trapz(a1,b1)


a = 1; b = 9;

%calcula com espaçamento 'e'
e = 0.1; % usando um conjunto de pontos com espaçamento 0.1
x = a : e : b;
y = cos(3.*x+1).*x.^2+x.^1.5;
area = trapz(x,y)


%calculando usando 'n' pontos (equivale a 'n-1' subintervalos)
n = 21;
h = (b-a)/(n-1);
x2 = a : h : b;
y2 = cos(3.*x2+1).*x2.^2+x2.^1.5;
area2 = trapz(x2,y2)