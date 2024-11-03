#include "order_hud.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"
#include "variants/const/order_params.hpp"

void godot::OrderHud::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("rate_current_order"), &OrderHud::rate_current_order);
    ClassDB::bind_method(D_METHOD("unrate_current_order"), &OrderHud::unrate_current_order);

    ClassDB::bind_method(D_METHOD("set_raw_img_path"), &OrderHud::set_raw_img_path);
    ClassDB::bind_method(D_METHOD("get_raw_img_path"), &OrderHud::get_raw_img_path);
    
    ClassDB::bind_method(D_METHOD("set_raw_name_path"), &OrderHud::set_raw_name_path);
    ClassDB::bind_method(D_METHOD("get_raw_name_path"), &OrderHud::get_raw_name_path);
    
    ClassDB::bind_method(D_METHOD("set_raw_descr_path"), &OrderHud::set_raw_descr_path);
    ClassDB::bind_method(D_METHOD("get_raw_descr_path"), &OrderHud::get_raw_descr_path);
    
    ClassDB::bind_method(D_METHOD("set_sorted_img_path"), &OrderHud::set_sorted_img_path);
    ClassDB::bind_method(D_METHOD("get_sorted_img_path"), &OrderHud::get_sorted_img_path);

    ClassDB::bind_method(D_METHOD("set_sorted_name_path"), &OrderHud::set_sorted_name_path);
    ClassDB::bind_method(D_METHOD("get_sorted_name_path"), &OrderHud::get_sorted_name_path);
    
    ClassDB::bind_method(D_METHOD("set_sorted_desr_path"), &OrderHud::set_sorted_desr_path);
    ClassDB::bind_method(D_METHOD("get_sorted_desr_path"), &OrderHud::get_sorted_desr_path);

    ClassDB::bind_method(D_METHOD("set_sorted_rank_path"), &OrderHud::set_sorted_rank_path);
    ClassDB::bind_method(D_METHOD("get_sorted_rank_path"), &OrderHud::get_sorted_rank_path);

    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "raw_img_path"), "set_raw_img_path", "get_raw_img_path");
    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "raw_name_path"), "set_raw_name_path", "get_raw_name_path");
    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "raw_descr_path"), "set_raw_descr_path", "get_raw_descr_path");

    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "sorted_img_path"), "set_sorted_img_path", "get_sorted_img_path");
    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "sorted_name_path"), "set_sorted_name_path", "get_sorted_name_path");
    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "sorted_desr_path"), "set_sorted_desr_path", "get_sorted_desr_path");
    ClassDB::add_property("OrderHud", PropertyInfo(Variant::NODE_PATH, "sorted_rank_path"), "set_sorted_rank_path", "get_sorted_rank_path");
}

godot::OrderContainer *godot::OrderHud::get_container_data(Entity *entity)
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

void godot::OrderHud::update_window()
{
    draw_raw();
    draw_sorted();
}

void godot::OrderHud::draw_raw()
{
    if(order_container->get_orger_count() == 0){
        reset_raw();
        return;
    }

    Entity *order = order_container->get_order(raw_carrera);
    if(!order){
        UtilityFunctions::print("OrderHud: raw_order is null");
        reset_raw();
        return;
    }

    EntityData *data = order->get_data();
    if(!data){
        UtilityFunctions::print("OrderHud: raw_data is null");
        reset_raw();
        return;
    }
    

    if(has_node(raw_name_path) && get_node<Label>(raw_name_path)){
        Label *raw_name = get_node<Label>(raw_name_path);
        raw_name->set_text(data->get_string(OrderParams::name()));
    }else{
        UtilityFunctions::print("OrderHud: raw_name is null");
        close_window();
        return;
    }

    if(has_node(raw_descr_path) && get_node<RichTextLabel>(raw_descr_path)){
        RichTextLabel *raw_descr = get_node<RichTextLabel>(raw_descr_path);
        raw_descr->set_text(data->get_string(OrderParams::descr()));
    }else{
        UtilityFunctions::print("OrderHud: raw_descr is null");
        close_window();
        return;
    }

    // if(has_node(raw_descr_path) && get_node<TextureRect>(raw_img_path)){
    //     TextureRect *raw_texture = get_node<TextureRect>(raw_name_path);
    //     Ref<Texture2D> texture = Util::load_image(data->get_string(OrderParams::img()));
    //     if(texture != Ref<Texture2D>()){
    //         raw_texture->set_texture(texture);
    //     }
    // }else{
    //     UtilityFunctions::print("OrderHud: name is null");
    //     close_window();
    //     return;
    // }
}

