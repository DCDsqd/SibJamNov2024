#include "pc_interaction.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"



void godot::PcInteractor::_bind_methods()
{
}


bool godot::PcInteractor::_interact(Entity *p_entity)
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(!hud){
        UtilityFunctions::print("ArcInteractor: hud is null");
        return false;
    }

    String pc_view_model = Util::get_value_from_config("ref_config", "pc_view_model");
    Node *node = Util::spawn_node(pc_view_model);

    if(!node){
        UtilityFunctions::print("ArcInteractor: viewmodel is null");
        return false;
    }

    ViewModel *view_model = Object::cast_to<ViewModel>(node);
    if(!view_model){
        UtilityFunctions::print("ArcInteractor: viewmodel is not ViewModel");
        return false;
    }

    PcViewModel *order_hud = Object::cast_to<PcViewModel>(view_model);
    if(!view_model){
        UtilityFunctions::print("ArcInteractor: viewmodel is not OrderHud");
        return false;
    }
    
    
    hud->add_child(order_hud);
    order_hud->open_window(get_entity(), p_entity);

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
