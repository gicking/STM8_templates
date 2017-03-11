#!/usr/bin/python

import sys
import argparse
import time
import threading
import serial

# use to kill threads
g_flagExit=0

#############################################################

"""
class for OS independent keyboard polling
  source: 
"""
class _Getch:
    """Gets a single character from standard input.  Does not echo to the screen."""
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()

#############################################################

"""
main function of sender thread: wait for byte from keyboard and send 
"""
def sender():
  global g_flagExit
  getch = _Getch()
  while g_flagExit == 0:
    c = getch()
    if c:
      #sys.stdout.write(c)
      port.write(c)
    if ord(c)==13:
      print
      sys.stdout.flush()
    # stop in case of Ctrl-C
    if ord(c)==3:
      g_flagExit=1
      exit()
  return


#############################################################

"""
main function of receiver thread: wait for byte received and display 
"""
def receiver():
  global g_flagExit
  while g_flagExit == 0:
    num=port.inWaiting()    # check for data received
    if num>0:
      rcv = port.read(num)  # read data from buffer
      #print rcv             # display
      sys.stdout.write(rcv)
      #print chr(13)
      sys.stdout.flush()
  exit()
  return


#############################################################


##########
# main program
##########

# serial port & baudrate
#PORT     = '/dev/ttyUSB0'
#BAUDRATE = 115200
PORT     = '/dev/ttyUSB0'
BAUDRATE = 115200

# commandline parameters
parser = argparse.ArgumentParser(description="simple terminal script")
parser.add_argument('-p', '--port', type=str, help='port name', required=False, default=PORT)
parser.add_argument('-b', '--baud', type=int, help='baudrate', required=False, default=BAUDRATE)
parser.add_argument('-t', '--timeout', type=float, help='timeout', required=False, default=2.0)
args = parser.parse_args()

# print message
print ' '
print 'Simple Python Terminal (v0.1)'
print 'connect', args.port, 'at', args.baud, 'Baud'
print 'press Ctrl-C to exit'
print ' '

# open serial port
port = serial.Serial(args.port, baudrate=args.baud, timeout=args.timeout)

# for exiting all threads via Ctrl-C
g_flagExit=0

# create and start threads for sender and receiver
Tx = threading.Thread(target=sender)
Rx = threading.Thread(target=receiver)
Tx.start()
Rx.start()

