#include "pc_interaction.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::PcInteractor::_bind_methods()
{
}

bool godot::PcInteractor::_interact(Entity *p_entity)
{
    UtilityFunctions::print("PcInteractor: intreact");
    return true;
}

godot::Interaction *godot::PcInteractor::_clone()
{
    return new PcInteractor();
}

godot::PcInteractor::PcInteractor()
{
}

godot::PcInteractor::~PcInteractor()
{
}
