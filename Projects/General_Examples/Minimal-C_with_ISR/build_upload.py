#!/usr/bin/python

'''
 Script for building and uploading a STM8 project with dependency auto-detection
'''

# set general options
UPLOAD   = 'SWIM'       # select 'BSL' or 'SWIM'
TERMINAL = False        # set True to open terminal after upload
RESET    = 1            # STM8 reset: 0=skip, 1=manual, 2=DTR line (RS232), 3=send 'Re5eT!' @ 115.2kBaud, 4=Arduino pin 8, 5=Raspi pin 12
OPTIONS  = ''           # e.g. device for SPL ('-DSTM8S105', see stm8s.h)

# set path to root of STM8 templates
ROOT_DIR = '../../../'
LIB_ROOT = ROOT_DIR + 'Library/'
TOOL_DIR = ROOT_DIR + 'Tools/'
OBJDIR   = 'output'
TARGET   = 'main.ihx'

# set OS specific
import platform
if platform.system() == 'Windows':
  PORT         = 'COM10'
  SWIM_PATH    = 'C:/Programme/STMicroelectronics/st_toolset/stvp/'
  SWIM_TOOL    = 'ST-LINK'
  SWIM_NAME    = 'STM8S105x6'  # STM8 Discovery
  #SWIM_NAME    = 'STM8S208xB'  # muBoard
  MAKE_TOOL    = 'mingw32-make.exe'
else:
  PORT         = '/dev/ttyUSB0'
  SWIM_TOOL    = 'stlink'
  SWIM_NAME    = 'stm8s105c6'  # STM8 Discovery
  #SWIM_NAME    = 'stm8s208?b'  # muBoard
  MAKE_TOOL    = 'make'
  
# import required modules
import sys
import os
import platform
import argparse
sys.path.append(TOOL_DIR)
import misc
from buildProject import createMakefile, buildProject
from uploadHex import stm8gal, stm8flash, STVP


##################
# main program
##################

# commandline parameters with defaults
parser = argparse.ArgumentParser(description="compile and upload STM8 project")
parser.add_argument("--skipmakefile", default=False, action="store_true" , help="skip creating Makefile")
parser.add_argument("--skipbuild",    default=False, action="store_true" , help="skip building project")
parser.add_argument("--skipupload",   default=False, action="store_true" , help="skip uploading hexfile")
parser.add_argument("--skipterminal", default=False, action="store_true" , help="skip opening terminal")
parser.add_argument("--skippause",    default=False, action="store_true" , help="skip pause before exit")
args = parser.parse_args()


# create Makefile
if args.skipmakefile == False:
  createMakefile(workdir='.', libroot=LIB_ROOT, outdir=OBJDIR, target=TARGET, options=OPTIONS)

# build target 
if args.skipbuild == False:
  buildProject(workdir='.', make=MAKE_TOOL)

# upload code via UART bootloader
if args.skipupload == False:
  if UPLOAD == 'BSL':
    stm8gal(tooldir=TOOL_DIR, port=PORT, outdir=OBJDIR, target=TARGET, reset=RESET)
  
  
  # upload code via SWIM. Use stm8flash on Linux, STVP on Windows (due to libusb issues)
  if UPLOAD == 'SWIM':
    if platform.system() == 'Windows':
      STVP(tooldir=SWIM_PATH, device=SWIM_NAME, hardware=SWIM_TOOL, outdir=OBJDIR, target=TARGET)
    else:
      stm8flash(tooldir=TOOL_DIR, device=SWIM_NAME, hardware=SWIM_TOOL, outdir=OBJDIR, target=TARGET)


# if specified open serial console after upload
if args.skipterminal == False:
  if TERMINAL == True:
    cmd = 'python '+TOOL_DIR+'terminal.py -p '+PORT
    exitcode = os.system(cmd)
    if (exitcode != 0):
      sys.stderr.write('error '+str(exitcode)+'\n\n')
      misc.Exit(exitcode)
    
# wait for return, then close window
if args.skippause == False:
  if (sys.version_info.major == 3):
    input("\npress return to exit ... ")
  else:
    raw_input("\npress return to exit ... ")
  sys.stdout.write('\n\n')

# END OF MODULE
