#!/usr/bin/env python
#coding=utf-8

"""
* CREATED TIME: 2016-8-27 23:03:56
* MODIFIED TIME: 2016-8-28 09:53:17
* BY: 357688981@qq.com
"""

import os
import sys

def _check_python_version():
    '''
        检测python的版本
    '''

    major_ver = sys.version_info[0]

    # python 2.7
    # sys.version_info = sys.version_info(major=2, minor=7, micro=10, releaselevel='final', serial=0)

    if major_ver > 2:
        print ("The python version is %d.%d. But python 2.x is required. (Version 2.7 is well tested)\n"
               "Download it here: https://www.python.org/" % (major_ver, sys.version_info[1]))
        return False
    return True


if __name__ == '__main__':
    _check_python_version()