#!/usr/bin/python

'''
 Script for making and uploading a STM8 project with dependency auto-detection
'''

# required modules
import sys
import os
import platform
import shlex
from subprocess import Popen, PIPE

# set OS specific
if platform.system() == 'Windows':
  PORT         = 'COM6'
  BSL_FLASHER  = 'STM8_serial_flasher.exe'
  SWIM_FLASHER = 'C:\Programme\STMicroelectronics\st_toolset\stvp\STVP_CmdLine.exe'
  SWIM_TOOL    = 'ST-LINK'
  SWIM_NAME    = 'STM8S105x6'  # STM8 Discovery
  #SWIM_NAME    = 'STM8S208xB'  # muBoard
  MAKE_TOOL    = 'mingw32-make.exe'
else:
  PORT         = '/dev/ttyUSB0'
  BSL_FLASHER  = 'STM8_serial_flasher'
  SWIM_FLASHER = 'stm8flash'
  SWIM_TOOL    = 'stlink'
  SWIM_NAME    = 'stm8s105c6'  # STM8 Discovery
  #SWIM_NAME    = 'stm8s208?b'  # muBoard
  MAKE_TOOL    = 'make'

# set general options
MAKE_CORES    = 4
UPLOAD        = 'SWIM'  # select 'BSL' or 'SWIM'
OPEN_TERMINAL = False
  

##################
# helper functions
##################

#########
def getchar():
  """
   python equivalent of getchar()
  """
  ch = 0
  if platform.system() == 'Windows':
    import msvcrt as m
    ch = m.getch()
    #sys.stdio.flush()
    #sys.stderr.flush()
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
def listFiles( start='.', pattern='.c' ):
  """
   return set of matching files in project folder incl. subfolders
  """
  result = set()
  for root, dirs, files in os.walk(start):
    for file in files:
      if file.endswith(pattern):
        #print(os.path.join(root, file))
        result.add(os.path.join(root, file))
  return result
  # end listFiles()


#########
def listSubdirs( start='.' ):
  """
   return set of subdirectories in given folder
  """
  result = set()
  for root, dirs, files in os.walk(start):
    for dir in dirs:
      #print(os.path.join(root, dir))
      result.add(os.path.join(root, dir))
  return result
  # end listFiles()


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


#########
def get_swim_device(start='.'):
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

# set compile search paths
ROOT_DIR = '../../../'
TOOL_DIR = ROOT_DIR + 'Tools/'
LIB_ROOT = ROOT_DIR + 'Library/'
PRJ_ROOT = '.'
OBJDIR   = 'output'
TARGET   = 'main.ihx'

# set command for creating dependencies and set search paths 
CC       = 'sdcc '
CFLAGS   = '-mstm8 --std-sdcc99 --std-c99 --opt-code-speed '
#CFLAGS   = '-mstm8 --std-sdcc99 --std-c99 --debug -DDEBUG '
LFLAGS   = '-mstm8 -lstm8 --out-fmt-ihx '
DEPEND   = '-MM '
INCLUDE  = '-I. '
for dir in listSubdirs(PRJ_ROOT):
  INCLUDE += '-I' + dir + ' '
for dir in listSubdirs(LIB_ROOT):
  INCLUDE += '-I' + dir + ' '

# get set of .c files in project folder incl. subdirectories
source_todo = listFiles(PRJ_ROOT,".c")
source_done = set()
header_done = set()
object_done = set()

# generate generic Makefile header
Makefile = open('Makefile', 'wb')
Makefile.write('OBJDIR   = '+OBJDIR+'\n')
Makefile.write('TARGET   = '+TARGET+'\n\n')
Makefile.write('.PHONY: clean all default objects\n\n')
Makefile.write('.PRECIOUS: $(TARGET)\n\n')
Makefile.write('default: $(OBJDIR) $(OBJDIR)/$(TARGET)\n\n')
Makefile.write('all: default\n\n')
Makefile.write('# create output folder\n')
Makefile.write('$(OBJDIR):\n')
if platform.system() == 'Windows':
  Makefile.write('	mkdir $(OBJDIR)\n')
else:
  Makefile.write('	mkdir -p $(OBJDIR)\n')
Makefile.write('\n')

