
function UI::OnDraw(drawList) {
    print("called")
}

print("-------------------------")

foreach(k,v in this["ST_UIS"]) {
    print(k)
    foreach(n,f in v) {
    	print(n)
    	print(f)
    	
    	if (n == "OnDraw") {
    		f(null)
    	}
    }
}


