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
