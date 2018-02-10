/**********************
  Arduino-like project with setup() & loop(). 
  read/write text to SD card via FatFS and bitbanging ->
  slow (meas. 27kB/s), but requires no dedicated SPI. 
  Notes:
    - SD cards generally use 3.3V -> check schematics
    - pin macros are required in 'config.h'
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1.h"           // UART1 communication
#include "putchar.h"         // for printf()
#include "ff.h"              // SD card with FatFS file system


/*----------------------------------------------------------
    GLOBALS
----------------------------------------------------------*/

FATFS    FatFs;  /* FatFs work area needed for each volume */
FIL      Fil;    /* File object needed for each open file */


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
  uint32_t start, stop, count, size;
	uint8_t  c;
  
  // for FatFS
  FRESULT  err;    /* FatFs function return codes */
	UINT     bw;     /* buffer size */

	// mount SD card
  printf("mount SD card\n");
	err = f_mount(&FatFs, "", 0);
  if (err) f_print_error(err,1);
  

  // create new file
  printf("create file 'newfile.txt'\n");
	err = f_open(&Fil, "newfile.txt", FA_WRITE | FA_CREATE_ALWAYS);
  if (err) f_print_error(err,1);

  // print message
  printf("\nstart write ... ");

	// write some data for speed test
	size = 0;
	start = millis();
	for (count=0; size<1L*1024L; count++) {
		err = f_write(&Fil, "Hello world!\r\n", 14, &bw);
    if (err) f_print_error(err,1);
		size += bw;
	}
	stop = millis();
	
  // print message
  printf("done, wrote %ld bytes in %ldms\n", (long) size, (long) (stop-start));
  
  // close file
  printf("close file\n");
  f_close(&Fil);

  
  // open file for read back
  printf("open file 'newfile.txt'\n");
	err = f_open(&Fil, "newfile.txt", FA_READ);
  if (err) f_print_error(err,1);

  // print message
  printf("\nstart read ... \n");

  // dump beginning of file
  for (size=0; size<20; size++) {
    err = f_read(&Fil,&c,1, &bw);
    if (!err & bw) putchar(c);
  }

  // print message
  printf("\n...done\n\n");

  
  // close file
  printf("close file\n");
  f_close(&Fil);
  
  
	printf("\nTest completed.\n");
	for (;;) ;

} // loop

