#include "trigger_clock.h"

void godot::TriggerClock::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_clock_path"), &TriggerClock::set_clock_path);
    ClassDB::bind_method(D_METHOD("get_clock_path"), &TriggerClock::get_clock_path);

    ClassDB::add_property("TriggerClock", PropertyInfo(Variant::NODE_PATH, "clock_path"), "set_clock_path", "get_clock_path");
}

void godot::TriggerClock::set_clock_path(NodePath p_clock_path)
{
    this->clock_path = p_clock_path;
}

godot::NodePath godot::TriggerClock::get_clock_path()
{
    return this->clock_path;
}

bool godot::TriggerClock::_activate()
{
    if(has_node(clock_path) && get_node<SuperClock>(clock_path)){
        SuperClock *clock = get_node<SuperClock>(clock_path);
        clock->activate_timer();
    }
    return false;
}

godot::TriggerClock::TriggerClock()
{
}

godot::TriggerClock::~TriggerClock()
{
}
