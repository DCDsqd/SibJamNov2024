#include "custommer_view_model.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"
#include "variants/const/order_params.hpp"
#include "variants/const/customer_params.hpp"

void godot::CustomerViewModel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("request_quest"), &CustomerViewModel::request_quest);

    ClassDB::bind_method(D_METHOD("set_custommer_name_path"), &CustomerViewModel::set_custommer_name_path);
    ClassDB::bind_method(D_METHOD("get_custommer_name_path"), &CustomerViewModel::get_custommer_name_path);

    ClassDB::bind_method(D_METHOD("set_custommer_lvl_path"), &CustomerViewModel::set_custommer_lvl_path);
    ClassDB::bind_method(D_METHOD("get_custommer_lvl_path"), &CustomerViewModel::get_custommer_lvl_path);
    
    ClassDB::bind_method(D_METHOD("set_order_name_path"), &CustomerViewModel::set_order_name_path);
    ClassDB::bind_method(D_METHOD("get_order_name_path"), &CustomerViewModel::get_order_name_path);

    ClassDB::bind_method(D_METHOD("set_order_lvl_path"), &CustomerViewModel::set_order_lvl_path);
    ClassDB::bind_method(D_METHOD("get_order_lvl_path"), &CustomerViewModel::get_order_lvl_path);
    
    ClassDB::bind_method(D_METHOD("set_output_path"), &CustomerViewModel::set_output_path);
    ClassDB::bind_method(D_METHOD("get_output_path"), &CustomerViewModel::get_output_path);

    ClassDB::add_property("CustomerViewModel", PropertyInfo(Variant::NODE_PATH, "custommer_name_path"), "set_custommer_name_path", "get_custommer_name_path");
    ClassDB::add_property("CustomerViewModel", PropertyInfo(Variant::NODE_PATH, "custommer_lvl_path"), "set_custommer_lvl_path", "get_custommer_lvl_path");
    ClassDB::add_property("CustomerViewModel", PropertyInfo(Variant::NODE_PATH, "order_name_path"), "set_order_name_path", "get_order_name_path");
    ClassDB::add_property("CustomerViewModel", PropertyInfo(Variant::NODE_PATH, "order_lvl_path"), "set_order_lvl_path", "get_order_lvl_path");
    ClassDB::add_property("CustomerViewModel", PropertyInfo(Variant::NODE_PATH, "output_path"), "set_output_path", "get_output_path");
}

godot::OrderContainer *godot::CustomerViewModel::get_container_data(Entity *entity)
{
    if(!entity){
        UtilityFunctions::print("OrderHud: entity is null");
        return nullptr;
    }

    EntityData *data = entity->get_data();
    if(!data){
        UtilityFunctions::print("OrderHud: data in entity is null");
        return nullptr;
    }

    ContainerEntityData *container_data = Object::cast_to<ContainerEntityData>(data);

    if(!container_data){
        UtilityFunctions::print("OrderHud: data in entity is not ContainerEntityData");
        return nullptr;
    }

    OrderContainer *container = container_data->get_order_container();
    if(!container){
        UtilityFunctions::print("OrderContainer: container in data is null");
        return nullptr;
    }
    return container;

}

bool godot::CustomerViewModel::check_request()
{
    
    return false;
}

void godot::CustomerViewModel::update_window()
{
    
    update_order();
    update_customer();
}

void godot::CustomerViewModel::update_customer()
{
    if(!custommer_data){
        UtilityFunctions::print("OrderHud: custommer data is null");
        close_window();
        return;
    }
    
    if(has_node(custommer_name_path) && get_node<Label>(custommer_name_path)){
        Label *custommer_name = get_node<Label>(custommer_name_path);
        custommer_name->set_text(custommer_data->get_string(CustomerParams::name()));
    }else{
        UtilityFunctions::print("CustomerViewModel: custommer_name incorrect");
        close_window();
        return;
    }

    if(has_node(custommer_lvl_path) && get_node<Label>(custommer_lvl_path)){
        Label *custommer_lvl = get_node<Label>(custommer_lvl_path);
        custommer_lvl->set_text(Util::int_to_godot_str(custommer_data->get_int(CustomerParams::display_lvl())));
    }else{
        UtilityFunctions::print("CustomerViewModel: custommer_lvl incorrect");
        close_window();
        return;
    }

}

