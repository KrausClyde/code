require "luarocks.site_config" 
require "lfs" 

delimiter = nil
--在luarocks模块中，有一个luarocks.site_config模块（一个lua文件），其安装时便设定了操作系统类型
--local system = luarocks.site_config.LUAROCKS_UNAME_S or io.popen("uname -s"):read("*l") 
local system = io.popen("uname -s"):read("*l")
if system == "Darwin" then  
    delimiter = '/'  
elseif system and system:match("^Windows") then  
    delimiter = '\\'  
end  
print(system)  

--get filename
function getFileName(str)
    local idx = str:match(".+()%.%w+$")
    if(idx) then
        return str:sub(1, idx-1)
    else
        return str
    end
end

--get file postfix
function getExtension(str)
    return str:match(".+%.(%w+)$")
end

path=lfs.currentdir()
print("current path: " .. path)
--[[
    lfs.attributes(filepath [, aname]) 获取路径指定属性
    lfs.chdir(path) 改变当前工作目录，成功返回true，失败返回nil加上错误信息
    lfs.currentdir 获取当前工作目录，成功返回路径，失败为nil加上错误信息
    lfs.dir(path) 返回一个迭代器(function)和一个目录(userdata)，每次迭代器都会返回一个路径，直到不是文件目录为止，则迭代器返回nil
    lfs.lock
    lfs.mkdir(dirname)  创建一个新目录
    lfs.rmdir(dirname) 删除一个已存在的目录，成功返回true，失败返回nil加上错误信息
--]]
--把遍历目录得到的每一个路径都存在一个table里面，然后遍历这个table就能把每条目录都打印出来
function getpathes(rootpath, pathes)
    pathes = pathes or {}
    for entry in lfs.dir(rootpath) do
        if entry ~= '.' and entry ~= '..' then
            local path = rootpath .. delimiter .. entry
            local attr = lfs.attributes(path)
            assert(type(attr) == 'table')
            
            if attr.mode == 'directory' then
                getpathes(path, pathes)
            else
                table.insert(pathes, path)
            end
        end
    end
    return pathes
end

local rootpath = '/Users/krausclyde/code'
local pathes
pathes = getpathes(rootpath, pathes)  
  
for key, path in pairs(pathes) do  
    --print(key .. "==" .. path)  
end 


--Regular Expression
--[[
	+      匹配前一字符1次或多次
	*      匹配前一字符0次或多次
	-      匹配前一字符0次或多次
	?      匹配前一字符0次或1次


	单个字符(除^$()%.[]*+-?外): 与该字符自身配对
	.(点): 与任何字符配对
	%a: 与任何字母配对
	%c: 与任何控制符配对(例如\n)
	%d: 与任何数字配对
	%l: 与任何小写字母配对
	%p: 与任何标点(punctuation)配对
	%s: 与空白字符配对
	%u: 与任何大写字母配对
	%w: 与任何字母/数字配对
	%x: 与任何十六进制数配对
	%z: 与任何代表0的字符配对
	%x(此处x是非字母非数字字符): 与字符x配对. 主要用来处理表达式中有功能的字符(^$()%.[]*+-?)的配对问题, 例如%%与%配对
	[数个字符类]: 与任何[]中包含的字符类配对. 例如[%w_]与任何字母/数字, 或下划线符号(_)配对
	[^数个字符类]: 与任何不包含在[]中的字符类配对. 例如[^%s]与任何非空白字符配对

	当上述的字符类用大写书写时, 表示与非此字符类的任何字符配对. 例如, %S表示与任何非空白字符配对.例如，'%A'非字母的字符
	print(string.gsub("hello, up-down!", "%A", "."))
	    --> hello..up.down. 4
	（数字4不是字符串结果的一部分，他是gsub返回的第二个结果，代表发生替换的次数。下面其他的关于打印gsub结果的例子中将会忽略这个数值。）在模式匹配中有一些特殊字符，他们有特殊的意义，Lua中的特殊字符如下：
	( ) . % + - * ? [ ^ $
	'%' 用作特殊字符的转义字符，因此 '%.' 匹配点；'%%' 匹配字符 '%'。转义字符 '%'不仅可以用来转义特殊字符，还可以用于所有的非字母的字符。当对一个字符有疑问的时候，为安全起见请使用转义字符转义他。
	对Lua而言，模式串就是普通的字符串。他们和其他的字符串没有区别，也不会受到特殊对待。只有他们被用作模式串用于函数的时候，'%' 才作为转义字符。所以，如果你需要在一个模式串内放置引号的话，你必须使用在其他的字符串中放置引号的方法来处理，使用 '\' 转义引号，'\' 是Lua的转义符。你可以使用方括号将字符类或者字符括起来创建自己的字符类（译者：Lua称之为char-set，就是指传统正则表达式概念中的括号表达式）。比如，'[%w_]' 将匹配字母数字和下划线，'[01]' 匹配二进制数字。
--]]
s = "hello world from Lua"
--for w in string.gmatch(s, "%a+") do
--    print(w)
--end

s = string.gsub("hello world from Lua", "(%w+)%s?(%w+)%s?(%w+)%s?(%w+)%s?", "%4 %3 %2 %1")
print(s)

print(string.gsub("hello world", "(%w+)", "%1 %1"))


--file
local file = io.open("text1.txt","r")
local str = file:read("*a")
file:close()
local newStr = string.gsub(str,"aaa","bbb")
print(newStr)