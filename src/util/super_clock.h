#ifndef SUPER_CLOCK_H
#define SUPER_CLOCK_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>


namespace godot {

class SuperClock : public Node3D{
    GDCLASS(SuperClock, Node3D);

protected:
    static void _bind_methods();

    NodePath order_getter_path;

public:
    

    SuperClock();
    ~SuperClock();

};

}

#endif //SUPER_CLOCK_H