#!/usr/bin/python3

'''
 upload hexfile via STM8 bootloader or SWIM
'''

# required modules
import sys
import os
import platform
import misc


##################
# upload to STM8 via stm8gal and UART bootloader
##################
def stm8gal(tooldir='../../../Tools/', tool='stm8gal', port='/dev/ttyUSB0', outdir='output', target='main.ihx', reset=0):

  # on Windows attach .exe to tool
  if platform.system() == 'Windows':
    tool = tool + ".exe"

  # assemble shell command
  cmd = tooldir + tool + ' -p ' + port + ' -w ' + outdir + '/' + target + ' -v -R ' + str(reset) 
  
  # on Windows replace path delimiter
  if platform.system() == 'Windows':
    cmd = cmd.replace('/','\\')
  #print cmd

  # upload hexfile
  exitcode = os.system(cmd)
  
  # check for success
  if (exitcode != 0):
    sys.stderr.write('error '+str(exitcode)+'\n\n')
    misc.Exit(exitcode)

# stm8gal
##################


##################
# upload to STM8 via stm8flash and SWIM interface
##################
def stm8flash(tooldir='../../../Tools/', tool='stm8flash', device='stm8s105c6', hardware='stlink', outdir='output', target='main.ihx'):

  # separate output a bit
  sys.stdout.write('\n')
  
  # on Windows attach .exe to tool
  if platform.system() == 'Windows':
    tool = tool + ".exe"

  # assemble shell command
  cmd = tooldir + tool + ' -c ' + hardware + ' -w ' + outdir + '/' + target + ' -p ' + device 
  
  # on Windows replace path delimiter
  if platform.system() == 'Windows':
    cmd = cmd.replace('/','\\')  
    cmd = cmd + ".exe"
  #print cmd

  # upload hexfile
  exitcode = os.system(cmd)
  
  # check for success
  if (exitcode != 0):
    sys.stderr.write('error '+str(exitcode)+'\n\n')
    misc.Exit(exitcode)

# stm8flash
##################


##################
# upload to STM8 via stm8flash and SWIM interface
##################
def STVP(tooldir='C:/Programme/STMicroelectronics/st_toolset/stvp/', tool='STVP_CmdLine.exe', device='STM8S105x6', hardware='ST-LINK', outdir='output', target='main.ihx'):

  # assemble shell command
  cmd = tooldir + tool + ' -BoardName=' + hardware + ' -Port=USB -ProgMode=SWIM -Device=' + device + \
    ' -readData -readOption -no_progData -no_progOption -no_loop -no_log -FileProg=' + outdir + '/' + target
  
  # on Windows replace path delimiter
  if platform.system() == 'Windows':
    cmd = cmd.replace('/','\\')  
  #print cmd

  # upload hexfile
  exitcode = os.system(cmd)
  
  # check for success
  if (exitcode != 0):
    sys.stderr.write('error '+str(exitcode)+'\n\n')
    misc.Exit(exitcode)

# STVP
##################
