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