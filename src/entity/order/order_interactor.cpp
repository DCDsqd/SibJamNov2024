#include "order_interactor.h"

bool godot::OrderInteractor::_interact(Entity *p_entity)
{
    return false;
}

godot::Interaction *godot::OrderInteractor::_clone()
{
    return new OrderInteractor();
}

godot::OrderInteractor::OrderInteractor()
{
}

godot::OrderInteractor::~OrderInteractor()
{
}
