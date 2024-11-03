#ifndef CUSTOMER_ORDER_INTERACTOR_H
#define CUSTOMER_ORDER_INTERACTOR_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>


namespace godot {

class CustomerInteractor : public Interaction{
    GDCLASS(CustomerInteractor, Interaction);

protected:
    static void _bind_methods();

public:
    bool _interact(Entity *p_entity) override;
	Interaction *_clone() override;

    CustomerInteractor();
    ~CustomerInteractor();

};

}

#endif //CUSTOMER_ORDER_INTERACTOR_H