void godot::CustomerViewModel::update_order()
{
    if(order_container->get_orger_count() == 0){
        reset_quest();
        return;
    }

    Entity *order = order_container->get_order(carrera);
    if(!order){
        UtilityFunctions::print("OrderHud: raw_order is null");
        reset_quest();
        return;
    }

    EntityData *data = order->get_data();
    if(!data){
        UtilityFunctions::print("OrderHud: raw_data is null");
        reset_quest();
        return;
    }

    if(has_node(order_name_path) && get_node<Label>(order_name_path)){
        Label *order_name = get_node<Label>(order_name_path);
        order_name->set_text(data->get_string(OrderParams::name()));
    }else{
        UtilityFunctions::print("CustomerViewModel: order_name_path incorrect");
        close_window();
        return;
    }

    if(has_node(order_lvl_path) && get_node<Label>(order_lvl_path)){
        Label *order_lvl = get_node<Label>(order_lvl_path);
        order_lvl->set_text(Util::int_to_godot_str(data->get_int(OrderParams::placed_rank())));
    }else{
        UtilityFunctions::print("CustomerViewModel: order_lvl_path incorrect");
        close_window();
        return;
    }
}

void godot::CustomerViewModel::reset_quest()
{
    if(has_node(order_name_path) && get_node<Label>(order_name_path)){
        Label *order_name = get_node<Label>(order_name_path);
        order_name->set_text("No Quest");
    }else{
        UtilityFunctions::print("CustomerViewModel: order_name_path incorrect");
        close_window();
        return;
    }

    if(has_node(order_lvl_path) && get_node<Label>(order_lvl_path)){
        Label *order_lvl = get_node<Label>(order_lvl_path);
        order_lvl->set_text("");
    }else{
        UtilityFunctions::print("CustomerViewModel: order_lvl_path incorrect");
        close_window();
        return;
    }
}

void godot::CustomerViewModel::set_custommer_name_path(NodePath p_custommer_name_path)
{
    this->custommer_name_path = p_custommer_name_path;
}

godot::NodePath godot::CustomerViewModel::get_custommer_name_path()
{
    return this->custommer_name_path;
}

void godot::CustomerViewModel::set_custommer_lvl_path(NodePath p_custommer_lvl_path)
{
    this->custommer_lvl_path = p_custommer_lvl_path;
}

godot::NodePath godot::CustomerViewModel::get_custommer_lvl_path()
{
    return this->custommer_lvl_path;
}

void godot::CustomerViewModel::set_order_name_path(NodePath p_order_name_path)
{
    this->order_name_path = p_order_name_path;
}

godot::NodePath godot::CustomerViewModel::get_order_name_path()
{
    return this->order_name_path;
}

void godot::CustomerViewModel::set_order_lvl_path(NodePath p_order_lvl_path)
{
    this->order_lvl_path = p_order_lvl_path;
}

godot::NodePath godot::CustomerViewModel::get_order_lvl_path()
{
    return this->order_lvl_path;
}

void godot::CustomerViewModel::set_output_path(NodePath p_output_path)
{
    this->output_path = p_output_path;
}

godot::NodePath godot::CustomerViewModel::get_output_path()
{
    return this->output_path;
}

void godot::CustomerViewModel::request_quest()
{
    if(this->order_container->get_orger_count() == 0){
        UtilityFunctions::print("CustomerViewModel: no orders");
        return;
    }

    Entity *order = order_container->get_order(carrera);
    if(!order){
        UtilityFunctions::print("CustomerViewModel: null orders");
        return;
    }

    EntityData *data = order->get_data();
    if(!data){
        UtilityFunctions::print("CustomerViewModel: null data");
        return;
    }

    if(custommer_data->get_int(CustomerParams::min_req_lvl()) <= data->get_int(OrderParams::placed_rank())){
        custommer_data->put_int(CustomerParams::request_quest(), data->get_int(OrderParams::fact_rank()));
        order_container->remove_order(carrera);
        close_window();
    }

}

void godot::CustomerViewModel::_open_window(Entity *interaction, Entity *interactor)
{
    UtilityFunctions::print("CustomerViewModel: lauch hud");

    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("CustomerViewModel: hud is null");
        close_window();
        return;
    }

    order_container = get_container_data(interactor);

    if(!order_container){
        UtilityFunctions::print("CustomerViewModel: order_contaier is null");
        close_window();
        return;
    }

    custommer_data = interaction->get_data();

    if(!custommer_data){
        UtilityFunctions::print("CustomerViewModel: customer_data is null");
        close_window();
        return;
    }

    hud->lock_game();
    set_physics_process_internal(true);
    update_window();
    
}

void godot::CustomerViewModel::_close_window()
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("CustomerViewModel: hud is null");
        return;
    }

    hud->unlock_game();
}

void godot::CustomerViewModel::_int_process()
{
    if(Input::get_singleton()->is_action_just_released("e_cancel")){
        close_window();
    }
}

godot::CustomerViewModel::CustomerViewModel()
{
}

godot::CustomerViewModel::~CustomerViewModel()
{
}
