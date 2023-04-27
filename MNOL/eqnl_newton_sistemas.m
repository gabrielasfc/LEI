%% MÉTODO DE NEWTON (SISTEMAS)
clear all

%criterio de paragem e aproximaçao inicial
paragem = 1e-8;
x0 = [1 ; 1]

%opts para paragem
opt1 = optimset('Display', 'iter', 'tolfun', paragem); %ver iteraçoes
opt = optimset('tolfun', paragem);


%x - resultado, fval - valor do x na função, exitflag - convergência, output - iterações
% fsolve(funcao, intervalo, opt)
[x, fval, exitflag, output] = fsolve(@func, x0, opt)

%exitflag > 0 - convergiu para uma soluçao X
%exitflag = 0 - indica que atingiu o maxIter ou maxFunEvals
%exitflag < 0 - indica que não convergiu para uma solução

function [f] = func(x)
%%inserir funções do sistema
f(1) = (x(1)^6 - x(2)^3 - 0.5) * exp(-x(1)^2- x(2)^2);
f(2) = 20 * (x(1)^2 - x(2)^2) - 12;
end
