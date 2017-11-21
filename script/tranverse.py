#Python 3.6.1 (v3.6.1:69c0db5, Mar 21 2017, 17:54:52) [MSC v.1900 32 bit (Intel)] on win32
#Type "copyright", "credits" or "license()" for more information.
import os
import platform
import re
import sys
import time

delimiter = '\\'
endofline = "\r\n"
path = "D:\\git\\code"
#path = os.getcwd()
def init():
	global delimiter
	global endofline
	global path
	systemName = platform.system()
	if(systemName == "Windows"):
		delimiter = '\\' 
		endofline = "\r\n"
		path = os.getcwd()
		print ("Call Windows tasks")
	elif(systemName == "Linux"):
		delimiter = '/'  
		endofline = "\n"
		path = os.getcwd()
		print ("Call Linux task")
	elif(systemName == "Darwin"):
		delimiter = '/'  
		endofline = "\n"
		path = os.getcwd()
		print ("Call Mac task")
	else:
		print (systemName)


init()
print("path : %s"%path)

pyVersion = 2
pyVersion = sys.version[0]

            
pattern = re.compile(r'^1[345789][0-9]{9}$')
match = pattern.match('13345677892')
#match = re.match(r'^1[345789][0-9]{9}$','13345677892')
if match:
	print("regular expression match")

def modifyFile(filename):
	with open(filename,"r",encoding="utf-8") as f:
		lines = f.readlines()
	for line in lines:
		match = pattern.match(line)
		if match:
			print("regular expression match : %s"%line)
	#写的方式打开文件
	'''
	with open("filename","w",encoding="utf-8") as f_w:
		for line in lines:
			if "taste" in line:
			#替换
				line = line.replace("taste","tasting")
			f_w.write(line)
			
	'''


#os.chdir("目标目录")   #修改当前工作目录
#os.getcwd()    #获取当前工作目录


def tranverseFolder(path):
	parents = os.listdir(path)
	for parent in parents:
		child = os.path.join(path, parent)
		if os.path.isdir(child):
			tranverseFolder(child)
		else:
			print(child)
			if child.split(delimiter)[-1] == "text.txt":
				modifyFile(child)



print(path)
tranverseFolder(path)
print (platform.python_version())
print (delimiter)
print (endofline)
init()
time.sleep(1)
