#include "arc_view_model.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::ArcViewModel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_answer_container_path"), &ArcViewModel::set_answer_container_path);
    ClassDB::bind_method(D_METHOD("get_answer_container_path"), &ArcViewModel::get_answer_container_path);

    ClassDB::bind_method(D_METHOD("set_speaker_name_field_path"), &ArcViewModel::set_speaker_name_field_path);
    ClassDB::bind_method(D_METHOD("get_speaker_name_field_path"), &ArcViewModel::get_speaker_name_field_path);

    ClassDB::bind_method(D_METHOD("set_text_field_path"), &ArcViewModel::set_text_field_path);
    ClassDB::bind_method(D_METHOD("get_text_field_path"), &ArcViewModel::get_text_field_path);

    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "answer_container_path"), "set_answer_container_path", "get_answer_container_path");
    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "speaker_name_field_path"), "set_speaker_name_field_path", "get_speaker_name_field_path");
    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "text_field_path"), "set_text_field_path", "get_text_field_path");
   
}

void godot::ArcViewModel::update_winow()
{
    if(dialogue == nullptr){
        close_window();
        return;
    }

    if(text_field_path != NodePath() && get_node<RichTextLabel>(text_field_path)){
        RichTextLabel *text_field = get_node<RichTextLabel>(text_field_path);
        text_field->set_text(dialogue->get_text());
    }

    

    std::vector<String> answers;
    for(int i = 0; i < dialogue->get_answer_count(); ++i){
        answers.push_back(dialogue->get_answer_text(i));
    }
    
   //update_answer(answers);
    
}

void godot::ArcViewModel::update_answer(const std::vector<String> &answers)
{
    if(answer_container_path != NodePath() && get_node<RichTextLabel>(answer_container_path)){
        RichTextLabel *answer_contaier = get_node<RichTextLabel>(answer_container_path);
        answer_contaier->set_text("");
        for(int i = 0; i < answers.size(); ++i){
            String answer = answers[i];
            answer_contaier->add_text("- " + answer + "\n");
        }
    }
}

void godot::ArcViewModel::set_answer_container_path(NodePath p_answer_container_path)
{
    this->answer_container_path = p_answer_container_path;
}

godot::NodePath godot::ArcViewModel::get_answer_container_path()
{
    return this->answer_container_path;
}

void godot::ArcViewModel::set_speaker_name_field_path(NodePath p_speaker_name_field_path)
{
    this->speaker_name_field_path = p_speaker_name_field_path;
}

godot::NodePath godot::ArcViewModel::get_speaker_name_field_path()
{
    return this->speaker_name_field_path;
}

void godot::ArcViewModel::set_text_field_path(NodePath p_text_field_path)
{
    this->text_field_path = p_text_field_path;
}

godot::NodePath godot::ArcViewModel::get_text_field_path()
{
    return this->text_field_path;
}

void godot::ArcViewModel::_open_window(Entity *interaction, Entity *interactor)
{
    UtilityFunctions::print("ArcViewModel: start dialogue");

    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("SimpleViewModel: hud is null");
        return;
    }

    hud->lock_game();
    set_physics_process_internal(true);
    update_winow();
}

void godot::ArcViewModel::_close_window()
{
}

void godot::ArcViewModel::_int_process()
{
}

godot::ArcViewModel::ArcViewModel()
{
}

godot::ArcViewModel::~ArcViewModel()
{
}
