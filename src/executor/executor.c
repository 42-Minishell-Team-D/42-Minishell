#include "../../libs/minishell.h"

// open, close, read, write,
// malloc, free, perror,
// strerror, access, dup, dup2,
// execve, exit, fork, pipe,
// unlink, wait, waitpid

void    executor(t_data *data)
{
    // This simulate pipe redirection // still not writing in a file
    
    int read_fd_3 = open("tmp.txt", O_RDONLY | O_CREAT, 0777);  // create a file descriptor 3
    if (read_fd_3 == -1)
        perror("open");
    int write_fd_4 = open("tmp.txt", O_WRONLY | O_CREAT, 0777);  // create a file descriptor 4
    if (write_fd_4 == -1)
        perror("open");

    // unsure how to redirect the output to a file
    
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)  // create a pipe and store the file descriptors in pipe.fd[0] and pipe.fd[1]
        return ;

    int pid1 = fork();
    if (pid1 < 0)
        perror("fork");

    if (pid1 == 0) // check if we are in the child process
    {
        dup2(pipe_fd[1], STDOUT_FILENO);  // redirect the output of the child process to the pipe
        close(pipe_fd[0]);  // close the read end of the pipe
        close(pipe_fd[1]);  // close the write end of the pipe    // fd[1] remains open in the parent process
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }

    int pid2 = fork();
    if (pid2 < 0)
        perror("fork");
        
    if (pid2 == 0) // check if we are in the child process
    {
        dup2(pipe_fd[0], STDIN_FILENO);  // redirect the input of the child process to the pipe
        close(pipe_fd[0]);  // close the read end of the pipe
        close(pipe_fd[1]);  // close the write end of the pipe    // fd[0] remains open in the parent process
        execlp("grep", "grep", "rtt", NULL);
        // write the output of the child process to the file descriptor 4
    }

    close(pipe_fd[0]);  // close the read end of the parent process
    close(pipe_fd[1]);  // close the write end of the parent process

    waitpid(pid1, NULL, 0);  // wait for the child process to finish
    waitpid(pid2, NULL, 0);  // wait for the child process to finish

    (void)data;
    data = NULL;
}
