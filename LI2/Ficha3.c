#include <stdio.h>
#include <assert.h>

void replicate (int n, char c) {
    int i;
    for (i=0; i<n; i++) putchar (c);
}

int main () {
    int n, l;
    int accast = 1;
    int accponto = 1;

    assert(scanf("%d",&n)==1);
    for (l=0; l<n; l++) {
        replicate (l+1, '*');
        replicate (2*n - 2*(l+1), '.');
        replicate (l+1, '*');
        putchar ('\n');
    }
    for (l=n; l < (2*n - 1); l++) {
        replicate (l - 2*accast + 1, '*');
        replicate (2*n - 2*(l-accponto),'.');
        replicate (l - 2*accast + 1, '*');
        accast = accast + 1;
        accponto = accponto + 2;
        putchar ('\n');
    }
    return 0;
}