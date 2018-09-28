#include <unistd.h>
#include <fcntl.h>

void toggle_endianess(int *n)
{
    char *tmp;
    char i;

    tmp = (char *)n;
    i = tmp[0];
    tmp[0] = tmp[3];
    tmp[3] = i;
    i = tmp[1];
    tmp[1] = tmp[2];
    tmp[2] = i;
}

int main(int argc, char const *argv[])
{
    int fd;
    int toto;
    int padding;

    padding = 0;
    fd = open(argv[1], O_WRONLY | O_CREAT);
    toto = 0x01020304;
    write(fd, &toto, sizeof(int));
    write(fd, &padding, sizeof(int));
    write(fd, &padding, sizeof(int));
    write(fd, &padding, sizeof(int));
    toggle_endianess(&toto);    
    write(fd, &toto, sizeof(int));
    write(fd, &padding, sizeof(int));
    write(fd, &padding, sizeof(int));
    write(fd, &padding, sizeof(int));
    close(fd);
    return 0;
}