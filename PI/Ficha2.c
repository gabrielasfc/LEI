//Codeboard: https://codeboard.io/projects/222346

#include <stdio.h>
#include <stdlib.h>

//1
float multInt1(int n, float m){
    float r = 0;
    int i;
    for (i=0; i<n; i++) r += m;
    return r;
}


//2
float multInt2(int n, float m){
    float sum = 0;
    for (; n>0; n = n/2){
        if (n%2 != 0) sum += m;
        m *= 2;
    }
    return sum;
}


//3
int mdc(int a, int b){
    int i;
    if (b < a){
        int c = a;
        a = b;
        b = c;
    }
    for (i=a; a>0; i--){
        if (a%i == 0 && b%i == 0) return i;
    }
}


//4
int mdc2(int a, int b){
    while (a != b){
        if (a > b) a -= b;
        if (b > a) b -= a; 
    }
    return a;
}


//5
int mdc3(int a, int b){
    while (a != b){
        if (a > b) a %= b;
        if (b > a) b %= a; 
    }
    return a;
}


//6
//a
int fib1(int n){
    if(n == 0) return 0;
    else if (n == 1) return 1;
    else return (fib1(n-1) + fib1(n-2));
}


//b
int fib2(int n){
    int i, x=1, y=1, aux;
    for (i=2; i<n; i++){
        aux = y;
        y = x;
        x = aux + y;
    }
    return x;
}