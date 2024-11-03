#ifndef ORDER_BEHAIVOR_H
#define ORDER_BEHAIVOR_H

#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/entity_data.hpp>
#include <godot_cpp/classes/moving_entity.hpp>
#include <godot_cpp/classes/void_behaivor.hpp>
#include "entity/hero/container_entity_data.h"

namespace godot {

class OrderBehaivor : public VoidBehaivor {
	GDCLASS(OrderBehaivor, VoidBehaivor)

protected:
	static void _bind_methods();

    void generate_orders();

public:
    void _set_entity(ModelEntity *p_entity) override;
	void _int_process() override;

	OrderBehaivor();
	~OrderBehaivor();
};

}

#endif //HERO_BEHAIVOR_H