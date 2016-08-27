#!/usr/bin/env python
#coding=utf-8
import sys

# 判断操作系统platform
def _isWindows():
    return sys.platform == 'win32'

def _isLinux():
    return sys.platform.startswith('linux')

def _is_mac():
    return sys.platform == 'darwin'


# 设置Windows环境变量, PATH
# _winreg.HKEY_LOCAL_MACHINE
# _winreg.HKEY_CURRENT_USER
def set_windows_path(add_dir):
        ret = False
        import _winreg
        try:
            env = None
            path = None
            env = _winreg.OpenKeyEx(_winreg.HKEY_CURRENT_USER,
                                    'Environment',
                                    0,
                                    _winreg.KEY_SET_VALUE | _winreg.KEY_READ)
            path = _winreg.QueryValueEx(env, 'Path')[0]

            # add variable if can't find it in PATH
            path_lower = path.lower()
            add_dir_lower = add_dir.lower()
            if (path_lower.find(add_dir_lower) == -1):
                path = add_dir + ';' + path
                _winreg.SetValueEx(env, 'Path', 0, _winreg.REG_SZ, path)
                _winreg.FlushKey(env)

            _winreg.CloseKey(env)
            ret = True
        except Exception:
            if not path:
                path = add_dir
                _winreg.SetValueEx(env, 'Path', 0, _winreg.REG_SZ, path)
                _winreg.FlushKey(env)
                ret = True
            else:
                _winreg.SetValueEx(env, 'Path', 0, _winreg.REG_SZ, path)
                _winreg.FlushKey(env)
                ret = False

            if env:
                _winreg.CloseKey(env)

        if ret:
            print("  ->Add directory \"%s\" into PATH succeed!\n" % add_dir)
        else:
            print("  ->Add directory \"%s\" into PATH failed!\n" % add_dir)



# 添加注册表
# modify registry table to add an environment variable on windows
def _set_environment_variable_win32(key, value):
    ret = False
    import _winreg
    try:
        env = None
        env = _winreg.OpenKeyEx(_winreg.HKEY_CURRENT_USER,
                                'Environment',
                                0,
                                _winreg.KEY_SET_VALUE | _winreg.KEY_READ)
        _winreg.SetValueEx(env, key, 0, _winreg.REG_SZ, value)
        _winreg.FlushKey(env)
        _winreg.CloseKey(env)
        ret = True
    except Exception:
        if env:
            _winreg.CloseKey(env)
        ret = False

    return ret


def _set_environment_variable(key, value):
    print("  -> Add %s environment variable..." % key)
    ret = False
    if _isWindows():
        ret = _set_environment_variable_win32(key, value)

    if ret:
        print("    ->Added %s=%s\n" % (key, value))
    else:
        print("    ->Add failed\n")
    return ret


if __name__ == '__main__':
    set_windows_path(r"D:\BaiduYunDownload\2016shanghai")
    _set_environment_variable("POP", "21534;abc")