#!/usr/bin/python

'''
 Open terminal program
'''

# set OS specific
TOOL_DIR = '../../../Tools/'
import platform
if platform.system() == 'Windows':
  PORT         = 'COM10'
else:
  PORT         = '/dev/ttyUSB0'
  
# import required modules
import sys
import os
import platform
import argparse
sys.path.append(TOOL_DIR)
import misc


##################
# main program
##################

cmd = 'python '+TOOL_DIR+'terminal.py -p '+PORT
exitcode = os.system(cmd)
if (exitcode != 0):
  sys.stderr.write('error '+str(exitcode)+'\n\n')
  misc.Exit(exitcode)
    
# wait for return, then close window
if (sys.version_info.major == 3):
  input("\npress return to exit ... ")
else:
  raw_input("\npress return to exit ... ")
sys.stdout.write('\n\n')

# END OF MODULE
