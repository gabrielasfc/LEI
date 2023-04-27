%FMINSEARCH - METODO DE NELDER-MEAD %

%exitflag
% 1 - convergiu para a solução x
% 0 - nº de iterações excedeu o MaxIter ou o MaxFunEvals
% -1 - não convergiu para uma solução

% tolfun - tolerancia de paragem relativamente à funçao objetivo
% tolx - tolerancia de paragem relativamente a x

%QUANDO A FUNÇÃO É MAX ENTRE + DE 2 NUMEROS
% function [f] = fun(x)
% u = [(x(1)-1)^2 , x(2)^2+x(1) , 4*(x(2)-1)^2];
% f = max(u);
%end

op = optimset('Display', 'iter'); %para ver resultados obtidos em cada iteração
op1 = optimset('TolX', 1e-10); %usar tolerancia de paragem TolX
op2 = optimset('TolFun', 1e-12); %usar tolerancia de paragem TolFun
op3 = optimset('MaxIter', 20); %usa tolerancia de paragem de 20 iterações

m = [1 1]; %matriz do enunciado

[x, fval, exitflag, output] = fminsearch (@fun, m, op)

%função objetivo a minimizar
function [f] = fun (x)
    f = max (abs(x(1)), abs(x(2)-1));
end
