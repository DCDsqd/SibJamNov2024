#include "arc_dialogue.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"

void godot::ArcDialogue::_bind_methods()
{
    
}

bool godot::ArcDialogue::check_condition(String condition)
{
    return true;
}

godot::String godot::ArcDialogue::check_condition_bit(ArcConditionBit *bit)
{
    String if_condition = bit->get_if_condition();
    if(if_condition == String())
        return String();

    if(check_condition(if_condition)){
        return bit->get_output_id(bit->get_if_output());
    }
    
    int elif_size = bit->get_elif_condition_size();
    for(int i = 0; i < elif_size; ++i){
        String elif_condition = bit->get_elif_condition(i);
        if(elif_condition == String()){
            continue;
        }

        if(check_condition(elif_condition)){
            return bit->get_output_id(bit->get_elif_output(i));
        }
    }

    String else_condition = bit->get_else_condition();
    if(else_condition == String()){
        return String();
    }

    if(check_condition(else_condition)){
        return bit->get_output_id(bit->get_else_output());
    }

    return String();
}

std::pair<godot::String, bool> godot::ArcDialogue::parse_answer(String id, String label, bool avaible, int num)
{
    //UtilityFunctions::print("ArcDialogue: parse answer num: " + Util::int_to_godot_str(num) + " labele is: " + label);
    VoidConnect *connect = God::get_singleton()->get_connect(id);
    if(!connect){
        UtilityFunctions::print("ArcDialogue: connect is not found: " + id);
        return std::pair<String, bool>();
    }

    ArcConnect *arc_connect = Object::cast_to<ArcConnect>(connect);
    if(!arc_connect){
        UtilityFunctions::print("ArcDialogue: connect is not arc: " + id);
        return std::pair<String, bool>();
    }

    if(arc_connect->get_label() != String() && arc_connect->get_label() != "<null>"){
        label = arc_connect->get_label();
        //UtilityFunctions::print("ArcDialogue: rename label num: " + Util::int_to_godot_str(num) + " labele is: " + label);
    }

    String id_to = arc_connect->get_to();

    VoidBit *bit = God::get_singleton()->get_bit(id_to);
    if(!bit){
        UtilityFunctions::print("ArcDialogue: not found to_id: " + id_to + " from connect: " + id);
        return std::pair<String, bool>();
    }

    ArcElementBit *arc_element_bit = Object::cast_to<ArcElementBit>(bit);
    if(arc_element_bit){
        return std::pair<String, bool>(label, avaible);
    }

    ArcJumper *arc_jumper = Object::cast_to<ArcJumper>(bit);
    if(arc_jumper){
        return std::pair<String, bool>(label, avaible);
    }

    ArcConditionBit *arc_condition = Object::cast_to<ArcConditionBit>(bit);
    if(arc_condition){
        String next_id = check_condition_bit(arc_condition);
        if(next_id == String()){
            if(label == String()){
                UtilityFunctions::print("ArcDialogue: unable");
                return std::pair<String, bool>();
            }
            
            return std::pair<String, bool>(label, false);
        }
        return parse_answer(next_id, label, avaible, num);

    }

    //UtilityFunctions::print("ArcDialogue: not arc bit: " + id_to + " from connect: " + id);
    return std::pair<String, bool>();
    
}


void godot::ArcDialogue::set_id(String p_cur_id)
{
    this->cur_id = p_cur_id;
    update_text();
}

godot::String godot::ArcDialogue::get_text()
{
    return this->cur_text;
}

int godot::ArcDialogue::get_speaker_count()
{
    return this->cur_speakers.size();
}

godot::String godot::ArcDialogue::get_speaker(int i)
{
    return this->cur_speakers[i];
}

int godot::ArcDialogue::get_answer_count()
{
    return this->cur_answers.size();
}

godot::String godot::ArcDialogue::get_answer_id(int i)
{
    return this->cur_answers[i].first;
}

bool godot::ArcDialogue::get_answer_avaible(int i)
{
    return this->cur_answers[i].second.second;
}

godot::String godot::ArcDialogue::get_answer_text(int i)
{
    return this->cur_answers[i].second.first;
}

void godot::ArcDialogue::answer(int i)
{
}

void godot::ArcDialogue::update_text()
{
    VoidBit *bit = God::get_singleton()->get_bit(cur_id);

    if(bit == nullptr){
        UtilityFunctions::print("ArcDialogue: bit is null: " + cur_id);
        return;
    }

    ArcElementBit *element = Object::cast_to<ArcElementBit>(bit);

    if(!element){
        UtilityFunctions::print("ArcDialogue: bit is not arcElement: " + cur_id);
        return;
    }

    this->cur_text = element->get_content();

    std::vector<String> speakers;

    int speakers_size = element->get_component_size();

    for(int i = 0; i < speakers_size; ++i){
        speakers.push_back(element->get_component(i));
    }
    this->cur_speakers = speakers;

    int output_size = element->get_output_id_count();
    for(int i = 0; i < output_size; ++i){
        String id = element->get_output_id(i);
        std::pair<String, bool>  answer = parse_answer(id, String(), true, i);
        if(answer == std::pair<String, bool>()){
            continue;
        }
        UtilityFunctions::print(answer.first);
        cur_answers.push_back(std::pair<String, std::pair<String, bool>>(id, answer));
    }

}

godot::ArcDialogue::ArcDialogue()
{
}

godot::ArcDialogue::~ArcDialogue()
{
}
