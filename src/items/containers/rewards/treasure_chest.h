//
// Created by Admin on 17.08.2023.
//

#ifndef CANARY_TREASURE_CHEST_H
#define CANARY_TREASURE_CHEST_H

#include <cstdint>
#include <string>
#include "items/containers/container.h"
#include "creatures/players/player.h"
#include "game/movement/position.h"
#include "treasure_chests.h"

class TreasureChest final : public Container {
	public:
		explicit TreasureChest(uint16_t type);
		TreasureChest* getTreasureChest() final {
			return this;
		}
		const TreasureChest* getTreasureChest() const final {
			return this;
		}
		static TreasureChest* CreateTreasureChest(const uint16_t type, Player* player, BaseTreasureChest baseTreasureChest);
		ReturnValue queryAdd(int32_t index, const Thing &thing, uint32_t count, uint32_t flags, Creature* actor = nullptr) const final;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, CylinderLink_t link = LINK_OWNER) final;
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, CylinderLink_t link = LINK_OWNER) final;

		bool canRemove() const final {
			return false;
		}

		void removeItem(Thing* thing, bool sendToClient = false) override;
		std::string getDescription(int32_t lookDistance) const override;
		const std::string &getName() const {
			return baseTreasureChest->name;
		}

		void start();
		void yell(std::string message);
		bool isCompleted();
		bool isStarted();
		void spawn();

	private:
		Player* player = nullptr;
		const Position* position = nullptr;
		Tile* tile;
		int stage = 0;
		bool started = false;
		bool completed = false;
		const BaseTreasureChest* baseTreasureChest = nullptr;
};

#endif // CANARY_TREASURE_CHEST_H
