#include "arc_view_model.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"

void godot::ArcViewModel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("check_answer"), &ArcViewModel::check_answer);

    ClassDB::bind_method(D_METHOD("set_answer_container_path"), &ArcViewModel::set_answer_container_path);
    ClassDB::bind_method(D_METHOD("get_answer_container_path"), &ArcViewModel::get_answer_container_path);

    ClassDB::bind_method(D_METHOD("set_speaker_name_field_path"), &ArcViewModel::set_speaker_name_field_path);
    ClassDB::bind_method(D_METHOD("get_speaker_name_field_path"), &ArcViewModel::get_speaker_name_field_path);

    ClassDB::bind_method(D_METHOD("set_text_field_path"), &ArcViewModel::set_text_field_path);
    ClassDB::bind_method(D_METHOD("get_text_field_path"), &ArcViewModel::get_text_field_path);
    
    ClassDB::bind_method(D_METHOD("set_answer_field_path"), &ArcViewModel::set_answer_field_path);
    ClassDB::bind_method(D_METHOD("get_answer_field_path"), &ArcViewModel::get_answer_field_path);

    ClassDB::bind_method(D_METHOD("set_speaker_path"), &ArcViewModel::set_speaker_path);
    ClassDB::bind_method(D_METHOD("get_speaker_path"), &ArcViewModel::get_speaker_path);

    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "answer_container_path"), "set_answer_container_path", "get_answer_container_path");
    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "speaker_name_field_path"), "set_speaker_name_field_path", "get_speaker_name_field_path");
    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "text_field_path"), "set_text_field_path", "get_text_field_path");
    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "answer_field_path"), "set_answer_field_path", "get_answer_field_path");
    ClassDB::add_property("ArcViewModel", PropertyInfo(Variant::NODE_PATH, "speaker_path"), "set_speaker_path", "get_speaker_path");
}

void godot::ArcViewModel::update_window()
{
    if(dialogue == nullptr){
        UtilityFunctions::print("ArcViewModel: dialogue is null");
        close_window();
        return;
    }

    if(dialogue->get_text() == String()){
        UtilityFunctions::print("ArcViewModel: text is null");
        close_window();
        return;
    }

    if(editor){
        editor->clear();
    }

    String sound = dialogue->get_audio();
    if(sound != String()){
        play_sound(sound);
    }

    if(text_field_path != NodePath() && get_node<RichTextLabel>(text_field_path)){
        RichTextLabel *text_field = get_node<RichTextLabel>(text_field_path);
        text_field->clear();
        text_field->append_text(fix_markup(dialogue->get_text()));
    }else{
        close_window();
        return;
    }

    if(speaker_name_field_path != NodePath() && get_node<Label>(speaker_name_field_path)){
        Label *speaker_name = get_node<Label>(speaker_name_field_path);
        String name_id = dialogue->get_speaker(0);
        VoidComponent *component = God::get_singleton()->get_component(name_id);
        if(component){
            speaker_name->set_text(component->get_name());
        }
        
    }else{
        close_window();
        return;
    }

    std::vector<String> answers;
    for(int i = 0; i < dialogue->get_answer_count(); ++i){
        answers.push_back(dialogue->get_answer_text(i));
    }
    
    update_answer(answers);
    
}

void godot::ArcViewModel::update_answer(const std::vector<String> &answers)
{
    if(answer_container_path != NodePath() && get_node<RichTextLabel>(answer_container_path)){
        RichTextLabel *answer_contaier = get_node<RichTextLabel>(answer_container_path);
        answer_contaier->clear();
        for(int i = 0; i < answers.size(); ++i){
            String answer = answers[i];
            answer_contaier->append_text("- " + answer + "\n");
        }
    }
}

void godot::ArcViewModel::play_sound(String asset_id)
{
    VoidAsset *asset = God::get_singleton()->get_asset(asset_id);
    if(!asset){
        UtilityFunctions::print("ArcViewModel: asset " + asset_id + " is null");
        return;
    }

    ArcAsset *arc_asset = Object::cast_to<ArcAsset>(asset);
    if(!arc_asset){
        UtilityFunctions::print("ArcViewModel: asset " + asset_id + " is not arcAsset");
        return;
    }
    String name = arc_asset->get_name();
    UtilityFunctions::print("ArcViewModel: sound name: " + name);

    if(has_node(speaker_path) && get_node<AudioStreamPlayer>(speaker_path)){
        AudioStreamPlayer* speaker = get_node<AudioStreamPlayer>(speaker_path);
        Ref<AudioStream> sound = Util::load_music(Util::get_value_from_config("story", "assets") + name);
        if(sound == Ref<AudioStream>()){
            UtilityFunctions::print("ArcViewModel: unable to play sound");
            return;
        }
        speaker->set_stream(sound);
        speaker->play();
        return;
    }
    UtilityFunctions::print("ArcViewModel: speaker is incorrect");
}

godot::String godot::ArcViewModel::fix_markup(String input)
{
    input = input.replace("<code", "[lang");
    input = input.replace("</code", "[/lang");
    input = input.replace("<", "[");
    input = input.replace(">", "]");
    
    return input;
}

godot::String godot::ArcViewModel::erase_markup(String input)
{
    RegEx *regex = new RegEx();
    regex->compile("\\<.*?\\>");
    return regex->sub(input, "", true);
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

void godot::ArcViewModel::set_answer_field_path(NodePath p_answer_field_path)
{
    this->answer_field_path = p_answer_field_path;
}

godot::NodePath godot::ArcViewModel::get_answer_field_path()
{
    return this->answer_field_path;
}

void godot::ArcViewModel::set_speaker_path(NodePath p_speaker_path)
{
    this->speaker_path = p_speaker_path;
}

godot::NodePath godot::ArcViewModel::get_speaker_path()
{
    return this->speaker_path;
}

void godot::ArcViewModel::set_dialogue(ArcDialogue *p_dialogue)
{
    this->dialogue = p_dialogue;
}

void godot::ArcViewModel::_open_window(Entity *interaction, Entity *interactor)
{
    UtilityFunctions::print("ArcViewModel: start dialogue");

    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("ArcViewModel: hud is null");
        close_window();
        return;
    }

    if(has_node(answer_field_path) && get_node<TextEdit>(answer_field_path)){
        editor = get_node<TextEdit>(answer_field_path);
        editor->connect("text_changed", Callable(this, "check_answer"));
    }else{
        UtilityFunctions::print("ArcViewModel: editor is null or incorrect");
        close_window();
        return;
    }


    hud->lock_game();
    //set_physics_process_internal(true);
    update_window();
}

void godot::ArcViewModel::_close_window()
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("SimpleViewModel: hud is null");
        return;
    }

    hud->unlock_game();
}

void godot::ArcViewModel::_int_process()
{
}

void godot::ArcViewModel::check_answer()
{
    if(dialogue->is_end()){
        close_window();
        return;
    }

    String text = editor->get_text();
    if(dialogue->answer(text)){
        update_window();
    }
}


godot::ArcViewModel::ArcViewModel()
{
}

godot::ArcViewModel::~ArcViewModel()
{
}
