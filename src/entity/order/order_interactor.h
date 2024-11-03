#ifndef ORDER_INTERACTOR_H
#define ORDER_INTERACTOR_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include "hud/order_hud.h"
#include "entity/hero/container_entity_data.h"


namespace godot {

class OrderInteractor : public Interaction{
    GDCLASS(OrderInteractor, Interaction);

protected:
    static void _bind_methods();

public:
    bool _interact(Entity *p_entity) override;
	Interaction *_clone() override;

    OrderInteractor();
    ~OrderInteractor();

};

}

#endif //ORDER_INTERACTOR_H