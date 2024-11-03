#include "arc_hud_dialogue.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::ArcHudDialogue::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_text_field_path"), &ArcHudDialogue::set_text_field_path);
    ClassDB::bind_method(D_METHOD("get_text_field_path"), &ArcHudDialogue::get_text_field_path);

    ClassDB::bind_method(D_METHOD("set_speaker_name_field_path"), &ArcHudDialogue::set_speaker_name_field_path);
    ClassDB::bind_method(D_METHOD("get_speaker_name_field_path"), &ArcHudDialogue::get_speaker_name_field_path);

    ClassDB::bind_method(D_METHOD("set_answer_container_path"), &ArcHudDialogue::set_answer_container_path);
    ClassDB::bind_method(D_METHOD("get_answer_container_path"), &ArcHudDialogue::get_answer_container_path);
    

    ClassDB::add_property("ArcHudDialogue", PropertyInfo(Variant::NODE_PATH, "TextFieldPath"), "set_text_field_path", "get_text_field_path");
    ClassDB::add_property("ArcHudDialogue", PropertyInfo(Variant::NODE_PATH, "SpeakerNamePath"), "set_speaker_name_field_path", "get_speaker_name_field_path");
    ClassDB::add_property("ArcHudDialogue", PropertyInfo(Variant::NODE_PATH, "AnswerContainerPath"), "set_answer_container_path", "get_answer_container_path");
}

void godot::ArcHudDialogue::_play_dialogue(Dialogue *dialogue)
{
    
    if(text_field == nullptr || speaker_name_field == nullptr || answer_container == nullptr){
        UtilityFunctions::print("ArcHudDialogue: fields is incorrect");
        end_dialogue();
        return;
    }
    
    ArcDialogue *arc_dialogue = Object::cast_to<ArcDialogue>(dialogue);

    if(!arc_dialogue){
        UtilityFunctions::print("ArcHudDialogue: dialogue is not arc");
        end_dialogue();
        return;
    }
    
    arc_dialogue->update_text();
    get_hud()->lock_game();
    set_process_internal(true);

}

void godot::ArcHudDialogue::_end_dialogue()
{
    get_hud()->unlock_game();
    set_process_internal(false);
}

void godot::ArcHudDialogue::_int_process()
{

}

void godot::ArcHudDialogue::_init_links()
{
    if(text_field_path != NodePath() && get_node<RichTextLabel>(text_field_path)){
        this->text_field = get_node<RichTextLabel>(text_field_path);
    }else{
        UtilityFunctions::print("ArcHudDialogue: text_field_path incorrect");
    }

    if(speaker_name_field_path != NodePath() && get_node<Label>(speaker_name_field_path)){
        this->speaker_name_field = get_node<Label>(speaker_name_field_path);
    }else{
        UtilityFunctions::print("ArcHudDialogue: speaker_name_field_path incorrect");
    }

    if(answer_container_path != NodePath() && get_node<BoxContainer>(answer_container_path)){
        this->answer_container = get_node<BoxContainer>(answer_container_path);
    }else{
        UtilityFunctions::print("ArcHudDialogue: answer_container incorrect");
    }

}

void godot::ArcHudDialogue::set_text_field_path(NodePath p_text_field_path)
{
    this->text_field_path = p_text_field_path;
}

godot::NodePath godot::ArcHudDialogue::get_text_field_path()
{
    return this->text_field_path;
}

void godot::ArcHudDialogue::set_speaker_name_field_path(NodePath p_speaker_name_field_path)
{
    this->speaker_name_field_path = p_speaker_name_field_path;
}

godot::NodePath godot::ArcHudDialogue::get_speaker_name_field_path()
{
    return this->speaker_name_field_path;
}

void godot::ArcHudDialogue::set_answer_container_path(NodePath p_answer_container_path)
{
    this->answer_container_path = p_answer_container_path;
}

godot::NodePath godot::ArcHudDialogue::get_answer_container_path()
{
    return this->answer_container_path;
}

godot::ArcHudDialogue::ArcHudDialogue()
{

}

godot::ArcHudDialogue::~ArcHudDialogue()
{

}
