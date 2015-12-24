#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <mtd/mtd-user.h>
#include <sys/ioctl.h>


#define DATA_OFFSET 20
#define RAWBYTES_LEN 4

int main(int argc, char *argv[])
{
    mtd_info_t mtd_info;           // the MTD structure
    erase_info_t ei;               // the erase block structure
    int m;
    unsigned int rawBytes; //the bytes we want to write
    
    if (argc != 2) {
            printf("Usage: tp0set [0/1]\n");
            return 1;
    }
    
    m = atoi(argv[1]); //convert argument to integer
    if( m == 1) {
        rawBytes = 0x10000000;
	printf("setting TP1 main core\n");         
    }
    else if ( m == 0 ) {
        rawBytes = 0x00000000;
	printf("setting TP0 main core\n");         
    }
    else {
	     printf("only 0 or 1 allowed\n");
	     return 1;
    }
    
    unsigned char read_buf[0x20000] = {0x00};    // empty array for reading 

    int fd = open("/dev/mtd0", O_RDWR); // open the mtd device for reading and 
                                        // writing. Note you want mtd0 not mtdblock0
                                        // also you probably need to open permissions
                                        // to the dev (sudo chmod 777 /dev/mtd0)

    ioctl(fd, MEMGETINFO, &mtd_info);   // get the device info

    // dump it for a sanity check, should match what's in /proc/mtd
    printf("MTD Type: %x\nMTD total size: %x bytes\nMTD erase size: %x bytes\n",
         mtd_info.type, mtd_info.size, mtd_info.erasesize);

    lseek(fd, 0, SEEK_SET);               // go to the first block
    read(fd, read_buf, sizeof(read_buf)); // read and store CFE in read_buf
    memcpy(read_buf + DATA_OFFSET, (unsigned char*)&rawBytes, RAWBYTES_LEN); //write some bytes to CFE
    
    ei.length = mtd_info.erasesize;   //set the erase block size
    for(ei.start = 0; ei.start < mtd_info.size; ei.start += ei.length)
    {
        ioctl(fd, MEMUNLOCK, &ei);
         printf("Eraseing Block %#x\n", ei.start); // show the blocks erasing
                                                  // warning, this might print a lot!
        ioctl(fd, MEMERASE, &ei);
    }

    printf("Writting to /dev/mtd0...\n"); // 
    lseek(fd, 0, SEEK_SET);        // go back to first block's start
    write(fd, read_buf,  sizeof(read_buf)); // write our modified CFE

    close(fd);

    printf("Done!!\n");
    
    return 0;
} 
