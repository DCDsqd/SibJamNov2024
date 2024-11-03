#ifndef ORDER_CONTAINER_H
#define ORDER_CONTAINER_H

#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>


namespace godot {

class OrderContainer : public Object{
    GDCLASS(OrderContainer, Object);

protected:
    static void _bind_methods();

    std::vector<Entity*> orders;


public:

    OrderContainer();
    ~OrderContainer();

};

}

#endif //ORDER_CONTAINER_H