%% SPLINE CUBICA COMPLETA
clear all

%valores da tabela
x = [0.5 1.5 2];
y = [-0.69 0.41 0.69];

%SE NAO FOR DADA AS DERIVADAS NOS EXTREMOS OU A FUNÇAO
%guardar 2 e penultimo pontos para estimar f'0 e f'n
xx = [10 18 27 34];
yy = [20 15 9 10];

f_linha_0 = (20-18)/(10-12);
f_linha_n = (12-10)/(30-34);

%%COM DECLIVES JA DADOS
d0 = 2;
dn = 0.5;

%%ATENÇAO
% se ja nos forem dados os valores das derivadas
% usar x em vez de xx, y em vez de yy
% d0 em vez de f_linha_0 e dn em vez de f_linha_n

s_completa = spline(xx, [f_linha_0 yy f_linha_n]);

%para ver os segmentos da spline:
segmentos = s_completa.coefs

%a primeira linha corresponde aos coeficientes o segmento 1 entre [10,18]
%a segunda linha corresponde aos coeficientes do segmento 2 entre [18,27]
%a terceira linha corresponde aos coeficientes do segmento 3 entre [27,34]

%%ATENÇAO 
%calcular valor da spline para nr
nr = 1;
s_nr = spline(xx, [f_linha_0 yy f_linha_n], nr)

%%ATENÇAO
%determinar valor da spline num vetor de pontos
vet = [1 1.5 2.5 3.5 4.5];
s_vetor = spline(xx, [f_linha_0 yy f_linha_n], vet)
