#include "trigger_next_customer.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::TriggerNextCustomer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_clock_path"), &TriggerNextCustomer::set_clock_path);
    ClassDB::bind_method(D_METHOD("get_clock_path"), &TriggerNextCustomer::get_clock_path);

    ClassDB::add_property("TriggerNextCustomer", PropertyInfo(Variant::NODE_PATH, "clock_path"), "set_clock_path", "get_clock_path");
}

void godot::TriggerNextCustomer::set_clock_path(NodePath p_clock_path)
{
    this->clock_path = p_clock_path;
}

godot::NodePath godot::TriggerNextCustomer::get_clock_path()
{
    return this->clock_path;
}

bool godot::TriggerNextCustomer::_activate()
{
    if(has_node(clock_path) && get_node<SuperClock>(clock_path)){
        SuperClock *clock = get_node<SuperClock>(clock_path);
        clock->acess_customer();
    }
    return false;
}

godot::TriggerNextCustomer::TriggerNextCustomer()
{
}

godot::TriggerNextCustomer::~TriggerNextCustomer()
{
}
