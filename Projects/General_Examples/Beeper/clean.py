#!/usr/bin/python

#############
# clean up project outputs and temporary files
#############

# required modules
import os


##################
# helper functions
##################

#########
def removeFolder(foldername):
  """
   delete folder and content
  """
  
  #if folder exists
  if os.path.exists(foldername):
    # recursively remove files in folder
    for root, dirs, files in os.walk(foldername, topdown=False):
      for name in files:
        os.remove(os.path.join(root, name))
      for name in dirs:
        os.rmdir(os.path.join(root, name))
    
    # delete folder itself
    os.rmdir(foldername) 
 
  # end removeFolder()


#########
def removeFile(path=os.curdir, pattern='XYX'):
  """
   delete file ending with pattern
  """
  for filename in os.listdir(path):
    if filename.endswith(pattern):
      os.remove(os.path.join(path, filename)) 
      #print(filename)    
  # end removeFile()



##################
# main program
##################
   
removeFile('.','Makefile')
removeFile('.','.DS_Store')
removeFile('./STVD_Cosmic','.DS_Store')
removeFile('.','*.TMP')
removeFile('./STVD_Cosmic','.TMP')
removeFile('./STVD_Cosmic','.spy')
#removeFile('./STVD_Cosmic','.dep')
removeFile('./STVD_Cosmic','.pdb')
removeFile('./STVD_Cosmic','.wdb')
#removeFile('./STVD_Cosmic','.wed')
removeFolder('./-p')
removeFolder('./output')
removeFolder('./STVD_Cosmic/Release')
removeFolder('./STVD_Cosmic/Debug')
  
# END OF MODULE

