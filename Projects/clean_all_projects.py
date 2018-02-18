#!/usr/bin/python3

'''
 Find and execute all clean.py beneath this script
'''

# required modules
import sys
import os
sys.path.insert(0,'../Tools')
import misc

# execute all 'clean.py' below the current folder
oldDir = os.getcwd()
for file in misc.listFiles('.',"clean.py"):
  
  # change working directory
  os.chdir(os.path.dirname(file))

  # print progress
  print(os.path.dirname(file))

  # execute clean.py
  os.system('python clean.py')
  
  # restore working directory
  os.chdir(oldDir)
  
# optional prompt for return, then close window
if False:
  if (sys.version_info.major == 3):
    input("\npress return to exit ... ")
  else:
    raw_input("\npress return to exit ... ")
  sys.stdout.write('\n\n')

