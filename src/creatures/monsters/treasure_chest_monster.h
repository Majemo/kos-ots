//
// Created by Admin on 17.08.2023.
//

#ifndef CANARY_TREASURE_CHEST_MONSTER_H
#define CANARY_TREASURE_CHEST_MONSTER_H

#include "monster.h"
class TreasureChestMonster final : public Monster {
	public:
		explicit TreasureChestMonster(MonsterType* mType);
		static TreasureChestMonster* createTreasureChestMonster(MonsterType* mType, TreasureChest* treasureChest);
	private:
		TreasureChest* treasureChest;
};

#endif // CANARY_TREASURE_CHEST_MONSTER_H
