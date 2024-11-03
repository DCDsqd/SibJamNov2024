#ifndef CUSTOMMER_BUILDER_H
#define CUSTOMMER_BUILDER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/entity_data.hpp>
#include <godot_cpp/classes/entity_data_impl.hpp>
#include <godot_cpp/classes/entity_builder.hpp>

#include "variants/const/customer_params.hpp"

namespace godot {

class CustommerBuilder : public Object {
	GDCLASS(CustommerBuilder, Object)

protected:
	static void _bind_methods();

    EntityData *data = nullptr;

public:
    void set_data(EntityData *p_data);

    void set_name(String name);
    void set_fact_level(int fact_level);
    void set_display_level(int display_level);
    void set_min_req_level(int min_req_level);
    void set_dialogue_id(String dialogue_id);
    void set_state(int state);

    EntityData *get_data();

	CustommerBuilder();
	~CustommerBuilder();
};

}

#endif //CUSTOMMER_BUILDER_H