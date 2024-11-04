#include "result_view_model.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::ResultViewModel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("press"), &ResultViewModel::press);

    ClassDB::bind_method(D_METHOD("set_descr_path"), &ResultViewModel::set_descr_path);
    ClassDB::bind_method(D_METHOD("get_descr_path"), &ResultViewModel::get_descr_path);

    ClassDB::bind_method(D_METHOD("set_result_path"), &ResultViewModel::set_result_path);
    ClassDB::bind_method(D_METHOD("get_result_path"), &ResultViewModel::get_result_path);

    ClassDB::bind_method(D_METHOD("set_button_path"), &ResultViewModel::set_button_path);
    ClassDB::bind_method(D_METHOD("get_button_path"), &ResultViewModel::get_button_path);

    ClassDB::add_property("ResultViewModel", PropertyInfo(Variant::NODE_PATH, "descr_path"), "set_descr_path", "get_descr_path");
    ClassDB::add_property("ResultViewModel", PropertyInfo(Variant::NODE_PATH, "result_path"), "set_result_path", "get_result_path");
    ClassDB::add_property("ResultViewModel", PropertyInfo(Variant::NODE_PATH, "button_path"), "set_button_path", "get_button_path");
}

void godot::ResultViewModel::update_window()
{
    if(has_node(descr_path) && get_node<RichTextLabel>(descr_path)){
        RichTextLabel *descr = get_node<RichTextLabel>(descr_path);
        descr->set_text(str_descr);
    }else{
        UtilityFunctions::print("ResultViewModel: descr_path is incorrect");
        close_window();
        return;
    }

    if(has_node(result_path) && get_node<Label>(result_path)){
        Label *result = get_node<Label>(result_path);
        String text_key = "result_win";
        if(time_end){
            text_key = "result_time_end";
        }
        if(death){
            text_key = "result_death";
        }
        result->set_text(text_key);
    }else{
        UtilityFunctions::print("ResultViewModel: result_path is incorrect");
        close_window();
        return;
    }

    if(has_node(button_path) && get_node<Button>(button_path)){
        Button* button = get_node<Button>(button_path);
        String text_key = "button_continue";
        if(is_end){
            text_key = "button_end";
        }
        button->set_text(text_key);
    }


}

void godot::ResultViewModel::set_result(bool p_death, bool p_time_end, String descr)
{
    this->death = p_death;
    this->time_end = p_time_end;
    this->str_descr = descr;
    this->is_end = p_death || p_time_end;
}

void godot::ResultViewModel::press()
{
    if(is_end){
        get_tree()->quit();
        close_window();
        return;
    }
    close_window();
}

void godot::ResultViewModel::set_descr_path(NodePath p_descr_path)
{
    this->descr_path = p_descr_path;
}

godot::NodePath godot::ResultViewModel::get_descr_path()
{
    return this->descr_path;
}

void godot::ResultViewModel::set_result_path(NodePath p_result_path)
{
    this->result_path = p_result_path;
}

godot::NodePath godot::ResultViewModel::get_result_path()
{
    return this->result_path;
}

void godot::ResultViewModel::set_button_path(NodePath p_button_path)
{
    this->button_path = p_button_path;
}

godot::NodePath godot::ResultViewModel::get_button_path()
{
    return this->button_path;
}

void godot::ResultViewModel::_open_window(Entity *interaction, Entity *interactor)
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("ArcViewModel: hud is null");
        close_window();
        return;
    }

    hud->lock_game();
    update_window();
}

void godot::ResultViewModel::_close_window()
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("SimpleViewModel: hud is null");
        return;
    }

    hud->unlock_game();
}

void godot::ResultViewModel::_int_process()
{
}

godot::ResultViewModel::ResultViewModel()
{
}

godot::ResultViewModel::~ResultViewModel()
{
}