void godot::OrderHud::draw_sorted()
{
    if(hero_container->get_orger_count() == 0){
        reset_sorted();
        return;
    }

    Entity *order = hero_container->get_order(sorted_carrera);
    
    if(!order){
        UtilityFunctions::print("OrderHud: sorted_order is null");
        reset_sorted();
        return;
    }
    

    EntityData *data = order->get_data();
    if(!data){
        UtilityFunctions::print("OrderHud: sorted_data is null");
        reset_sorted();
        return;
    }

    
    if(has_node(sorted_name_path) && get_node<Label>(sorted_name_path)){
        Label *name = get_node<Label>(sorted_name_path);
        name->set_text(data->get_string(OrderParams::name()));
    }else{
        UtilityFunctions::print("OrderHud: sorted_name is null");
        close_window();
        return;
    }

    if(has_node(sorted_desr_path) && get_node<RichTextLabel>(sorted_desr_path)){
        RichTextLabel *sorted_descr = get_node<RichTextLabel>(sorted_desr_path);
        sorted_descr->set_text(data->get_string(OrderParams::descr()));
    }else{
        UtilityFunctions::print("OrderHud: sorted_descr is null");
        close_window();
        return;
    }

    if(has_node(sorted_rank_path) && get_node<Label>(sorted_rank_path)){
        Label *sorted_rank = get_node<Label>(sorted_rank_path);
        sorted_rank->set_text(data->get_string(OrderParams::placed_rank()));
    }else{
        UtilityFunctions::print("OrderHud: sorted_rank is null");
        close_window();
        return;
    }
}

void godot::OrderHud::reset_raw()
{
    if(has_node(raw_name_path) && get_node<Label>(raw_name_path)){
        Label *raw_name = get_node<Label>(raw_name_path);
        raw_name->set_text("Empty");
    }else{
        UtilityFunctions::print("OrderHud: name is null");
        close_window();
        return;
    }

    if(has_node(raw_descr_path) && get_node<RichTextLabel>(raw_descr_path)){
        RichTextLabel *raw_descr = get_node<RichTextLabel>(raw_descr_path);
        raw_descr->set_text("not quest selected");
    }else{
        UtilityFunctions::print("OrderHud: name is null");
        close_window();
        return;
    }
}

void godot::OrderHud::reset_sorted()
{
    
    if(has_node(sorted_name_path) && get_node<Label>(sorted_name_path)){
        Label *name = get_node<Label>(sorted_name_path);
        name->set_text("Empty");
    }else{
        UtilityFunctions::print("OrderHud: sorted_name is null");
        close_window();
        return;
    }

    if(has_node(sorted_desr_path) && get_node<RichTextLabel>(sorted_desr_path)){
        RichTextLabel *sorted_descr = get_node<RichTextLabel>(sorted_desr_path);
        sorted_descr->set_text("not quest selected");
    }else{
        UtilityFunctions::print("OrderHud: sorted_descr is null");
        close_window();
        return;
    }

    if(has_node(sorted_rank_path) && get_node<Label>(sorted_rank_path)){
        Label *sorted_rank = get_node<Label>(sorted_rank_path);
        sorted_rank->set_text("");
    }else{
        UtilityFunctions::print("OrderHud: sorted_rank is null");
        close_window();
        return;
    }
}

