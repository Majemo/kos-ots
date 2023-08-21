//
// Created by Admin on 17.08.2023.
//

#include "treasure_chest_monster.h"
TreasureChestMonster::TreasureChestMonster(MonsterType* mType) :
	Monster(mType) { }
TreasureChestMonster* TreasureChestMonster::createTreasureChestMonster(std::string monsterName, TreasureChest* treasureChest) {
	MonsterType* mType = g_monsters().getMonsterType(monsterName);
	if (!mType) {
		return nullptr;
	}
	TreasureChestMonster* treasureChestMonster = new TreasureChestMonster(mType);
	treasureChestMonster->treasureChest = treasureChest;

	return treasureChestMonster;
}
void TreasureChestMonster::death(Creature* creature) {
	Creature::death(creature);
	treasureChest->onMonsterDeath(this);
}
