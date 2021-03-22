#include <stdio.h>
#include <assert.h>

int main () {
    int x, dez, uni;
    int m[10][10] = {0};
    int d, u;
    x=0;
    while (x != -1) {
        assert((scanf("%d", &x)) == 1);
        dez = x / 10;
        uni = x % 10;
        m[dez][uni]++;
    }
    for (d = 0; d <= 9; d++) {
        printf("%d|", d);
        for (u = 0; u <= 9; u++) {
            while (m[d][u] != 0) {
                printf("%d", u);
                m[d][u]--;
            }
        }
        putchar('\n');
    }
    return 0;
}