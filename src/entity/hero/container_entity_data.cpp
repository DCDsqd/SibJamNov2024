#include "container_entity_data.h"

void godot::ContainerEntityData::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_order_container"), &ContainerEntityData::set_order_container);
    ClassDB::bind_method(D_METHOD("get_order_container"), &ContainerEntityData::get_order_container);
}

void godot::ContainerEntityData::set_order_container(OrderContainer *p_order_container)
{
    this->order_container = p_order_container;
}

godot::OrderContainer *godot::ContainerEntityData::get_order_container()
{
    return this->order_container;
}

godot::ContainerEntityData::ContainerEntityData()
{
}

godot::ContainerEntityData::~ContainerEntityData()
{
}
