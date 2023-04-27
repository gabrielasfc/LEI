%% SPLINE CUBICA NATURAL
clear all

%valores da tabela
x = [10 12 18 27 30 34];
y = [20 18 15 9 12 10];

s_natural = spline(x, y)

%para ver os segmentos da spline:
segmentos = s_natural.coefs

%calcular valor da spline para nr
nr = 29;
s_nr = spline(x, y, nr)

%determinar o valor da spline num vetor de pontos
vet = [1 1.5 2.5 3.5 4.5]; 
s_vetor = spline(x, y, vet)
