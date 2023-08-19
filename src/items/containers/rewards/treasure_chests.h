//
// Created by Admin on 18.08.2023.
//

#ifndef CANARY_TREASURE_CHESTS_H
#define CANARY_TREASURE_CHESTS_H

#include <utility>
#include <vector>
#include <string>


struct BaseTreasureChestWave {
		BaseTreasureChestWave(std::vector<std::string> initMonsters) : monsters(initMonsters) {}
		std::vector<std::string> monsters;
};


struct BaseTreasureChest {
		BaseTreasureChest(uint32_t initMinLevel,uint32_t initMaxLevel, std::string initName, std::string initBoss, std::vector<BaseTreasureChestWave> initWaves) : minLevel(initMinLevel),maxLevel(initMaxLevel),name(std::move(initName)),boss(std::move(initBoss)),waves(initWaves) {}
		uint32_t minLevel;
		uint32_t maxLevel;
		std::string name;
		std::string boss;
		std::vector<BaseTreasureChestWave> waves;
};


class TreasureChests {
	public:
		TreasureChests() = default;

		TreasureChests(const TreasureChests &) = delete;
		void operator=(const TreasureChests &) = delete;

		static TreasureChests &getInstance() {
			// Guaranteed to be destroyed
			static TreasureChests instance;
			// Instantiated on first use
			return instance;
		}

		bool loadFromXml();
		std::vector<BaseTreasureChest> getTreasureChests();
	protected:
		bool loaded = false;
		std::vector<BaseTreasureChest> basesTreasureChests;
};

constexpr auto g_treasureChests = &TreasureChests::getInstance;

#endif // CANARY_TREASURE_CHESTS_H
