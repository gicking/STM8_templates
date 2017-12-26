#!/usr/bin/python

'''
 Upload Cosmic S19 file via STM8 bootloader 
'''

# required modules
import os
import platform

# set path of s19 file
HEXFILE = './Release/STM8_Template.s19'
#HEXFILE = './Debug/STM8_Template.s19'

# set tool path
ROOT_DIR = '../../../../'
TOOL_DIR = ROOT_DIR + 'Tools/'

# determine operating system
OS = platform.system()
#print OS

# set OS specific
FLASHTOOL = ''
PORT      = ''
if OS == 'Windows':
  PORT      = 'COM10'
  FLASHTOOL = 'stm8gal.exe'
else:
  PORT = '/dev/ttyUSB0'
  FLASHTOOL = 'stm8gal'

# set general
TERMINAL  = False
  

##################
# helper functions
##################

#########
def getchar():
  """
   python equivalent of getchar()
  """
  ch = 0
  if OS == 'Windows':
    import msvcrt as m
    ch = m.getch()
    sys.stdio.flush()
    sys.stderr.flush()
  else:
    import sys, tty, termios
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    tty.setraw(sys.stdin.fileno())
    ch = sys.stdin.read(1)
    termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
  return ch
  # end getchar()


#########
def get_exitcode_stdout_stderr(cmd):
  """
   execute the external command and get its exitcode, stdout and stderr.
  """
  args = shlex.split(cmd)
  proc = Popen(args, stdout=PIPE, stderr=PIPE)
  out, err = proc.communicate()
  exitcode = proc.returncode
  return exitcode, out, err



##################
# main program
##################

# on success upload to STM8
cmd = TOOL_DIR+FLASHTOOL+' -p '+PORT+' -w '+HEXFILE+' -v' 
if OS == 'Windows':
  cmd = cmd.replace('/','\\')
#print cmd
#exitcode, out, err = get_exitcode_stdout_stderr(cmd)
exitcode = os.system(cmd)
if (exitcode != 0):
  #sys.stderr.write(err+'\n')
  #sys.stderr.write('error '+str(exitcode)+'\n\n')
  getchar()
  exit()


# for non-UART project skip opening terminal
if TERMINAL == False:
  sys.stdout.write('press return to exit')
  getchar()
  print('\n')
  exit()


# on success open terminal
cmd = 'python '+TOOL_DIR+'terminal.py -p '+PORT
exitcode = os.system(cmd)
if (exitcode != 0):
  sys.stderr.write('error '+str(exitcode)+'\n\n')
  getchar()
  exit()
  
# END OF MODULE
