#!/usr/bin/python
# -*- coding: utf-8 -*-


import os

#import pwd
import getpass

import signal
import time
import sys
import errno
import subprocess
#파이썬 유니코드 How-to : http://coreapython.hosting.paran.com/hangul/Unicode%20HOWTO.htm
import unicodedata# utf-8 : nfc, nfd

# Symbols
product_version = None
build_resource_path = 'mac_release/'
xcode_parameter = '-spec macx-xcode'
param1 = ''

# Declare Variable
starttime = time.time()

home_path = os.getcwd()
print 'home path = ' + home_path + '\n'

# Function
def remove_reverse_str(string, sep):
	endPos = string.rfind(sep)
	return string[0:endPos+1]

def compile_exit():
	os.chdir(home_path)
	sys.exit()

def run_command(command):
	print command
	e = os.system(command);

def buildWithMake(bClean):
	coreCount = subprocess.check_output('sysctl -n hw.ncpu', shell=True)
	command = "make -j%s" % coreCount

	if bClean == True:
		run_command("make clean -s")
	
	return run_command(command)

def remove_file(path):
	run_command('rm ' + path)

def remove_dir(path):
	run_command('rm -rf ' + path)

def build_library_api(option):
	print '\n\n\n'
	print 'build_library_api option=%s' % option

	os.chdir(home_path)

	remove_file("Makefile")
	remove_file(".qmake.stash")
	remove_dir("mac_release/CloLibraryAPI_Plugin")

	run_command("echo $QTDIR")
	run_command("echo $PATH")
	run_command("which qmake")
	run_command("mkdir mac_release")
	run_command("mkdir mac_release/CloLibraryAPI_Plugin")

	if param1 == 'xdebug':
		run_command("rm -rf CloLibraryAPI_Plugin.xcodeproj")
		run_command("qmake -nocache -spec macx-xcode CloLibraryAPI_Plugin.pro -o CloLibraryAPI_Plugin.xcodeproj CONFIG+=\"" + option + "\"")
		run_command("python scripts/xcodeprojset.py CloLibraryAPI_Plugin.xcodeproj -addstdlib")
		run_command("make -C " + home_path + " -f 'CloLibraryAPI_Plugin.xcodeproj/qt_preprocess.mak' mocables")
	elif param1 == 'release' or param1 == 'debug':
		os.chdir(home_path + "/mac_release/CloLibraryAPI_Plugin")
		run_command("qmake -nocache ../../CloLibraryAPI_Plugin.pro CONFIG+=\"" + option + "\"")
                returnVal = buildWithMake(True)

	change_reference_path()
	os.chdir(home_path)

def change_reference_path():
	libName = "build/libCloLibraryAPI_Plugin.1.0.0.dylib"
	refPath = "@executable_path/../Frameworks/"
	changeCmd = "install_name_tool -change"
	QtPath = "/Qt/4.8.7/lib/"

	# 현재 패스에 라이브러리가 있는지 확인하고
	cwd = os.getcwd() + "/" + libName

	# 있으면 참조패스를 변경하자
	if os.path.exists(cwd): 
		QtLib = "QtCore.framework/Versions/4/QtCore"
		pathName = QtPath + QtLib
		run_command(changeCmd + " " + pathName + " " + refPath + QtLib + " " + libName); 

		QtLib = "QtGui.framework/Versions/4/QtGui"
		pathName = QtPath + QtLib
		run_command(changeCmd + " " + pathName + " " + refPath + QtLib + " " + libName); 	

def build_debug_product(option):
	global param1
	print '\nBuild debug product'
	print 'option : ' + option
	build_library_api(option)

def build_release_product(option):
	global param1
	print '\nBuild release product'
	print 'option : ' + option
	build_library_api(option)

def make_sure_path_exists(path):
	try:
		os.makedirs(path)
	except OSError as exception:
		if exception.errno != errno.EEXIST:
			raise

def set_variable():
	print '\nBuild process...'
	global param1
	global build_option

	build_option = ""

	if param1 == 'xdebug':
		build_option += "xcode-debug build-debug"
	elif param1 == 'release':
		build_option += "build-release"
	elif param1 == 'debug':
		build_option += "build-debug"

	print 'build option : ' + build_option

def build_process():
	print '\nBuild process...'
	global param1
	global build_option

	set_variable()

	users_home_path = os.getenv('HOME')

	if param1 == 'debug' or param1 == 'xdebug':
		build_debug_product(build_option)
	elif param1 == 'release':
		build_release_product(build_option)

# build.py option
# sys.argv[1] debug, xdebug, release

print sys.platform

if len(sys.argv) < 2:
	print 'error:wrong parameters. %s' % len(sys.argv)
	compile_exit()
elif sys.argv[1] == 'debug' or sys.argv[1] == 'release' or sys.argv[1] == 'xdebug':
	param1 = sys.argv[1]
	build_process()

endtime = time.time()
print '\nStart time: ' + time.ctime(starttime)
print 'End time: ' + time.ctime(endtime)
minute = (endtime - starttime)/60
second = (endtime - starttime)%60
print 'Elapsed time : %dm:%ds' % ( minute, second )

compile_exit()

