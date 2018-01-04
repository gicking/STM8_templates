#!/usr/bin/python3

'''
 create Makefile with auto-dependencies
 standalone usage: create_makefile.py [-m make-tool] [-w workdir] [-o outdir] [-t target]
'''

# required modules
import sys
import os
import platform
import argparse
import multiprocessing
import misc


##################
# create Makefile with auto-dependency
##################
def createMakefile(workdir='.', libroot='../../../Library/', outdir='output', target='main.ihx', options=''):

  # print message to console  
  sys.stdout.write('creating Makefile ... ')
  sys.stdout.flush()

  # change to specified working directory
  os.chdir(workdir)

  # set project paths
  LIB_ROOT = libroot
  PRJ_ROOT = workdir
  OBJDIR   = outdir
  TARGET   = target

  # set command for creating dependencies and set search paths 
  CC       = 'sdcc '
  CFLAGS   = '-mstm8 --std-sdcc99 --opt-code-speed '+options+' '
  #CFLAGS   = '-mstm8 --std-sdcc99 --debug -DDEBUG '+options+' '
  LFLAGS   = '-mstm8 -lstm8 --out-fmt-ihx '
  DEPEND   = '-MM '
  INCLUDE  = '-I. '
  for dir in misc.listSubdirs(PRJ_ROOT):
    dir = dir.replace('\\','/')
    INCLUDE += '-I' + dir + ' '
  for dir in misc.listSubdirs(LIB_ROOT):
    dir = dir.replace('\\', '/')          # convert Windows path to POSIX for Makefile
    if os.path.basename(dir) == 'inc':    # include all 'inc' folders
      INCLUDE += '-I' + dir + ' '

  # get set of .c files in project folder incl. subdirectories
  source_todo = misc.listFiles(PRJ_ROOT,".c")
  source_done = set()
  header_done = set()
  object_done = set()

  # generate generic Makefile header
  Makefile = open('Makefile', 'wb')
  Makefile.write(('OBJDIR   = '+OBJDIR+'\n').encode())    # Python 3.x requires bytes, not string 
  Makefile.write(('TARGET   = '+TARGET+'\n\n').encode())
  Makefile.write(('.PHONY: clean all default objects\n\n').encode())
  Makefile.write(('.PRECIOUS: $(TARGET)\n\n').encode())
  Makefile.write(('default: $(OBJDIR) $(OBJDIR)/$(TARGET)\n\n').encode())
  Makefile.write(('all: default\n\n').encode())
  Makefile.write(('# create output folder\n').encode())
  Makefile.write(('$(OBJDIR):\n').encode())
  if platform.system() == 'Windows':
    Makefile.write(('	mkdir $(OBJDIR)\n').encode())
  else:
    Makefile.write(('	mkdir -p $(OBJDIR)\n').encode())
  Makefile.write(('\n').encode())

  # iteratively add project sources to Makefile
  Makefile.write(('# compile sources\n').encode())
  while (len(source_todo) > 0):

    # get next pending source and mark as done
    source = source_todo.pop()
    source_done.add(source)

    # convert Windows path to POSIX for Makefile
    source = source.replace('\\','/')

    # use compiler generate dependency list
    cmd = CC+DEPEND+CFLAGS+INCLUDE+source
    #print cmd
    exitcode, out, err = misc.executeCmd(cmd, verbose=1)
    if (exitcode != 0):
      misc.Exit(exitcode)
    
    # for Python 3.x need to explicitely convert bytes to str
    if (sys.version_info.major == 3):
      out = str(out, sys.stdout.encoding)

    # append .c file with dependency and compile instruction to Makefile
    Makefile.write(('$(OBJDIR)/'+out).encode())
    #print(out)
    Makefile.write(('\t'+CC+CFLAGS+INCLUDE+'-c $< -o $@\n\n').encode())
    
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
          next = (next[::-1].replace("/inc/"[::-1], "/src/"[::-1], 1))[::-1]  # replace last /inc/ by /src/ (see https://stackoverflow.com/questions/2556108/rreplace-how-to-replace-the-last-occurrence-of-an-expression-in-a-string)        
          if (os.path.isfile(next[:-1]+'c')):   # if corresponding .c exists, add to todo list
            source_todo.add(next[:-1]+'c')


  # link project object files
  Makefile.write(('# link sources\n').encode())
  Makefile.write(('$(OBJDIR)/$(TARGET): ').encode())
  for next in object_done:
    Makefile.write(('$(OBJDIR)/'+next+' ').encode())
  Makefile.write(('\n').encode())
  Makefile.write(('\t'+CC+LFLAGS).encode())
  for next in object_done:
    Makefile.write(('$(OBJDIR)/'+next+' ').encode())
  Makefile.write((' -o $@\n').encode())

  # close Makefile.dep
  Makefile.close()

  # print message to console  
  sys.stdout.write('done\n')
  sys.stdout.flush()

# createMakefile
##################


##################
# build Project using Makefile
##################
def buildProject(workdir='.', make='make', numCPU=0):

  # change to specified working directory
  os.chdir(workdir)

  # print message to console  
  sys.stdout.write('building target ... ')
  sys.stdout.flush()

  # for non-positive CPU number use all available cores  
  if (numCPU <= 0):
    numCPU = multiprocessing.cpu_count()  
  
  # compile project
  exitcode, out, err = misc.executeCmd(make+' -j'+str(numCPU), verbose=1)
  
  # on error terminate script  
  if (exitcode != 0):
    misc.Exit(exitcode)
  else:
    sys.stdout.write('done\n')
    sys.stdout.flush()

# buildProject
##################



########################################################################


#-------------------------------------------------------------------
# MODULE TEST
#-------------------------------------------------------------------
# only executute this block of code if running this module directly,
# *not* if importing it
# -see here: http://effbot.org/pyfaq/tutor-what-is-if-name-main-for.htm
if __name__ == "__main__":

  # check python version
  #version = sys.version_info
  #print(version)

  # define commandline parameters and defaults
  parser = argparse.ArgumentParser(description="create project makefile")
  parser.add_argument('-m', '--make',    type=str, help='make tool',    required=False, default='make')
  parser.add_argument('-w', '--workdir', type=str, help='work dir',     required=False, default='.')
  parser.add_argument('-o', '--outdir',  type=str, help='output dir',   required=False, default='output')
  parser.add_argument('-t', '--target',  type=str, help='target hex',   required=False, default='main.ihx')
  args = parser.parse_args()

  # create Makefile with autodependency
  createMakefile(workdir=args.workdir, rootdir=args.rootdir, outdir=args.outdir, target=args.target)

  # build target 
  buildProject(workdir=args.workdir, make=args.make)

