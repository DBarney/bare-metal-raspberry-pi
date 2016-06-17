#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);

// loads a file from disk and echos it out to stdout prefixed with its length
int main (int argc, char **argv)
{
    if (argc != 2)
    {
      fprintf(stderr, "USAGE: %s <path of file to send>\r\n",argv[0]);
    }
    struct stat info;
    if (stat(argv[1], &info) == -1 )
    {
      fprintf(stderr, "unable to stat file %s\r\n", argv[1]);
      return -1;
    }

    int sz = info.st_size +1;
    write(1, (void*)&sz, sizeof(sz));
    char c = getchar();
    if (c != 'y') {
      fprintf(stderr, "---- kernel wasn't accepted %c\r\n",c);
      return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "unable to open file\r\n");
        return -1;
    }
    char buf[1024];
    int buflen;
    while((buflen = read(fd, buf, 1024)) > 0)
    {
        write(1, buf, buflen);
    }
    close(fd);
    return(0);
}
//exec !! load /Users/danielbarney/Projects/Personal/pi/raspberrypi/boards/pizero/sensorCheck/echo.bin
