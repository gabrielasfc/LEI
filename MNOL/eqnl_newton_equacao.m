%% MÉTODO DE NEWTON (EQUAÇOES)
clear all

%criterio de paragem e aproximaçao inicial
paragem = 1e-3;
aprox_inic = 6;

%opts para paragem
opt1 = optimset('Display', 'iter', 'tolfun', paragem); %ver iteraçoes 
opt = optimset('tolfun', paragem);

%x - soluçao, fval - valor do x na função, exitflag - convergência, output - iterações
% fsolve(funcao, aproximaçao inicial, opt)
[x, fval, exitflag, output] = fsolve(@func, aprox_inic, opt)

%exitflag > 0 - convergiu para uma soluçao X
%exitflag = 0 - indica que atingiu o maxIter ou maxFunEvals
%exitflag < 0 - indica que não convergiu para uma solução

function f = func(x)
f = 7*(2-0.9^(x))-10;
end
