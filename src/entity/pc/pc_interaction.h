#ifndef PC_INTERACTOR_H
#define PC_INTERACTOR_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/input.hpp>

#include "hud/pc_view_model.h"


namespace godot {

class PcInteractor : public Interaction{
    GDCLASS(PcInteractor, Interaction);

protected:
    static void _bind_methods();

public:
    bool _interact(Entity *p_entity) override;
	Interaction *_clone() override;

    PcInteractor();
    ~PcInteractor();

};

}

#endif //PC_INTERACTOR_H