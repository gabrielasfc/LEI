%FMINUNC - METODO QUASI-NEWTON OU 'TRUST-REGION' %

% usar GradObj = 'on' ⇒ Método trust-region -> usa gradiente definido pelo utilizador

%exitflag
% 1 - magnitude do gradiente < tolerancia de otimalidade (OptimalityTolerance)
% 2 - alteração em x < tolerancia TolX
% 3 - alteração na funçao obj < tolerancia TolFun
% 5 - previsto decrescimo na funçao obj < tolerancia TolFun
% 0 - nr de iteraçoes excedeu o MaxIter ou MaxFunEvals
% -1 - funçao não convergiu para uma solução
% -3 - problema parece ser nao limitado

op = optimset('Display', 'iter'); %visualizar resultados obtidos em cada iteraçao
op1 = optimset('TolX', 1e-10, 'TolFun', 1e-12); %usar tolerancia TolX e TolFun
op2 = optimset('hessupdate', 'dfp'); %usar formula de atualizaçao DFP -> por defeito usa BFGS
op3 = optimset('MaxIter', 20); %usar tolerancia de paragem 20 iteraçoes

[x, fval, exitflag, output] = fminunc(@fun, [1 0], op)

%função objetivo a minimizar
function [f] = fun(x)
    f = x(1)^2+x(2)^2-x(1)*x(2);
end
