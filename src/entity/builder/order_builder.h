#ifndef ORDER_BUILDER_H
#define ORDER_BUILDER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/entity_data.hpp>
#include <godot_cpp/classes/entity_data_impl.hpp>
#include <godot_cpp/classes/entity_builder.hpp>

#include "variants/const/order_params.hpp"

namespace godot {

class OrderBuilder : public Object {
	GDCLASS(OrderBuilder, Object)

protected:
	static void _bind_methods();

    Entity *entity = nullptr;
    EntityData *data = nullptr;

public:
    void create_order();

    void set_fact_level(int fact_level);
    void set_name(String name);
    void set_image(String img);
    void set_descr(String descr);

    Entity *get_entity();

	OrderBuilder();
	~OrderBuilder();
};

}

#endif //ENTITY_BUILDER_H