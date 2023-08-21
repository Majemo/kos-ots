local aol = TalkAction("!tp")


local config = {
	{ name="Duke Krull", position = Position(32369, 32150, 7) },
	{ name="Falcon Bastion", position = Position(33374, 31349, 7) },
	{ name="Trainer", position = Position(33375, 31320, 12) },
	{ name="Temple", position = Position(32369, 32241, 7) }
}
function aol.onSay(player, words, param)
	local menu = ModalWindow{
		title = "Teleport Modal",
		message = "Locations"
	}

	for i, info in pairs(config) do
		menu:addChoice(string.format("%s", info.name), function (player, button, choice)
			if button.name ~= "Select" then
				return
			end

			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You were teleported to " .. info.name)
			player:teleportTo(info.position)
		end)
	end

	menu:addButton("Select")
	menu:addButton("Close")
	menu:sendToPlayer(player)
	return false
end

aol:groupType("normal")
aol:register()
