pos = vec2.new()
pos.x = 100
pos.y = 100
function Start()
end
function Update()
	setPosition(Quad,pos)
end
function HandleInput(key)
	if key == KEY_P then
		pos.x = pos.x + 10;
	end
end