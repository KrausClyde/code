function domain(i)  
--[[		  
    -- call C function.  
    local tab = gettab()   
		  
   -- show key and value  
   for k, v in pairs(tab) do  
        print("key: ".. k)  
        print("val: ".. v)  
	    print()  
    end  
	--]]
	print("test.lua")

end

function func1 (n)
    if n == 0 then
        print(0)
		return 1
	else
        print(n)
        return n * func1 (n - 1)
    end
	return 1
end

function test()
	print("lua function test() called")
	readfile("text.txt")
end

function NA()
	print("lua function NA() called")
end

--功能：读取文件  
--输入：文件名  
--输出：屏幕上一行一行显示文件里的内容  
function readfile(filename)  
    local rfile=io.open(filename, "r+") --读取文件(r读取)  
    assert(rfile)                   --打开时验证是否出错  
    rfile:seek("set")
	for str in rfile:lines() do     --一行一行的读取  
        print(str)                  --显示在屏幕上  
        string = replace(str, nil, nil)
		rfile:write("aaaaaaa")
	end  
    rfile:close()                   --调用结束后记得关闭  
end 

function replace(string, from, to)
    if string.gmatch(string, "tt", "show") then
	    string = string.gsub(string, "tt", "show")
	end
	print(string)
	return string
end
