//
// Created by Admin on 17.08.2023.
//

#include <string>
#include "treasure_chest.h"
#include "game/game.h"
#include "creatures/monsters/treasure_chest_monster.h"
TreasureChest::TreasureChest(uint16_t type) :
	Container(type) { }

ReturnValue TreasureChest::queryAdd(int32_t, const Thing &, uint32_t, uint32_t, Creature* actor /* = nullptr*/) const {
	if (actor) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	return RETURNVALUE_NOERROR;
}

void TreasureChest::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, CylinderLink_t) {
	if (parent != nullptr) {
		parent->postAddNotification(thing, oldParent, index, LINK_PARENT);
	}
}

void TreasureChest::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, CylinderLink_t) {
	if (parent != nullptr) {
		parent->postRemoveNotification(thing, newParent, index, LINK_PARENT);
	}
}

// Second argument is disabled by default because not need to send to client in the TreasureChest
void TreasureChest::removeItem(Thing* thing, bool /* sendToClient = false*/) {
	if (thing == nullptr) {
		return;
	}

	auto itemToRemove = thing->getItem();
	if (itemToRemove == nullptr) {
		return;
	}

	auto it = std::ranges::find(itemlist.begin(), itemlist.end(), itemToRemove);
	if (it != itemlist.end()) {
		itemlist.erase(it);
		itemToRemove->setParent(nullptr);
	}
}
std::string TreasureChest::getDescription(int32_t lookDistance) const {
	std::ostringstream ss;
	ss << "Treasure Chest it belongs to ";
	ss << player->getName();
	return ss.str();
}
TreasureChest* TreasureChest::CreateTreasureChest(const uint16_t type, Player* player, const BaseTreasureChest& baseTreasureChest) {
	TreasureChest* treasureChest = new TreasureChest(type);
	treasureChest->player = player;
	treasureChest->position = &player->getPosition();
	treasureChest->tile = player->getTile();
	treasureChest->baseTreasureChest = &baseTreasureChest;

	treasureChest->incrementReferenceCounter();

	return treasureChest;
}

void TreasureChest::yell(std::string message) {
	player->sendCreatureSay(player, TALKTYPE_MONSTER_SAY, message, position);
}
bool TreasureChest::isCompleted() {
	return completed;
}
bool TreasureChest::isStarted() {
	return started;
}
void TreasureChest::start() {
	started = false;
	completed = true;
}
void TreasureChest::startWave() {
	BaseTreasureChestWave wave = baseTreasureChest->waves[stage];
	currentWave.clear();



}

void TreasureChest::spawn() {
	g_game().internalAddItem(tile, this, INDEX_WHEREEVER, FLAG_NOLIMIT);
	this->dropLoot();
}
void TreasureChest::dropLoot() {
	Item* remaindItem = Item::CreateItem(ITEM_CRYSTAL_COIN, 100);
	int64_t rewardId = getTimeMsNow();
	Reward* itemReward = player->getReward(rewardId, true);
	SPDLOG_ERROR("item id {}", baseTreasureChest->rewards.size());
	for (BaseTreasureChestReward reward : baseTreasureChest->rewards) {
		SPDLOG_ERROR("item id {}", reward.itemId);
		Item* item = Item::CreateItem(reward.itemId, 1);
		itemReward->addItem(item);
	}

	Item* item = Item::CreateItem(ITEM_CRYSTAL_COIN, 1);
	itemReward->addItem(item);
	this->setAttribute(ItemAttribute_t::DATE, rewardId);
	this->addThing(itemReward);
	std::ostringstream lootMessage;
	lootMessage << "Loot of " << getNameDescription() << ": " << itemReward->getContainer()->getContentDescription(player->getProtocolVersion() < 1200);
	auto suffix = itemReward->getContainer()->getAttribute<std::string>(ItemAttribute_t::LOOTMESSAGE_SUFFIX);
	if (!suffix.empty()) {
		lootMessage << suffix;
	}
	player->sendLootMessage(lootMessage.str());

}
void TreasureChest::onMonsterDeath(TreasureChestMonster* killedMonster) {
}
