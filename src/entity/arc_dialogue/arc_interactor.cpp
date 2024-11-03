#include "arc_interactor.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"
//#include "util/constants.hpp"

void godot::ArcInteractor::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_element_id"), &ArcInteractor::set_element_id);
    ClassDB::bind_method(D_METHOD("get_element_id"), &ArcInteractor::get_element_id);
}

bool godot::ArcInteractor::_interact(Entity *p_entity)
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(!hud){
        UtilityFunctions::print("ArcInteractor: hud is null");
        return false;
    }

    String arc_view_model_path = Util::get_value_from_config("ref_config", "arc_view_model");
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

    ArcViewModel *arc_view_model = Object::cast_to<ArcViewModel>(view_model);
    if(!view_model){
        UtilityFunctions::print("ArcInteractor: viewmodel is not ArcViewModel");
        return false;
    }
    
    ArcDialogue *dialogue = new ArcDialogue();
    dialogue->set_id(element_id);
    
    arc_view_model->set_dialogue(dialogue);
    hud->add_child(arc_view_model);
    arc_view_model->open_window(get_entity(), p_entity);

    return true;
}

godot::Interaction *godot::ArcInteractor::_clone()
{
    return nullptr;
}

void godot::ArcInteractor::set_element_id(String p_element_id)
{
    this->element_id = p_element_id;
}

godot::String godot::ArcInteractor::get_element_id()
{
    return this->element_id;
}

godot::ArcInteractor::ArcInteractor()
{
}

godot::ArcInteractor::~ArcInteractor()
{
}
