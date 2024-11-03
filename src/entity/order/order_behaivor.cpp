#include "order_behaivor.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::OrderBehaivor::_bind_methods()
{
}

void godot::OrderBehaivor::generate_orders()
{
    ModelEntity *mentity = get_entity();
    if(!mentity){
        UtilityFunctions::print("OrderBehaivor: mentity is null");
        return;
    }

    Entity *entity = mentity->get_entity();

    if(!entity){
        UtilityFunctions::print("OrderBehaivor: entity is null");
        return;
    }

    EntityData *data = entity->get_data();
    if(!data){
        UtilityFunctions::print("OrderBehaivor: entity is null");
        return;
    }

    ContainerEntityData *container = Object::cast_to<ContainerEntityData>(data);
    if(!container){
        UtilityFunctions::print("OrderBehaivor: data is not ContainerEntityData");
    }

    
}

void godot::OrderBehaivor::_set_entity(ModelEntity *p_entity)
{
}

void godot::OrderBehaivor::_int_process()
{
}

godot::OrderBehaivor::OrderBehaivor()
{
}

godot::OrderBehaivor::~OrderBehaivor()
{
}
