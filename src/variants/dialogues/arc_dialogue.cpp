#include "arc_dialogue.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"

void godot::ArcDialogue::_bind_methods()
{
    
}

bool godot::ArcDialogue::check_condition(String gd_condition)
{
    std::string condition = std::string(gd_condition.utf8().get_data());

    std::istringstream ss(condition);
    std::string token;
    
    bool result = true;
    bool currentCondition = true;
    bool isAnd = true;
    
    while (ss >> token) {
        if (token == "and" || token == "or") {
            isAnd = (token == "and");
        } else {
            int varValue = God::get_singleton()->get_variable(token.c_str());

            std::string op;
            int value;
            ss >> op >> value;
            
            if (op == "==") currentCondition = (varValue == value);
            else if (op == "&lt;") currentCondition = (varValue < value);
            else if (op == "&gt;") currentCondition = (varValue > value);
            else if (op == "&lt;=") currentCondition = (varValue <= value);
            else if (op == "&gt;=") currentCondition = (varValue >= value);
            else if (op == "!=") currentCondition = (varValue != value);
            else throw std::invalid_argument("Unsupported operator: " + op);
            
            if (isAnd) result &= currentCondition;
            else result |= currentCondition;
        }
    }
    
    return result;
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
        return std::pair<String, bool>(erase_markup(label), avaible);
    }

    ArcJumper *arc_jumper = Object::cast_to<ArcJumper>(bit);
    if(arc_jumper){
        return std::pair<String, bool>(erase_markup(label), avaible);
    }

    ArcConditionBit *arc_condition = Object::cast_to<ArcConditionBit>(bit);
    if(arc_condition){
        String next_id = check_condition_bit(arc_condition);
        if(next_id == String()){
            if(label == String()){
                UtilityFunctions::print("ArcDialogue: unable");
                return std::pair<String, bool>();
            }
            return std::pair<String, bool>(erase_markup(label), false);
        }
        return parse_answer(next_id, label, avaible, num);

    }

    //UtilityFunctions::print("ArcDialogue: not arc bit: " + id_to + " from connect: " + id);
    return std::pair<String, bool>();
    
}

godot::String godot::ArcDialogue::step_carrera(String id)
{
    VoidConnect *connect = God::get_singleton()->get_connect(id);
    if(!connect){
        UtilityFunctions::print("ArcDialogue: connect is not found: " + id);
        return String();
    }

    ArcConnect *arc_connect = Object::cast_to<ArcConnect>(connect);
    if(!arc_connect){
        UtilityFunctions::print("ArcDialogue: connect is not arc: " + id);
        return String();
    }

    String id_to = arc_connect->get_to();

    VoidBit *bit = God::get_singleton()->get_bit(id_to);
    if(!bit){
        UtilityFunctions::print("ArcDialogue: not found to_id: " + id_to + " from connect: " + id);
        return String();
    }

    ArcElementBit *arc_element_bit = Object::cast_to<ArcElementBit>(bit);
    if(arc_element_bit){
        return arc_element_bit->get_id();
    }

    ArcJumper *arc_jumper = Object::cast_to<ArcJumper>(bit);
    if(arc_jumper){
        return arc_jumper->get_element_id();
    }

    ArcConditionBit *arc_condition = Object::cast_to<ArcConditionBit>(bit);
    if(arc_condition){
        String next_id = check_condition_bit(arc_condition);
        if(next_id == String()){
            UtilityFunctions::print("ArcDialogue: unable win condition: " + bit->get_id());
            return String();
        }
        return step_carrera(next_id);
    }

    UtilityFunctions::print("ArcDialogue: not arc bit: " + bit->get_id());
    return bit->get_id();
}

godot::String godot::ArcDialogue::erase_markup(String input)
{
    RegEx *regex = new RegEx();
    regex->compile("\\<.*?\\>");
    return regex->sub(input, "", true);
}

void godot::ArcDialogue::set_id(String p_cur_id)
{
    this->cur_id = p_cur_id;
    this->cur_answers.clear();
    this->cur_audio.clear();
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

bool godot::ArcDialogue::is_end()
{
    return this->end;
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

godot::String godot::ArcDialogue::get_audio()
{
    if(this->cur_audio.size() == 0)
        return String();
    
    return this->cur_audio[0];
}

bool godot::ArcDialogue::answer(int i)
{
    if(cur_answers.size() < i){
        UtilityFunctions::print("ArcDialogue: answer out of range: " + i);
        return false;
    }

    String connect_id = cur_answers[i].first;
    String next_id = step_carrera(connect_id);

    if(next_id == String()){
        end = true;
        return false;
    }

    set_id(next_id);
    return true;
}

bool godot::ArcDialogue::answer(String name)
{
    for(int i = 0; i < cur_answers.size(); ++i){
        if(cur_answers[i].second.first == name){
            return answer(i);
        }
    }
    return false;
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

    std::vector<String> audios;

    int audio_size = element->get_audio_size();
    for(int i = 0; i < audio_size; ++i){
        audios.push_back(element->get_audio_asset(i));
    }
    this->cur_audio = audios;

    int output_size = element->get_output_id_count();
    for(int i = 0; i < output_size; ++i){
        String id = element->get_output_id(i);
        std::pair<String, bool>  answer = parse_answer(id, String(), true, i);
        if(answer == std::pair<String, bool>()){
            continue;
        }
        //UtilityFunctions::print(answer.first);
        cur_answers.push_back(std::pair<String, std::pair<String, bool>>(id, answer));
    }

    if(cur_answers.size() == 0){
        end = true;
    }

}

godot::ArcDialogue::ArcDialogue()
{
}

godot::ArcDialogue::~ArcDialogue()
{
}
