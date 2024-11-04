#include "custommer_builder.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::CustommerBuilder::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_data"), &CustommerBuilder::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &CustommerBuilder::get_data);

    ClassDB::bind_method(D_METHOD("set_name"), &CustommerBuilder::set_name);
    ClassDB::bind_method(D_METHOD("set_fact_level"), &CustommerBuilder::set_fact_level);
    ClassDB::bind_method(D_METHOD("set_display_level"), &CustommerBuilder::set_display_level);
    ClassDB::bind_method(D_METHOD("set_min_req_level"), &CustommerBuilder::set_min_req_level);
    ClassDB::bind_method(D_METHOD("set_dialogue_id"), &CustommerBuilder::set_dialogue_id);
    ClassDB::bind_method(D_METHOD("set_state"), &CustommerBuilder::set_state);
    ClassDB::bind_method(D_METHOD("set_sprite"), &CustommerBuilder::set_sprite);
}

void godot::CustommerBuilder::set_data(EntityData *p_data)
{
    this->data = p_data;
}

void godot::CustommerBuilder::set_name(String name)
{
    data->put_string(CustomerParams::name(), name);
}

void godot::CustommerBuilder::set_fact_level(int fact_level)
{
    data->put_int(CustomerParams::fact_lvl(), fact_level);
}

void godot::CustommerBuilder::set_display_level(int display_level)
{
    data->put_int(CustomerParams::display_lvl(), display_level);
}

void godot::CustommerBuilder::set_min_req_level(int min_req_level)
{
    data->put_int(CustomerParams::min_req_lvl(), min_req_level);
}

void godot::CustommerBuilder::set_dialogue_id(String dialogue_id)
{
    data->put_string(CustomerParams::dialogue_id(), dialogue_id);
}

void godot::CustommerBuilder::set_state(int state)
{
    data->put_int(CustomerParams::state(), 0);
}

void godot::CustommerBuilder::set_sprite(String sprite_img)
{
    data->put_string(CustomerParams::sprite_id(), sprite_img);
}

void godot::CustommerBuilder::set_tech_name(String tech_name)
{
    data->put_string(CustomerParams::tech_name(), tech_name);
}

godot::EntityData *godot::CustommerBuilder::get_data()
{
    if(!data){
        UtilityFunctions::print("CustommerBuilder: data is null");
    }

    return data;
}

godot::CustommerBuilder::CustommerBuilder()
{
}

godot::CustommerBuilder::~CustommerBuilder()
{
}
