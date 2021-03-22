#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
    int a,b,c;

    assert (scanf("%d %d %d", &a, &b, &c) == 3) {
        //Perimetro
        int p = a+b+c;
        //Area
        float semip = (float) p / 2;
        float area = sqrt(semip * (semip-a) * (semip-b) * (semip-c));

        if (a + b <= c || a + c <= b || b + c <= a)
            printf("INVALIDO\n");
        else {
            if (a == b && a == c) {
                printf("EQUILATERO %d %.2f\n", p, area);}
            else if (a*a == b*b + c*c || b*b == a*a + c*c || c*c == a*a + b*b) {
                printf("RETANGULO %d %.2f\n", p, area);}
            else if (a == b || b == c || a == c) {
                printf("ISOSCELES %d %.2f\n", p, area);}
            else { printf("ESCALENO %d %.2f\n", p, area);}
        }
    }
    return 0;
}
