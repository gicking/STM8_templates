#!/usr/bin/python3

"""
 @package misc
 implementation miscelaneous helper routines
"""

import sys
import os
import platform
import inspect
import shlex
from subprocess import Popen, PIPE


##################
# python equivalent of getchar()
# Noter: fails in iPython console and Linux
##################
def getchar():

  ch = 0
  if platform.system() == 'Windows':
    import msvcrt as m
    ch = m.getch()
    #sys.stdio.flush()
    #sys.stderr.flush()
  else:
    import tty, termios
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    tty.setraw(sys.stdin.fileno())
    ch = sys.stdin.read(1)
    termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
  return ch
    
# getchar
##################



##################
# exit program without terminating iPython console in Spyder
##################
def Exit(code=0):
  
  # flush colsole output
  sys.stderr.flush()
  sys.stdout.flush()
  
  # for iPython console raise exception, else exit normally
  try:
    __IPYTHON__
  except NameError:
    if (code != 0):
      if (sys.version_info.major == 3):
        #pass
        input("\npress return ... ")
      else:
        #pass
        raw_input("\npress return ... ")
      print("")
    exit(code)
  else:
    raise Exception('exit')
    
# Exit
##################



##################
# execute the external command and get its exitcode, stdout and stderr.
# verbose: 1: print stderr output; 2: print stdout and stderr output
##################
def executeCmd(cmd, verbose=0):
  
  # split arguments (required for Popen)  
  args = shlex.split(cmd)
  
  # launch external application  
  proc = Popen(args, stdout=PIPE, stderr=PIPE)
  out, err = proc.communicate()
  exitcode = proc.returncode

  # on error print to stderr
  if ((exitcode != 0) and (verbose >= 1)):
    if (sys.version_info.major == 3):
      sys.stderr.write(str(err, sys.stdout.encoding)+"\n")
    else:
      sys.stderr.write(err+'\n')

  # print output to console
  if (verbose >= 2):
    if (sys.version_info.major == 3):
      sys.stdout.write(str(out, sys.stdout.encoding)+"\n")
    else:
      sys.stdout.write(out+"\n")
  
  # flush output
  sys.stderr.flush()
  sys.stdout.flush()
  
  # return exit code, stdout and stderr output
  return exitcode, out, err
    
# executeCmd
##################



##################
# return set of matching files in project folder incl. subfolders
##################
def listFiles( start='.', pattern='.c' ):

  result = set()
  for root, dirs, files in os.walk(start, followlinks=True):
    for file in files:
      if file.endswith(pattern):
        #print(os.path.join(root, file))
        result.add(os.path.join(root, file))
  return result
    
# listFiles
##################



##################
# return set of subdirectories in given folder
##################
def listSubdirs( start='.' ):

  result = set()
  for root, dirs, files in os.walk(start, followlinks=True):
    for dir in dirs:
      #print(os.path.join(root, dir))
      result.add(os.path.join(root, dir))
  return result
    
# listSubdirs
##################



##################
# return byte N of a number
##################
def byte(value=0x00, N=0):

  return (value >> (8*N)) & 0xFF
    
# byte
##################



##################
# name of calling function
##################
def whoami():

  return inspect.stack()[1][3]
    
# whoami
##################



##################
# name of caller of calling function
##################
def whosdaddy():

  return inspect.stack()[2][3]    

# whosdaddy
##################

