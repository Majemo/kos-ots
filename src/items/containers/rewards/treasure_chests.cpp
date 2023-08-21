//
// Created by Admin on 18.08.2023.
//


#include "pch.hpp"

#include "config/configmanager.h"
#include "treasure_chests.h"
#include "lua/scripts/scripts.h"
#include "utils/pugicast.h"
#include "utils/tools.h"

bool TreasureChests::loadFromXml() {
	pugi::xml_document doc;
	auto folder = g_configManager().getString(CORE_DIRECTORY) + "/XML/treasure_chests.xml";
	pugi::xml_parse_result result = doc.load_file(folder.c_str());
	if (!result) {
		printXMLError(__FUNCTION__, folder, result);
		return false;
	}

	loaded = true;
	for (const auto &treasureChestNode : doc.child("treasure_chests").children()) {
		pugi::xml_node wavesAttribute = treasureChestNode.child("waves");
		if (!wavesAttribute) {
			SPDLOG_WARN("Missing waves");
			continue;
		}


		uint32_t minLevel = pugi::cast<uint32_t>(treasureChestNode.attribute("minLevel").value());
		uint32_t maxLevel = pugi::cast<uint32_t>(treasureChestNode.attribute("maxLevel").value());
		std::string name = treasureChestNode.attribute("name").as_string();
		std::string boss = wavesAttribute.attribute("boss").as_string();
		std::vector<BaseTreasureChestWave> waves = std::vector<BaseTreasureChestWave>();
		std::vector<BaseTreasureChestReward> rewards = std::vector<BaseTreasureChestReward>();


		for (const auto &waveNode : treasureChestNode.child("waves").children()) {
			auto monsters = std::vector<std::string>();
			for (auto monsterNode : waveNode.children()) {
				monsters.push_back(monsterNode.attribute("name").as_string());
			}
			waves.emplace_back(monsters);
		}



		for (const auto &rewardNode : treasureChestNode.child("rewards").children()) {
			SPDLOG_ERROR("id {}", rewardNode.attribute("id").value());
			rewards.emplace_back(
				static_cast<uint16_t>(pugi::cast<uint16_t>(rewardNode.attribute("id").value())),
				static_cast<int8_t>(pugi::cast<uint16_t>(rewardNode.attribute("chance").value())),
				static_cast<int32_t>(pugi::cast<int32_t>(rewardNode.attribute("minAmount").value())),
				static_cast<int32_t>(pugi::cast<int32_t>(rewardNode.attribute("maxAmount").value()))
			);
		}
		basesTreasureChests.emplace_back(BaseTreasureChest(minLevel,maxLevel,name, boss, waves, rewards));



	}

	return true;
}
std::vector<BaseTreasureChest> TreasureChests::getTreasureChests() {
	return basesTreasureChests;
}
