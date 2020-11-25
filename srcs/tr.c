# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
#include <assert.h>
/*
int main() {
    printf("Hello from initial pid %d\n", getpid());

    pid_t p1 = fork();
    assert(p1 >= 0);

    pid_t p2 = fork();
    assert(p2 >= 0);

    printf("Hello from final pid %d\n", getpid());
}
*/
int main() {
    int pfd[2];
    int r = pipe(pfd);
    assert(r == 0);

    char wbuf[BUFSIZ];
    sprintf(wbuf, "Hello from pid %d\n", getpid());

    ssize_t n = write(pfd[1], wbuf, strlen(wbuf));
    assert(n == (ssize_t) strlen(wbuf));

    char rbuf[BUFSIZ];
    n = read(pfd[0], rbuf, BUFSIZ);
    assert(n >= 0);
    rbuf[n] = 0;

    assert(strcmp(wbuf, rbuf) == 0);
    printf("Wrote %s", wbuf);
    printf("Read %s", rbuf);
}