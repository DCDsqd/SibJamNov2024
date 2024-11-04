#ifndef CUSTOMER_INTERACTOR_H
#define CUSTOMER_INTERACTOR_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include <godot_cpp/classes/game_controller.hpp>
#include <godot_cpp/classes/trigger3d.hpp>

#include "entity/arc_dialogue/arc_interactor.h"
#include "hud/custommer_view_model.h"


namespace godot {

class CustomerInteractor : public Interaction{
    GDCLASS(CustomerInteractor, Interaction);

protected:
    static void _bind_methods();

    bool play_dialogue(String element_id, Entity *p_entity);
    bool open_hud(Entity *p_entity);
    bool event_switcher(Entity *p_entity, EntityData *data);

    bool try_swap_custommer();

public:
    bool _interact(Entity *p_entity) override;
	Interaction *_clone() override;

    CustomerInteractor();
    ~CustomerInteractor();

};

}

#endif //CUSTOMER_INTERACTOR_H