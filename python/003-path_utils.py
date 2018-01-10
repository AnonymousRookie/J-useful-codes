#!/usr/bin/env python
#coding=utf-8

"""
* CREATED TIME: 2018-1-10 23:06:24
* LAST MODIFIED TIME: 2018-1-10 23:06:24
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

if __name__ == '__main__':
    print("CurrentScriptDir: %s" % GetCurrentScriptDir())

    MaybeMakeDirectory("c:\\a\\b\\c\\d")

    pass