void godot::OrderHud::set_raw_img_path(NodePath p_raw_img_path)
{
    this->raw_img_path = p_raw_img_path;
}

godot::NodePath godot::OrderHud::get_raw_img_path()
{
    return this->raw_img_path;
}

void godot::OrderHud::set_raw_name_path(NodePath p_raw_name_path)
{
    this->raw_name_path = p_raw_name_path;
}

godot::NodePath godot::OrderHud::get_raw_name_path()
{
    return this->raw_name_path;
}

void godot::OrderHud::set_raw_descr_path(NodePath p_raw_descr_path)
{
    this->raw_descr_path = p_raw_descr_path;
}

godot::NodePath godot::OrderHud::get_raw_descr_path()
{
    return this->raw_descr_path;
}

void godot::OrderHud::set_sorted_img_path(NodePath p_sorted_img_path)
{
    this->sorted_img_path = p_sorted_img_path;
}

godot::NodePath godot::OrderHud::get_sorted_img_path()
{
    return this->sorted_img_path;
}

void godot::OrderHud::set_sorted_name_path(NodePath p_sorted_name_path)
{
    this->sorted_name_path = p_sorted_name_path;
}

godot::NodePath godot::OrderHud::get_sorted_name_path()
{
    return this->sorted_name_path;
}

void godot::OrderHud::set_sorted_desr_path(NodePath p_sorted_desr_path)
{
    this->sorted_desr_path = p_sorted_desr_path;
}

godot::NodePath godot::OrderHud::get_sorted_desr_path()
{
    return this->sorted_desr_path;
}

void godot::OrderHud::set_sorted_rank_path(NodePath p_sorted_rank_path)
{
    this->sorted_rank_path = p_sorted_rank_path;
}

godot::NodePath godot::OrderHud::get_sorted_rank_path()
{
    return this->sorted_rank_path;
}

void godot::OrderHud::rate_current_order(int rank)
{
    Entity *order = order_container->get_order(raw_carrera);
    if(!order){
        UtilityFunctions::print("OrderHud: order is null");
        return;
    }

    EntityData *data = order->get_data();
    if(!data){
        UtilityFunctions::print("OrderHud: data is null");
        return;
    }

    data->put_int(OrderParams::placed_rank(), rank);
    hero_container->add_order(order);
    order_container->remove_order(raw_carrera);
    update_window();
    //UtilityFunctions::print(order_container->get_orger_count());

}

void godot::OrderHud::unrate_current_order()
{
    Entity *order = hero_container->get_order(sorted_carrera);
    if(!order){
        UtilityFunctions::print("OrderHud: order is null");
        return;
    }

    EntityData *data = order->get_data();
    if(!data){
        UtilityFunctions::print("OrderHud: data is null");
        return;
    }

    data->put_int(OrderParams::placed_rank(), -1);
    order_container->add_order(order);
    hero_container->remove_order(sorted_carrera);
    update_window();

}

void godot::OrderHud::_open_window(Entity *interaction, Entity *interactor)
{
    UtilityFunctions::print("OrderHud: lauch hud");

    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("OrderHud: hud is null");
        close_window();
        return;
    }

    order_container = get_container_data(interaction);
    hero_container = get_container_data(interactor);

    if(!order_container){
        UtilityFunctions::print("OrderHud: order_contaier is null");
        close_window();
        return;
    }
    if(!hero_container){
        UtilityFunctions::print("OrderHud: hero_container is null");
        close_window();
        return;
    }

    hud->lock_game();
    set_physics_process_internal(true);
    update_window();
}

void godot::OrderHud::_close_window()
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("SimpleViewModel: hud is null");
        return;
    }

    hud->unlock_game();
}

void godot::OrderHud::_int_process()
{
    if(Input::get_singleton()->is_action_just_released("e_cancel")){
        close_window();
    }
}

godot::OrderHud::OrderHud()
{
}

godot::OrderHud::~OrderHud()
{
}
