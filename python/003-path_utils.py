#!/usr/bin/env python
#coding=utf-8

"""
* CREATED TIME: 2018-1-10 23:06:24
* LAST MODIFIED TIME: 2018-1-11 22:08:23
* DESCRIPTION: Some utility methods for getting and manipulating paths
* BY: 357688981@qq.com
"""

import errno
import os
import sys


def GetCurrentScriptDir():
    """Get the full path to the directory containing the current script."""
    script_filename = os.path.abspath(sys.argv[0])
    return os.path.dirname(script_filename)


def MaybeMakeDirectory(*path):
    """Creates an entire path, if it doesn't already exist."""
    file_path = os.path.join(*path)
    try:
        os.makedirs(file_path)
    except OSError as e:
        # errno.EEXIST is "File exists".  If we see another error, re-raise.
        if e.errno != errno.EEXIST:
          raise


def ListDirAndFiles(dir):
    """Lists all the files and directory inside dir."""
    return sorted(
      x for x in os.listdir(dir)
      if not x.startswith('.')
    )


if __name__ == '__main__':
    print("CurrentScriptDir: %s" % GetCurrentScriptDir())

    MaybeMakeDirectory("c:\\a\\b\\c\\d")

    print(ListDirAndFiles('D:\\MyGithub\\useful-codes'))

    pass




"""
创建/删除临时文件夹
"""
import subprocess
import sys
import tempfile


g_temp_dirs = []

def TempDir():
  """Generate a temporary directory (for downloading or extracting to) and keep
  track of the directory that's created for cleaning up later."""
  global g_temp_dirs
  temp = tempfile.mkdtemp()
  g_temp_dirs.append(temp)
  return temp

def RunOrDie(command):
  rc = subprocess.call(command, shell=True)
  if rc != 0:
    raise SystemExit('%s failed.' % command)

def DeleteAllTempDirs():
  """Remove all temporary directories created by |TempDir()|."""
  global g_temp_dirs
  if g_temp_dirs:
    sys.stdout.write('Cleaning up temporaries...\n')
  for temp in g_temp_dirs:
    # shutil.rmtree errors out on read only attributes.
    RunOrDie('rmdir /s/q "%s"' % temp)
  g_temp_dirs = []


if __name__ == '__main__':
    print(TempDir())
    DeleteAllTempDirs()