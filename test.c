#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd, value;
    fd = open("/dev/randnumber", O_RDONLY);
    if (fd < 0){
        perror("failed to open module");
        return -1;
    }
    read(fd, &value, sizeof(value));
    printf("Random number: %d\n", value);
    return 0;
}
