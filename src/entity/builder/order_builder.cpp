#include "order_builder.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::OrderBuilder::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_order"), &OrderBuilder::create_order);
    ClassDB::bind_method(D_METHOD("set_fact_level"), &OrderBuilder::set_fact_level);
    ClassDB::bind_method(D_METHOD("set_name"), &OrderBuilder::set_name);
    ClassDB::bind_method(D_METHOD("set_image"), &OrderBuilder::set_image);
    ClassDB::bind_method(D_METHOD("set_descr"), &OrderBuilder::set_descr);
    ClassDB::bind_method(D_METHOD("get_entity"), &OrderBuilder::get_entity);
}

void godot::OrderBuilder::create_order()
{
    this->entity = memnew(Entity);
    this->data = memnew(EntityDataImpl);
}

void godot::OrderBuilder::set_fact_level(int fact_level)
{
    if(!data){
        UtilityFunctions::print("OrderBuilder: data is null");
        return;
    }
    data->put_int(OrderParams::fact_rank(), fact_level);
}

void godot::OrderBuilder::set_name(String name)
{
    if(!data){
        UtilityFunctions::print("OrderBuilder: data is null");
        return;
    }
    data->put_string(OrderParams::name(), name);
}

void godot::OrderBuilder::set_image(String img)
{
    if(!data){
        UtilityFunctions::print("OrderBuilder: data is null");
        return;
    }
    data->put_string(OrderParams::img(), img);
}

void godot::OrderBuilder::set_descr(String descr)
{
    if(!data){
        UtilityFunctions::print("OrderBuilder: data is null");
        return;
    }
    data->put_string(OrderParams::descr(), descr);
}

godot::Entity *godot::OrderBuilder::get_entity()
{
    if(!data){
        UtilityFunctions::print("OrderBuilder: data is null");
        return nullptr;
    }
    if(!entity){
        UtilityFunctions::print("OrderBuilder: entity is null");
        return nullptr; 
    }
    entity->set_data(data);

    return entity;
}

godot::OrderBuilder::OrderBuilder()
{
}

godot::OrderBuilder::~OrderBuilder()
{
}
