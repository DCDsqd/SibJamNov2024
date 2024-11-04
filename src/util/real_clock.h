#ifndef REAL_CLOCK_H
#define REAL_CLOCK_H

#include <godot_cpp/classes/node3d.hpp>

namespace godot{

class SuperClock : public Node3D{
    GDCLASS(SuperClock, Node3D);

protected:
    static void _bind_methods();

public:

    SuperClock();
    ~SuperClock();

};

}

#endif //REAL_CLOCK_H