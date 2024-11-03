#ifndef HERO_ENTITY_DATA_H
#define HERO_ENTITY_DATA_H

#include <godot_cpp/classes/entity_data_impl.hpp>
#include "entity/order/order_container.h"

namespace godot {

class HeroEntityData : public EntityDataImpl {
	GDCLASS(HeroEntityData, EntityDataImpl)

protected:
	static void _bind_methods();

    OrderContainer *order_container = nullptr;

public:

	HeroEntityData();
	~HeroEntityData();
};

}

#endif //HUMAN_INPUT_H