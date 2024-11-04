#include "trigger_clock.h"

void godot::TriggerClock::_bind_methods()
{
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
