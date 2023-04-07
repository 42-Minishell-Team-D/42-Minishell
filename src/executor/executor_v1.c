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