#include "super_clock.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"
#include "variants/const/order_params.hpp"
#include "variants/const/customer_params.hpp"

void godot::SuperClock::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("parse_all"), &SuperClock::parse_all);
    ClassDB::bind_method(D_METHOD("update_orders"), &SuperClock::update_orders);
}

void godot::SuperClock::update_orders()
{
    RandomNumberGenerator *generator =  new RandomNumberGenerator();
    std::vector<Person> tmp_custommer_pull = all_custommer_pull;
    std::vector<Quest> tmp_quest_pull = all_quest_pull;

    if(tmp_custommer_pull.size() == 0){
        UtilityFunctions::print("SuperClock: custommer pull is 0");
        return;
    }

    if(tmp_quest_pull.size() == 0){
        UtilityFunctions::print("SuperClock: quest pull is 0");
        return;
    }

    for(int i = 0; i < custommer_count; ++i){
        int sel = generator->randi_range(0, tmp_custommer_pull.size()-1);
        day_custommer_pull.push_back(tmp_custommer_pull[sel]);
        //UtilityFunctions::print(sel);
        tmp_custommer_pull.erase(tmp_custommer_pull.begin() + sel);
    }

    for(int i = 0; i < quest_count; ++i){
        int sel = generator->randi_range(0, tmp_quest_pull.size()-1);
        day_quest_pull.push_back(tmp_quest_pull[sel]);
        //UtilityFunctions::print(sel);
        tmp_quest_pull.erase(tmp_quest_pull.begin() + sel);
    }

    for(auto i : day_custommer_pull){
        //UtilityFunctions::print(name_from_dialogue_id(i.dialogue_id));
    }
    
}

void godot::SuperClock::set_order_entity_path(NodePath p_order_entity_path)
{
    this->order_entity_path = p_order_entity_path;
}

godot::NodePath godot::SuperClock::get_order_entity_path()
{
    return this->order_entity_path;
}

void godot::SuperClock::update_custommer()
{
}

void godot::SuperClock::parse_custommer(const Dictionary &dict, const String &name)
{
    if(!dict.has("dialogue_id")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have dialogue_id");
        return;
    }
    if(!dict.has("display_lvl")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have display_lvl");
        return;
    }
    if(!dict.has("fact_lvl")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have fact_lvl");
        return;
    }
    if(!dict.has("min_req_lvl")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have min_req_lvl");
        return;
    }
    if(!dict.has("sprite_id")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have sprite_id");
        return;
    }

    String dialogue_id = dict["dialogue_id"];
    int display_lvl = dict["display_lvl"];
    int fact_lvl = dict["fact_lvl"];
    int min_req_lvl = dict["min_req_lvl"];
    String sprite_id = dict["sprite_id"];

    all_custommer_pull.push_back(Person(name, dialogue_id, display_lvl, fact_lvl, min_req_lvl, sprite_id));
    
}

void godot::SuperClock::parse_quest(const Dictionary &dict, const String &name)
{

}

void godot::SuperClock::parse_monster(const Dictionary &dict, const String &name)
{
    if(!dict.has("name")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have dialogue_id");
        return;
    }
    if(!dict.has("lvl")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have dialogue_id");
        return;
    }
    if(!dict.has("image")){
        //UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have dialogue_id");
        return;
    }
    String p_name = dict["name"];
    int lvl = dict["lvl"];
    String img = dict["image"];

    all_moster_pull.push_back(Enemy(p_name, lvl, img));

}

godot::String godot::SuperClock::name_from_dialogue_id(const String &dialogue_id)
{
    VoidBit *bit = God::get_singleton()->get_bit(dialogue_id);
    if(!bit){
        UtilityFunctions::print("SuperClock: not found bit: " + dialogue_id);
        return String();
    }
    
    ArcElementBit *arc_bit = Object::cast_to<ArcElementBit>(bit);
    if(!arc_bit){
        UtilityFunctions::print("SuperClock: not arc bit: " + dialogue_id);
        return String();
    }

    String component_id = arc_bit->get_component(0);
    VoidComponent *component = God::get_singleton()->get_component(component_id);
    if(!component){
        UtilityFunctions::print("SuperClock: not found component: " + component_id);
        return String();
    }

    ArcComponent *arc_component = Object::cast_to<ArcComponent>(component);
    if(!arc_component){
        UtilityFunctions::print("SuperClock: not arc component: " + component_id);
        return String();
    }

    return arc_component->get_name();
}

void godot::SuperClock::parse_all()
{
    String file_path = Util::get_value_from_config("story", "story_map");

    String text = FileAccess::get_file_as_string(file_path);
    if (text == String()) {
        //UtilityFunctions::print("SuperClock: " + text + " file not found");
        return;
    }

    Dictionary dict = JSON::parse_string(text);
    if(dict == Dictionary()){
        //UtilityFunctions::print("SuperClock: " + text + " bat structure");
        return;
    }

    if(!dict.has("Persons")){
        //UtilityFunctions::print("SuperClock: Persons is null");
        return;
    }

    if(!dict.has("Quests")){
        //UtilityFunctions::print("SuperClock: Quests is null");
        return;
    }

    if(!dict.has("Enemy")){
        //UtilityFunctions::print("SuperClock: Enemy is null");
        return;
    }

    Dictionary persons = dict["Persons"];
    Array persons_keys = persons.keys();

    for(int i = 0; i < persons_keys.size(); ++i){
        String name = persons_keys[i];
        UtilityFunctions::print("SuperClock: parse person: " + name);
        parse_custommer(persons[name], name);
    }

    Dictionary quests = dict["Quests"];
    Array quests_keys = quests.keys();

    for(int i = 0; i < quests_keys.size(); ++i){
        String name = quests_keys[i];
        UtilityFunctions::print("SuperClock: parse quest: " + name);
        String descr = quests[name];
        all_quest_pull.push_back(Quest(name, descr));
    }

    Dictionary enemys = dict["Enemy"];
    Array enemys_keys = enemys.keys();

    for(int i = 0; i < enemys_keys.size(); ++i){
        String name = enemys_keys[i];
        UtilityFunctions::print("SuperClock: parse enemy: " + name);
        parse_monster(enemys[name], name);
    }
}

godot::SuperClock::SuperClock()
{
}

godot::SuperClock::~SuperClock()
{
}
