#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int child;
    
    mkfifo("kprlnb", S_IRUSR | S_IWUSR);

    child = fork();

    if(child > 0){
        char s[1024];
        int fd;

        fd = open("kprlnb", O_RDONLY);
        read(fd, s, sizeof(s));
        printf("%s", s);

        close(fd);
        unlink("kprlnb");
    }
    else if(child == 0){
        int fd;

        fd = open("kprlnb", O_WRONLY);
        write(fd, "MA BFNA2X!\n", 12);

        close(fd);
}

    return 0;
}
