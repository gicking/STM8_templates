#!/usr/bin/python3

'''
 Find and execute all clean.py beneath this script
'''

# required modules
import sys
import os
import platform
sys.path.insert(0,'../Tools')
import misc

# execute all 'clean.py' below the current folder
oldDir = os.getcwd()
for file in misc.listFiles('.',"build_upload.py"):

  # change working directory
  os.chdir(os.path.dirname(file))
  
  # show progress
  sys.stdout.write('compile ' + os.path.dirname(file) + ' ... ')
  sys.stdout.flush()
  
  # build w/o upload
  if platform.system() == 'Windows':
    err = os.system('python build_upload.py --skipupload --skipterminal --skippause > NUL')
  else:
    err = os.system('python build_upload.py --skipupload --skipterminal --skippause > /dev/null')
  if err != 0:
    misc.Exit(err)

  # print message
  sys.stdout.write('done\n')
  sys.stdout.flush()

  # restore working directory
  os.chdir(oldDir)
  
# optional prompt for return, then close window
if True:
  if (sys.version_info.major == 3):
    input("\npress return to exit ... ")
  else:
    raw_input("\npress return to exit ... ")
  sys.stdout.write('\n\n')
  
