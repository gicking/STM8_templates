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
#include "uart1.h"           // UART1 communication
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
	
	// mount SD card
	printf("\nMount a volume.\n");
	rc = pf_mount(&fatfs);
	if (rc) pf_print_error(rc,1);

  #if _USE_READ
  
	  // open existing file for read
    printf("\nOpen a test file (message.txt).\n");
	  rc = pf_open("MESSAGE.TXT");
	  if (rc) pf_print_error(rc,1);

	  // dump content to PC
	  printf("\nType the file content.\n");
	  for (;;) {
		  rc = pf_read(buff, sizeof(buff), &br);	/* Read a chunk of file */
		  if (rc || !br) break;			/* Error or end of file */
		  for (i = 0; i < br; i++)		/* Type the data */
			  putchar(buff[i]);
	  }
	  if (rc) pf_print_error(rc,1);
  
  #endif // _USE_READ


  #if _USE_WRITE

	  // open existing file for overwriting (size remains constant!)
	  printf("\nOpen a file to write (write.txt).\n");
	  rc = pf_open("WRITE.TXT");
	  if (rc) pf_print_error(rc,1);

    // print message
    printf("\nstart overwiting ... ");

    // overwrite until filesize reached
	  size = 0;
	  start = millis();
	  for (;;) {
		  rc = pf_write("Hello world!\r\n", 14, &bw);
		  if (rc || !bw) break;
		  size += bw;
	  }
	  stop = millis();
	
    // print message
    printf("done, wrote %ld bytes in %ldms\n", (long) size, (long) (stop-start));
	  
	  // terminate file write process
	  rc = pf_write(0, 0, &bw);
	  if (rc) pf_print_error(rc,1);
	  
  #endif // _USE_WRITE
  

  #if _USE_DIR

	  // get pointer to root directory
	  printf("\nOpen root directory.\n");
	  rc = pf_opendir(&dir, "");
	  if (rc) pf_print_error(rc,1);

	  // list root directory
	  printf("\nDirectory listing...\n");
	  for (;;) {
		  rc = pf_readdir(&dir, &fno);	/* Read a directory item */
		  if (rc || !fno.fname[0]) break;	/* Error or end of dir */
		  if (fno.fattrib & AM_DIR)
			  printf("   <dir>  %s\n", fno.fname);
		  else
			  printf("%8lu  %s\n", fno.fsize, fno.fname);
	  }
	  if (rc) pf_print_error(rc,1);

  #endif // _USE_DIR

	// print message
	printf("\nTest completed.\n");
	for (;;) ;

} // loop

