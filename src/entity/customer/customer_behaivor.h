#ifndef CUSTOMMER_BEHAIVOR_H
#define CUSTOMMER_BEHAIVOR_H

#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/entity_data.hpp>
#include <godot_cpp/classes/moving_entity.hpp>
#include <godot_cpp/classes/void_behaivor.hpp>

namespace godot {

class CustomerBehaivor : public VoidBehaivor {
	GDCLASS(CustomerBehaivor, VoidBehaivor)

protected:
	static void _bind_methods();

    void update_texture();

public:
    void _set_entity(ModelEntity *p_entity) override;
	void _int_process() override;


	CustomerBehaivor();
	~CustomerBehaivor();
};

}

#endif //CUSTOMMER_BEHAIVOR_H