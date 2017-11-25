#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
 
int main(){
    int fd;
    //char path[10];
    struct termios options;
	
    /* ################# Open the port #################*/

    printf("Enter com_port path\n sorry not now\n");
//    scanf("%c",&path);
    fd = open("/dev/pts/2", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	   {                                              /* Could not open the port */
	     fprintf(stderr, "open_port: Unable to open /dev/pts/6 - %s\n",strerror(errno));
	   }else{
		printf("port opened\n");
	    }

    fcntl(fd, F_SETFL, 0);
 
    /* ################ Get the current options ###############*/

    tcgetattr(fd, &options);
 
    /*############## set raw input, 1 second timeout */

    options.c_cflag     |= (CLOCAL | CREAD);
    options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag     &= ~OPOST;
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 10;
 
    /*################### set the options ##################*/

    tcsetattr(fd, TCSANOW, &options);
 
	char buffer[400];  /* Input buffer */
      char *bufptr;      /* Current char in buffer */
      int  nbytes;       /* Number of bytes read */
      int  tries;        /* Number of tries so far */
 
      for (tries = 0; tries < 1; tries ++)
      {
       /* send an AT command*/
	if (write(fd, "AT+CMGL=\"ALL\"\n", strlen("AT+CMGL=\"ALL\"\n")) < 3){
		printf("command sent\n");
	  continue;
	//	if(write(fd, "AT+CMGL=\"ALL\"\r", strlen("AT+CMGL=\"ALL\"\r"))=="clc")
	//	goto loop;
	
	}

	
 
       /*################## Read characters into our string buffer ################*/

	bufptr = buffer;
 
	nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1);
	printf("%s\n",bufptr);
 
    char *p;
 
    p = strstr(buffer, "tin");
    printf("%s",p);
 
	p = strstr(buffer, "server");
	if(p == NULL) printf("not from server\n");
 	*bufptr = '\0';
//loop: close(fd);
 }

close(fd);
	return 0;
}
 


