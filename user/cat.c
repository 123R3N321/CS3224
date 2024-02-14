#include "user.h"

char buf[512];

void cat(int fd) {	//pass in file descriptor, but obviously EVERYTHING is an int
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0)	//xv6 syntax: read(filepath, the buffer to read into, the amount we want to read) and it returns 0, we reached the end
    						//btw, we do have sizeof() function, nice!
    write(1, buf, n);	//Im assuming always pass in a "1" for write command into terminal stdout, then where into, then the amount to write into the buffer
  if(n < 0) {
    printf("cat: read error\n");
    exit();	//interestingly not exit 1, Im assuming it is becase file we read is not fine, but cat itself is fine.
  }
}

int main(int argc, char* argv[]) {
  int fd, i;

  if(argc <= 1) {
    cat(0);	//this is reading from stdin. because fd is 0
    exit();	//terminate the call
  }	

  for(i = 1; i < argc; i++) {
    if((fd = open(argv[i], 0)) < 0) {	//attempt to open the file without writing it?  Seriously this entire part shoulbe be a header, "open file attempt" or something.
      printf("cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);	//ahh, good reminder, always close file
  }
  exit();
}
