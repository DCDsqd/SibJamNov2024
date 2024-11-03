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

    EntityData *data = get_entity()->get_data();
    if(ret){
        //UtilityFunctions::print("CustommerInteractor: next state");
        data->put_int(CustomerParams::state(), data->get_int(CustomerParams::state())+1);
    }
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

bool godot::CustomerInteractor::event_switcher(Entity *p_entity, EntityData *data)
{
    if(!data->has_int(CustomerParams::state())){
        UtilityFunctions::print("CustomerInteractor: data not contain: " + CustomerParams::state());
        return false;
    }

    int p_what = data->get_int(CustomerParams::state());
    switch (p_what){
        case 0: {
            if(!data->has_string(CustomerParams::dialogue_id())){
                UtilityFunctions::print("CustomerInteractor: data not have " + CustomerParams::dialogue_id());
                return false;
            }
            return play_dialogue(data->get_string(CustomerParams::dialogue_id()), p_entity);
        } break;

        case 1: {
            return open_hud(p_entity);
        } break;

        default: {
            UtilityFunctions::print("CustomerInteractor: out of range");
            return false;
        } break;
    }
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

    return event_switcher(p_entity, data);
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
