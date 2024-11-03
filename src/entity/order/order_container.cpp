#include "order_container.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"

void godot::OrderContainer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("add_order"), &OrderContainer::add_order);
    ClassDB::bind_method(D_METHOD("get_order"), &OrderContainer::get_order);
}

bool godot::OrderContainer::check_order(Entity *entity)
{
    return true;
}

void godot::OrderContainer::add_order(Entity *entity)
{
    if(!check_order(entity)){
        UtilityFunctions::print("OrderContainer: order is incorrect");
        return;
    }

    this->orders.push_back(entity);
}

int godot::OrderContainer::get_orger_count()
{
    return this->orders.size();
}

godot::Entity *godot::OrderContainer::get_order(int i)
{
    if(this->orders.size() < i){
        UtilityFunctions::print("OrderContainer: order: " + Util::int_to_godot_str(i) + " out of range");
        return nullptr;
    }
    return this->orders[i];
}

void godot::OrderContainer::remove_order(int i)
{
    if(this->orders.size() < i){
        UtilityFunctions::print("OrderContainer: order: " + Util::int_to_godot_str(i) + " out of range");
        return;
    }

    this->orders.erase(this->orders.begin() + i - 1);
}

godot::OrderContainer::OrderContainer()
{
}

godot::OrderContainer::~OrderContainer()
{
}
