/**********************
  Arduino-like project with setup() & loop(). 
  read/write text to SD card via PetitFS and bitbanging ->
  slow (meas. 27kB/s), but requires no dedicated SPI. 
  Notes:
    - SD cards generally use 3.3V -> check schematics
    - PetitFS can only change file content, not create or extend. For this use FatFS
    - pin macros are required in 'config.h'
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "pff.h"             // SD card with petit file system


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// access LED pin (=PH3). See gpio.h
#define LED   pinOutputReg(&PORT_H, pin3)


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/* Stop with dying message: rc = FatFs return value */
void die (FRESULT rc) {

	// print error message
	printf("PetitFS failed with return code %u ", rc);
  if (rc == 0)
	  printf("(OK)\n");
	else if (rc == 1)
	  printf("(DISK_ERR)\n");
	else if (rc == 2)
	  printf("(NOT_READY)\n");
	else if (rc == 3)
	  printf("(NO_FILE)\n");
	else if (rc == 4)
	  printf("(NOT_OPENED)\n");
	else if (rc == 5)
	  printf("(NOT_ENABLED)\n");
	else if (rc == 6)
	  printf("(NO_FILESYSTEM)\n");
	else
	  printf("(unknown)\n");
	
	// wait forever
	while(1);
	
} // die



//////////
// user setup, called once after reset
//////////
void setup() {

  // configure LED pin
  pinMode(&PORT_H, 3, OUTPUT);

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // wait for terminal to launch
  delay(1000);
  
} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // for performance measurement
  uint32_t start, stop, size;
  
  // for PetitFS
  FATFS fatfs;     // File system object
  DIR dir;         // Directory object
  FILINFO fno;     // File information object
  UINT bw=0, br=0, i=0;
  BYTE buff[64], rc=0;

  // avoid compiler warnings
	UNUSED(fno);
	UNUSED(dir);
	UNUSED(bw);
	
	printf("\nMount a volume.\n");
	rc = pf_mount(&fatfs);
	if (rc) die(rc);

  #if _USE_READ
	  printf("\nOpen a test file (message.txt).\n");
	  rc = pf_open("MESSAGE.TXT");
	  if (rc) die(rc);

	  printf("\nType the file content.\n");
	  for (;;) {
		  rc = pf_read(buff, sizeof(buff), &br);	/* Read a chunk of file */
		  if (rc || !br) break;			/* Error or end of file */
		  for (i = 0; i < br; i++)		/* Type the data */
			  putchar(buff[i]);
	  }
	  if (rc) die(rc);
  #endif

  #if _USE_WRITE
	  printf("\nOpen a file to write (write.txt).\n");
	  rc = pf_open("WRITE.TXT");
	  if (rc) die(rc);

	  printf("\nWrite a text data. (Hello world!)\n");
	  size = 0;
	  start = millis();
	  for (;;) {
		  rc = pf_write("Hello world!\r\n", 14, &bw);
		  if (rc || !bw) break;
		  size += 14;
	  }
	  if (rc) die(rc);
    stop = millis();
	
	  printf("\nTerminate the file write process (%ld bytes in %ldms).\n", (long) size, (long) (stop-start));
	  rc = pf_write(0, 0, &bw);
	  if (rc) die(rc);
  #endif

  #if _USE_DIR
	  printf("\nOpen root directory.\n");
	  rc = pf_opendir(&dir, "");
	  if (rc) die(rc);

	  printf("\nDirectory listing...\n");
	  for (;;) {
		  rc = pf_readdir(&dir, &fno);	/* Read a directory item */
		  if (rc || !fno.fname[0]) break;	/* Error or end of dir */
		  if (fno.fattrib & AM_DIR)
			  printf("   <dir>  %s\n", fno.fname);
		  else
			  printf("%8lu  %s\n", fno.fsize, fno.fname);
	  }
	  if (rc) die(rc);
  #endif

	printf("\nTest completed.\n");
	for (;;) ;

} // loop

