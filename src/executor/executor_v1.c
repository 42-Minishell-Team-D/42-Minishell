/*int main()
{
	int pipes[PROCESS_NUM + 1][2];
	int pid;
	
	pipe(pipes[0]);
	pipe(pipes[1]);

	write(pipes[0][1], "Hello\n", 6);

	pid = fork();

	if (pid == 0)
	{
		// Child Process
		char	readbuffer[80];
		bzero(readbuffer, 80);
		read(pipes[0][0], readbuffer, 6);
		printf("Child Process: %s", readbuffer);
		readbuffer[3] = '\0';
		write(pipes[1][1], readbuffer, 6);
		return (0);
	}
	wait(NULL);
	char read_something[80];
	read(pipes[1][0], read_something, 6);
	printf("Parent Process: '%s'\n", read_something);
	return (0);
}*/

/*
Pipe example
int main(int argc, char *argv[])
{
	int pipes[2][2];

	pipe(pipes[0]);
	pipe(pipes[1]);

	pid_t pid = fork();
	if (pid == 0) {
		// Create a child executing the command "echo hi"
		dup2(pipes[1][1], 1);	// Redirect stdout to pipe
		dup2(pipes[0][0], 0); 	// Redirect stdin to pipe
		char	*args[] = {"/bin/echo",  "hi", NULL}; // Arguments to execve
		execve("/bin/echo", args, NULL); // Execute the command
		return (0); // This line should never be reached
	}
	wait(NULL); // Wait for the child to finish
	char *buf = malloc(1024); // Allocate a buffer
	read(pipes[1][0], buf, 1024); // Read the output of the child
	write(1, buf, strlen(buf)); // Print the output of the child

	return (0);
}
*/

/*
Source code from Codevault video https://code-vault.net/lesson/v5cml4fg0w:1610639843712
int main(int argc, char* argv[]) {
    int pids[PROCESS_NUM];
    int pipes[PROCESS_NUM + 1][2];
    int i;
    for (i = 0; i < PROCESS_NUM + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    for (i = 0; i < PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        if (pids[i] == 0) {
            // Child process
            int j;
            for (j = 0; j < PROCESS_NUM + 1; j++) {
                if (i != j) {
                    close(pipes[j][0]);
                }
                if (i + 1 != j) {
                    close(pipes[j][1]);
                }
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) {
                printf("Error at reading\n");
                return 3;
            }
            printf("(%d) Got %d\n", i, x);
            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) {
                printf("Error at writing\n");
                return 4;
            }
            printf("(%d) Sent %d\n", i, x);
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            return 0;
        }
    }

    // Main process
    int j;
    for (j = 0; j < PROCESS_NUM + 1; j++) {
        if (j != PROCESS_NUM) {
            close(pipes[j][0]);
        }
        if (j != 0) {
            close(pipes[j][1]);
        }
    }
    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1) {
        printf("Error at writing\n");
        return 4;
    }
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) {
        printf("Error at reading\n");
        return 3;
    }
    printf("The final result is %d\n", y);
    close(pipes[0][1]);
    close(pipes[PROCESS_NUM][0]);

    for (i = 0; i < PROCESS_NUM; i++) {
        wait(NULL);
    }
    return 0;
}
*/