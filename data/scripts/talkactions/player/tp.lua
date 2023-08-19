local aol = TalkAction("!tp")

teleports = {
	['Death Priest Shargon'] = {x = 33594, y = 31851, z = 10}
}

function aol.onSay(player, words, param)
	player:teleportTo(Position(33594, 31851, 10))
end

aol:groupType("normal")
aol:register()
