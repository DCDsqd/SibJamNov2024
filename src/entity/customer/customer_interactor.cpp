#include "customer_interactor.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"
#include "variants/const/customer_params.hpp"

void godot::CustomerInteractor::_bind_methods()
{
}

bool godot::CustomerInteractor::play_dialogue(String element_id, Entity *p_entity)
{
    ArcInteractor *dialogue = memnew(ArcInteractor);
    dialogue->set_entity(get_entity());
    dialogue->set_element_id(element_id);
    bool ret = dialogue->interact(p_entity);
    memdelete(dialogue);
    return ret;
}

bool godot::CustomerInteractor::open_hud(Entity *p_entity)
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(!hud){
        UtilityFunctions::print("CustomerInteractor: hud is null");
        return false;
    }

    String custommer_view_model_path = Util::get_value_from_config("ref_config", "custommer_view_model");
    Node *node = Util::spawn_node(custommer_view_model_path);

    if(!node){
        UtilityFunctions::print("CustomerInteractor: viewmodel is null");
        return false;
    }

    ViewModel *view_model = Object::cast_to<ViewModel>(node);
    if(!view_model){
        UtilityFunctions::print("CustomerInteractor: viewmodel is not ViewModel");
        return false;
    }

    CustomerViewModel *custommer_view_model = Object::cast_to<CustomerViewModel>(view_model);
    if(!custommer_view_model){
        UtilityFunctions::print("CustomerInteractor: viewmodel is not CustomerViewModel");
        return false;
    }
    
    
    hud->add_child(custommer_view_model);
    custommer_view_model->open_window(get_entity(), p_entity);

    return true;
}

bool godot::CustomerInteractor::_interact(Entity *p_entity)
{
    if(!get_entity()){
        UtilityFunctions::print("CustomerInteractor: entity is null");
        return false;
    }

    EntityData *data = get_entity()->get_data();

    if(!data){
        UtilityFunctions::print("CustomerInteractor: data is null");
        return false;
    }

    if(!data->has_string(CustomerParams::dialogue_id())){
        UtilityFunctions::print("CustomerInteractor: data not have " + CustomerParams::dialogue_id());
        return false;
    }

    return play_dialogue(data->get_string(CustomerParams::dialogue_id()), p_entity);
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
