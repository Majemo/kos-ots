local ipBanDays = 7

local ipBan = TalkAction("/ipban")

function ipBan.onSay(player, words, param)
	if param == "" then
		player:sendCancelMessage("Command param required.")
		return false
	end

	local resultId = db.storeQuery("SELECT `name`, `lastip` FROM `players` WHERE `name` = " .. db.escapeString(param))
	if resultId == false then
		return false
	end

	local targetName = Result.getString(resultId, "name")
	local targetIp = Result.getNumber(resultId, "lastip")
	Result.free(resultId)

	local targetPlayer = Player(param)
	if targetPlayer then
		targetIp = targetPlayer:getIp()
		targetPlayer:remove()
	end

	if targetIp == 0 then
		return false
	end

	resultId = db.storeQuery("SELECT 1 FROM `ip_bans` WHERE `ip` = " .. targetIp)
	if resultId ~= false then
		player:sendTextMessage(MESSAGE_ADMINISTRADOR, targetName .. "  is already IP banned.")
		Result.free(resultId)
		return false
	end

	local timeNow = os.time()
	db.query("INSERT INTO `ip_bans` (`ip`, `reason`, `banned_at`, `expires_at`, `banned_by`) VALUES (" ..
			targetIp .. ", '', " .. timeNow .. ", " .. timeNow + (ipBanDays * 86400) .. ", " .. player:getGuid() .. ")")
	player:sendTextMessage(MESSAGE_ADMINISTRADOR, targetName .. "  has been IP banned.")
	return false
end

ipBan:separator(" ")
ipBan:groupType("god")
ipBan:register()
