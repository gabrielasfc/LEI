%% CALCULAR INTEGRAIS POR INTEGRAL
clear all

%q = integral(fun,lim_inf,lim_sup)
%q = integral(fun,lim_inf,lim_sup,Name,Value)

%para colocar no name se for preciso
%– AbsTol - Tolerancia do erro absoluto (default=1e-10)
%– RelTol - Tolerancia do erro relativo (default=1e-6)
%exemplo : I = (@myfun, 1.5, 5, `AbsTol´, 1e-2)

I = integral(@func, 0.1, 2)

function f = func(x)
f = log(x) ./ (x + 4);
end
