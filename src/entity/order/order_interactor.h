#ifndef ORDER_INTERACTOR_H
#define ORDER_INTERACTOR_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>


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