#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *args[] = { "/bin/ls", "-la", NULL };
    char *env[] = { NULL };
    int ret;

    ret = execve(args[0], args, env);
    if (ret == -1) {
        perror("execve");
        return 1;
    }

    return 0;
}

