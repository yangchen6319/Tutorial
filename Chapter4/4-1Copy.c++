#include <sys/stat.h>
#include <fcntl.h>
#include "MathFunctions.h"

#ifndef BUF_SIZE 
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]){
    char buf[BUF_SIZE];
    int inputFd, outputFd, flags;
    mode_t fileParams;
    ssize_t numRead;
    if (argc != 3) usageErr("%s old-file new-file\n", argv[0]);
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) errExit("open file %s", argv[1]);
    flags = O_CREAT | O_WRONLY | O_TRUNC;
    fileParams = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    outputFd = open(argv[2], flags, fileParams);
    if (outputFd == -1) errExit("open file %s", argv[2]);
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
    {
        if (write(outputFd, buf, BUF_SIZE) != numRead) fatal("couldn't write all buffer");
    }
    if (numRead == -1) errExit("read");
    if (close(inputFd) == -1) errExit("close %s fail", argv[1]);
    if (close(outputFd) == -1) errExit("close %s fail", argv[2]);
    
    exit(EXIT_SUCCESS);
}