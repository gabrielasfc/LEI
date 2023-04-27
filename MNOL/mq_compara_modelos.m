%% COMPARA MODELOS
clear all

x = [1.5 2.0 3.0 4.0];
f = [4.9 3.3 2.0 1.5];

% RETA (GRAU POL = 1)
[P1, S1] = polyfit(x, f, 1)
sqr1 = S1.normr^2

% PARABOLA (GRAU POL = 2)
[P2, S2] = polyfit(x, f, 2)
sqr2 = S2.normr^2 %dá a soma do quadrados do resíduos - erro

% MODELO NAO POLINOMIAL
ap = [1 1];
[c, RESNORM] = lsqcurvefit(@func, ap, x, f)

%funcao
function [m] = func(c, x)
m = c(1)./x+c(2).*x;
end