#include "trigger_sound.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::TriggerSound::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_sound"), &TriggerSound::set_sound);
    ClassDB::bind_method(D_METHOD("get_sound"), &TriggerSound::get_sound);
    
    ClassDB::bind_method(D_METHOD("set_speaker"), &TriggerSound::set_speaker);
    ClassDB::bind_method(D_METHOD("get_speaker"), &TriggerSound::get_speaker);

    ClassDB::add_property("TriggerSound", PropertyInfo(Variant::STRING, "sound"), "set_sound", "get_sound");
    ClassDB::add_property("TriggerSound", PropertyInfo(Variant::NODE_PATH, "speaker"), "set_speaker", "get_speaker");
}

void godot::TriggerSound::set_sound(String p_sound)
{
    this->sound = p_sound;
}

godot::String godot::TriggerSound::get_sound()
{
    return this->sound;
}

void godot::TriggerSound::set_speaker(NodePath p_speaker_path)
{
    this->speaker_path = p_speaker_path;
}

godot::NodePath godot::TriggerSound::get_speaker()
{
    return this->speaker_path;
}

bool godot::TriggerSound::_activate()
{
    if(sound == String())
        return false;
    
    Ref<AudioStream> stream = Util::load_music(sound);

    if(stream == Ref<AudioStream>()){
        UtilityFunctions::print("TriggerSound: stream is null");
        return false;
    }

    if(!(has_node(speaker_path) && get_node<AudioStreamPlayer3D>(speaker_path))){
        UtilityFunctions::print("TriggerSound: speaker_path is incorrect");
        return false;
    }

    AudioStreamPlayer3D *speaker = get_node<AudioStreamPlayer3D>(speaker_path);
    speaker->set_stream(stream);
    speaker->play();

    return true;
}

godot::TriggerSound::TriggerSound()
{
}

godot::TriggerSound::~TriggerSound()
{
}
