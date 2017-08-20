#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//strerror
#include <errno.h>

#define FIFO_NAME "/tmp/fifo"
#define FIFO_BUFF 12

int main(int argc, char const *argv[])
{
	char buffer[FIFO_BUFF];
	int pipd_fd;
	int size = sizeof(buffer);
	
	if ((pipd_fd=open(FIFO_NAME,O_RDWR))!=-1)
	{
		read(pipd_fd,(void *)buffer,size);
		printf("%s\n", buffer);
	}
	else
	{
		fprintf(stderr, "open:%s\n", strerror(errno));
		exit(1);
	}
	return 0;
}