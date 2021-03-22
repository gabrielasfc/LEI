#include <stdio.h>
#include <assert.h>

int main() {
    int a, b, c;
    assert (scanf("%d %d", &a, &b) == 2);
    c = a*a + b*b;
    printf("%d\n", c);
    return 0;
}
