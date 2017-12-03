# -*- coding: UTF-8 -*-
#Python 3.6.1 (v3.6.1:69c0db5, Mar 21 2017, 17:54:52) [MSC v.1900 32 bit (Intel)] on win32
#Type "copyright", "credits" or "license()" for more information.
import math
import os
import platform
import re
import sys
import time
import xlrd

delimiter = '\\'
endofline = "\r\n"
path = "D:\\git\\code"
#path = os.getcwd()

filename = "NULL"
arr = ["line"];
arrSeek = ["file_seek"];

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
	global arr
	with open(filename,"r",encoding="utf-8") as f:
		lines = f.readlines()
	i = 1
	#print(lines)
	for line in lines:
		#match = pattern.match(line)
		match = re.match(r'^1[345789][0-9]{9}$',line)
		tagMatch = re.search(r'tag',line)
		if tagMatch:
			print("tag match in %dth line : %s"%(i,line))
			arr.append(i)
		if match:
			print("regular expression match : %s"%line)
		i = i + 1
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
	global filename
	parents = os.listdir(path)
	for parent in parents:
		child = os.path.join(path, parent)
		if os.path.isdir(child):
			tranverseFolder(child)
		else:
			#print(child)
			if child.split(delimiter)[-1] == "text.txt":
				filename = child
				modifyFile(child)


def modifyExcel(filename):
	workbook = xlrd.open_workbook(filename)
	sheet_names = workbook.sheet_names()
	for sheet_name in sheet_names:
		worksheet = workbook.sheet_by_name(sheet_name)
		num_rows = worksheet.nrows
		for curr_row in range(num_rows):
			row = worksheet.row_values(curr_row)
			print('row%s is %s'%(curr_row,row))
		num_cols = worksheet.ncols
		for curr_col in range(num_cols):
			col = worksheet.col_values(curr_col)
			print('col%s is %s'%(curr_col,col))
		cell = worksheet.cell(num_rows-1,num_cols-1).value
		print("cell %s",cell)
		#获取单元格中值的类型，类型 0 empty,1 string, 2 number, 3 date, 4 boolean, 5 error
		cell_type = worksheet.cell_type(num_rows-1,num_cols-1)
		print("cell_type %s", cell_type)

#modifyExcel('D:\\git\\code\\script\\test.xlsx')
modifyExcel('/Users/krausclyde/code/script/test.xlsx')

print(path)
tranverseFolder(path)
print (platform.python_version())
print (delimiter)
print (endofline)
print (filename)
fstream = open(filename,'r')
arrNum = 1
lineNum = 0
pos = 0
while lineNum <= arr[3]:
	#global pos
	posPre = fstream.tell()
	line = fstream.readline()
	lineNum = lineNum + 1
	if lineNum == arr[arrNum]:
		arrNum = arrNum + 1
		pos = fstream.tell()
		arrSeek.append(posPre)

print("pos = ", pos)
print("arr = ", arr)
print("arrSeek = ", arrSeek)
#print(fstream.readlines(30))
#pos = fstream.tell()
#print("pos = ", pos)
fstream.seek(0,0)
fileblock = []
arrSeek[0] = 0
for i in range(1, len(arrSeek)):
	print(i)
	fileblock.append(fstream.read(arrSeek[i] - arrSeek[i-1]))
fileblock.append(fstream.read())
#print(fileblock)

fstream.seek(0,0)
fileblock = fstream.read()
match = re.search(r'tag', fileblock)
print("match = :", match)
if match:
	re.split(r'tag',fileblock)
	print(re.split(r'tag',fileblock))
print(fileblock)

fstream.close()
time.sleep(2)
