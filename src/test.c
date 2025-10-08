#include <signal.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    struct sigaction sa;
    printf("sigaction size: %zu\n", sizeof(sa));
    return 0;
}
