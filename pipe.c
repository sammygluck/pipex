#include <stdio.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[1024];

    // create pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    // fork first child
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // child 1 writes to pipe
        close(pipe_fd[0]); // close read end
        dup2(pipe_fd[1], STDOUT_FILENO); // redirect stdout to pipe write end
        execlp("ls", "ls", "-l", NULL); // execute "ls -l" command
        perror("execlp");
        return 1;
    }

    // fork second child
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // child 2 reads from pipe
        close(pipe_fd[1]); // close write end
        dup2(pipe_fd[0], STDIN_FILENO); // redirect stdin to pipe read end
        execlp("wc", "wc", "-l", NULL); // execute "wc -l" command
        perror("execlp");
        return 1;
    }

    // parent process
    close(pipe_fd[0]); // close read end
    close(pipe_fd[1]); // close write end
    wait(NULL); // wait for child processes to finish
    wait(NULL);

    return 0;
}
