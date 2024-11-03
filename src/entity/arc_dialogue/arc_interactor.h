#ifndef ARC_INTERACTOR_H
#define ARC_INTERACTOR_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/view_model.hpp>

#include "hud/arc_view_model.h"
#include "variants/dialogues/arc_dialogue.h"

namespace godot {

class ArcInteractor : public Interaction{
    GDCLASS(ArcInteractor, Interaction);

protected:
    static void _bind_methods();
    String element_id;

public:
    bool _interact(Entity *p_entity) override;
	Interaction *_clone() override;

    void set_element_id(String p_element_id);
    String get_element_id();

    ArcInteractor();
    ~ArcInteractor();

};

}

#endif //ARC_INTERACTOR_H