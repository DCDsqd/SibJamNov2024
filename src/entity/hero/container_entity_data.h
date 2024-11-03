#ifndef HERO_ENTITY_DATA_H
#define HERO_ENTITY_DATA_H

#include <godot_cpp/classes/entity_data_impl.hpp>
#include "entity/order/order_container.h"

namespace godot {

class ContainerEntityData : public EntityDataImpl {
	GDCLASS(ContainerEntityData, EntityDataImpl)

protected:
	static void _bind_methods();

    OrderContainer *order_container = nullptr;

public:
	void set_order_container(OrderContainer *p_order_container);
	OrderContainer *get_order_container();


	ContainerEntityData();
	~ContainerEntityData();
};

}

#endif //HUMAN_INPUT_H