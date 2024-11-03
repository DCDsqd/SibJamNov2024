#include "customer_interactor.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::CustomerInteractor::_bind_methods()
{
}

bool godot::CustomerInteractor::_interact(Entity *p_entity)
{
    UtilityFunctions::print("CustomerInteractor: interact");

    

    return true;
}

godot::Interaction *godot::CustomerInteractor::_clone()
{
    return new Interaction();
}

godot::CustomerInteractor::CustomerInteractor()
{
}

godot::CustomerInteractor::~CustomerInteractor()
{
}