# iteratively add project sources to Makefile
Makefile.write('# compile sources\n')
while (len(source_todo) > 0):

  # get next pending source and mark as done
  source = source_todo.pop()
  source_done.add(source)

  # convert Windows path to POSIX for Makefile
  if platform.system() == 'Windows':
    source = source.replace('\\','/')

  # use compiler generate dependency list
  cmd = CC+DEPEND+CFLAGS+INCLUDE+source
  #print cmd
  exitcode, out, err = get_exitcode_stdout_stderr(cmd)
  if (exitcode != 0):
    print 'error: ' + err
    getchar()
    exit()
  
  # append .c file with dependency and compile instruction to Makefile
  Makefile.write('$(OBJDIR)/'+out)
  #print(out)
  Makefile.write('\t'+CC+CFLAGS+INCLUDE+'-c $< -o $@\n\n')
  
  # extract file list including object[0], source[1] and headers[2..N]
  out = out.replace(':', '')
  out = out.replace('\\', '')
  out = out.replace('\n', '')
  out = out.split()
  #print out

  # for all files returned by compiler...
  for next in out:
    
    # append object files for linker
    if next.endswith('.rel'):
      object_done.add(next)

    # if corresponding source to header exists, add to pending sources
    if next.endswith('.h'):
      if next not in header_done:           # not yet in list
        header_done.add(next)                 # add to treated headers
        if (os.path.isfile(next[:-1]+'c')):   # if corresponding .c exists, add to todo list
          source_todo.add(next[:-1]+'c')


# link project object files
Makefile.write('# link sources\n')
Makefile.write('$(OBJDIR)/$(TARGET): ')
for next in object_done:
  Makefile.write('$(OBJDIR)/'+next+' ')
Makefile.write('\n')
Makefile.write('\t'+CC+LFLAGS)
for next in object_done:
  Makefile.write('$(OBJDIR)/'+next+' ')
Makefile.write(' -o $@\n')

# close Makefile.dep
Makefile.close()


# build target 
print("")
sys.stdout.write('building target ... ')
sys.stdout.flush()
exitcode, out, err = get_exitcode_stdout_stderr(MAKE_TOOL+' -j'+str(MAKE_CORES))
if (exitcode != 0):
  sys.stderr.write(err+'\n')
  getchar()
  exit()
else:
  print('done\n')


# upload to STM8 via UART bootloader
if UPLOAD == 'BSL':
  if OPEN_TERMINAL == True:
    sys.stdout.write('reset STM8 and press return to continue') # avoid conflict with possible serial output from STM8
    getchar()
    print(' ')
  cmd = TOOL_DIR+BSL_FLASHER+' -p '+PORT+' -w '+OBJDIR+'/'+TARGET+' -v -Q' 
  if platform.system() == 'Windows':
    cmd = cmd.replace('/','\\')
  #print cmd
  #exitcode, out, err = get_exitcode_stdout_stderr(cmd)
  exitcode = os.system(cmd)
  if (exitcode != 0):
    #sys.stderr.write(err+'\n')
    #sys.stderr.write('error '+str(exitcode)+'\n\n')
    getchar()
    exit()


# upload to STM8 via SWIM
if UPLOAD == 'SWIM':
  if platform.system() == 'Windows':    # Windows: STVP commandline version, see http://www.st.com
    cmd = SWIM_FLASHER+' -BoardName='+SWIM_TOOL+' -Port=USB -ProgMode=SWIM -Device='+SWIM_NAME+' -readData -readOption -no_progData -no_progOption -no_loop -no_log -FileProg='+OBJDIR+'/'+TARGET
    cmd = cmd.replace('/','\\')
  else:                                 # POSIX: use stm8flash, see https://github.com/vdudouyt/stm8flash 
    cmd = TOOL_DIR+SWIM_FLASHER+' -c '+SWIM_TOOL+' -w '+OBJDIR+'/'+TARGET+' -p '+SWIM_NAME 
  #print cmd
  #exitcode, out, err = get_exitcode_stdout_stderr(cmd)
  exitcode = os.system(cmd)
  if (exitcode != 0):
    #sys.stderr.write(err+'\n')
    #sys.stderr.write('error '+str(exitcode)+'\n\n')
    getchar()
    exit()


# open serial console
if OPEN_TERMINAL == True:
  cmd = 'python '+TOOL_DIR+'terminal.py -p '+PORT
  exitcode = os.system(cmd)
  if (exitcode != 0):
    sys.stderr.write('error '+str(exitcode)+'\n\n')
    getchar()
    exit()
  

# print message
sys.stdout.write('\npress return to exit')
getchar()
print('\n')
exit()

# END OF MODULE
