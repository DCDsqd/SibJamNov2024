#include "order_interactor.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"

void godot::OrderInteractor::_bind_methods()
{

}

bool godot::OrderInteractor::_interact(Entity *p_entity)
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(!hud){
        UtilityFunctions::print("ArcInteractor: hud is null");
        return false;
    }

    String arc_view_model_path = Util::get_value_from_config("ref_config", "order_hud");
    Node *node = Util::spawn_node(arc_view_model_path);

    if(!node){
        UtilityFunctions::print("ArcInteractor: viewmodel is null");
        return false;
    }

    ViewModel *view_model = Object::cast_to<ViewModel>(node);
    if(!view_model){
        UtilityFunctions::print("ArcInteractor: viewmodel is not ViewModel");
        return false;
    }

    OrderHud *order_hud = Object::cast_to<OrderHud>(view_model);
    if(!view_model){
        UtilityFunctions::print("ArcInteractor: viewmodel is not OrderHud");
        return false;
    }
    
    
    hud->add_child(order_hud);
    order_hud->open_window(get_entity(), p_entity);

    return true;
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
