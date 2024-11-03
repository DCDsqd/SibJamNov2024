#ifndef ENTITY_BUILDER_H
#define ENTITY_BUILDER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/entity_data.hpp>
#include <godot_cpp/classes/entity_builder.hpp>

namespace godot {

class SimpleEntityBuilder : public EntityBuilder {
	GDCLASS(SimpleEntityBuilder, EntityBuilder)

protected:
	static void _bind_methods();

public:

	SimpleEntityBuilder();
	~SimpleEntityBuilder();
};

}

#endif //ENTITY_BUILDER_H