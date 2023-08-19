//
// Created by Admin on 17.08.2023.
//

#include "treasure_chest_monster.h"
TreasureChestMonster::TreasureChestMonster(MonsterType* mType) :
	Monster(mType) { }
TreasureChestMonster* TreasureChestMonster::createTreasureChestMonster(MonsterType* mType, TreasureChest* treasureChest) {
	TreasureChestMonster* treasureChestMonster = new TreasureChestMonster(mType);
	treasureChestMonster->treasureChest = treasureChest;

	return treasureChestMonster;
}
