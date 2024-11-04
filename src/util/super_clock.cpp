#include "super_clock.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"
#include "variants/const/order_params.hpp"
#include "variants/const/customer_params.hpp"

void godot::SuperClock::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("parse_all"), &SuperClock::parse_all);
    ClassDB::bind_method(D_METHOD("update_day_pulls"), &SuperClock::update_day_pulls);
    ClassDB::bind_method(D_METHOD("update_custommer"), &SuperClock::update_custommer);
    ClassDB::bind_method(D_METHOD("update_quests"), &SuperClock::update_quests);

    ClassDB::bind_method(D_METHOD("set_custommer_entity_path"), &SuperClock::set_custommer_entity_path);
    ClassDB::bind_method(D_METHOD("get_custommer_entity_path"), &SuperClock::get_custommer_entity_path);

    ClassDB::bind_method(D_METHOD("set_order_entity_path"), &SuperClock::set_order_entity_path);
    ClassDB::bind_method(D_METHOD("get_order_entity_path"), &SuperClock::get_order_entity_path);

    ClassDB::add_property("SuperClock", PropertyInfo(Variant::NODE_PATH, "custommer_entity_path"), "set_custommer_entity_path", "get_custommer_entity_path");
    ClassDB::add_property("SuperClock", PropertyInfo(Variant::NODE_PATH, "order_entity_path"), "set_order_entity_path", "get_order_entity_path");

}


void godot::SuperClock::set_order_entity_path(NodePath p_order_entity_path)
{
    this->order_entity_path = p_order_entity_path;
}

godot::NodePath godot::SuperClock::get_order_entity_path()
{
    return this->order_entity_path;
}

void godot::SuperClock::set_custommer_entity_path(NodePath p_custommer_entity_path)
{
    this->custommer_entity_path = p_custommer_entity_path;
}

godot::NodePath godot::SuperClock::get_custommer_entity_path()
{
    return this->custommer_entity_path;
}

void godot::SuperClock::parse_custommer(const Dictionary &dict, const String &name)
{
    if(!dict.has("dialogue_id")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have dialogue_id");
        return;
    }
    if(!dict.has("display_lvl")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have display_lvl");
        return;
    }
    if(!dict.has("fact_lvl")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have fact_lvl");
        return;
    }
    if(!dict.has("min_req_lvl")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have min_req_lvl");
        return;
    }
    if(!dict.has("sprite_id")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have sprite_id");
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
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have name");
        return;
    }
    if(!dict.has("lvl")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have lvl");
        return;
    }
    if(!dict.has("image")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have image");
        return;
    }
    if(!dict.has("crowd_bonus")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have crowd_bonus");
        return;
    }
    String p_name = dict["name"];
    int lvl = dict["lvl"];
    String img = dict["image"];
    int crowd_bonus = dict["crowd_bonus"];

    all_moster_pull.push_back(Enemy(p_name, lvl, img, crowd_bonus));

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

std::vector<std::vector<godot::Enemy>> godot::SuperClock::top_combinations(const std::vector<Enemy>& enemies, int max_sum)
{
    std::vector<std::vector<Enemy>> best_combinations;
    int max_lvl_sum = 0;

    // Перебираем все возможные комбинации по два с повторениями
    for (size_t i = 0; i < enemies.size(); ++i) {
        for (size_t j = 0; j < enemies.size(); ++j) {
            int lvl_sum = enemies[i].crowd_bonus + enemies[j].crowd_bonus;

            // Если сумма подходит и она больше текущей максимальной, обновляем
            if (lvl_sum <= max_sum && lvl_sum >= max_lvl_sum) {
                // Если нашли новую максимальную сумму, сбрасываем предыдущие комбинации
                if (lvl_sum > max_lvl_sum) {
                    best_combinations.clear();
                    max_lvl_sum = lvl_sum;
                }
                // Добавляем текущую комбинацию
                best_combinations.push_back({ enemies[i], enemies[j] });
            }
        }
    }

    return best_combinations;
}

std::vector<godot::Enemy> godot::SuperClock::get_by_diaposon(const std::vector<Enemy> &enemies, int min, int max)
{
    std::vector<Enemy> ret;
    for(auto i : enemies){
        if(min <= i.lvl && i.lvl <= max){
            ret.push_back(i);
        }
    }

    return ret;

}

void godot::SuperClock::parse_all()
{
    String file_path = Util::get_value_from_config("story", "story_map");

    String text = FileAccess::get_file_as_string(file_path);
    if (text == String()) {
        UtilityFunctions::print("SuperClock: " + text + " file not found");
        return;
    }

    Dictionary dict = JSON::parse_string(text);
    if(dict == Dictionary()){
        UtilityFunctions::print("SuperClock: " + text + " bat structure");
        return;
    }

    if(!dict.has("Persons")){
        UtilityFunctions::print("SuperClock: Persons is null");
        return;
    }

    if(!dict.has("Quests")){
        UtilityFunctions::print("SuperClock: Quests is null");
        return;
    }

    if(!dict.has("Enemy")){
        UtilityFunctions::print("SuperClock: Enemy is null");
        return;
    }

    Dictionary persons = dict["Persons"];
    Array persons_keys = persons.keys();

    for(int i = 0; i < persons_keys.size(); ++i){
        String name = persons_keys[i];
        //UtilityFunctions::print("SuperClock: parse person: " + name);
        parse_custommer(persons[name], name);
    }

    Dictionary quests = dict["Quests"];
    Array quests_keys = quests.keys();

    for(int i = 0; i < quests_keys.size(); ++i){
        String name = quests_keys[i];
        //UtilityFunctions::print("SuperClock: parse quest: " + name);
        String descr = quests[name];
        //UtilityFunctions::print("SuperClock: parse quest: " + descr);
        all_quest_pull.push_back(Quest(name, descr));
    }

    Dictionary enemys = dict["Enemy"];
    Array enemys_keys = enemys.keys();

    for(int i = 0; i < enemys_keys.size(); ++i){
        String name = enemys_keys[i];
        //UtilityFunctions::print("SuperClock: parse enemy: " + name);
        parse_monster(enemys[name], name);
    }
}


void godot::SuperClock::update_day_pulls()
{
    RandomNumberGenerator *generator =  new RandomNumberGenerator();
    std::vector<Person> tmp_custommer_pull = all_custommer_pull;
    std::vector<Quest> tmp_quest_pull = all_quest_pull;

    if(tmp_custommer_pull.size() < custommer_count){
        UtilityFunctions::print("SuperClock: custommer pull so little");
        return;
    }

    if(tmp_quest_pull.size() < custommer_count){
        UtilityFunctions::print("SuperClock: quest pull so little");
        return;
    }

    for(int i = 0; i < custommer_count; ++i){
        int sel = generator->randi_range(0, tmp_custommer_pull.size()-1);

        day_custommer_pull.push_back(tmp_custommer_pull[sel]);
        day_quest_lvl_pull.push_back(tmp_custommer_pull[sel].fact_lvl);

        tmp_custommer_pull.erase(tmp_custommer_pull.begin() + sel);

    }

    return;
    for(int i = 0; i < custommer_count; ++i){
        int sel = generator->randi_range(0, tmp_quest_pull.size()-1);

        day_quest_pull.push_back(tmp_quest_pull[sel]);

        tmp_quest_pull.erase(tmp_quest_pull.begin() + sel);
    }
    
}

void godot::SuperClock::update_custommer()
{
    if(day_custommer_pull.size() == 0){
        UtilityFunctions::print("SuperClock: day_custommer_pull size 0");
        return;
    }

    if(!(has_node(custommer_entity_path) && get_node<ModelEntity>(custommer_entity_path))){
        UtilityFunctions::print("SuperClock: custommer_entity_path is incorrect");
        return;
    }
    ModelEntity *model = get_node<ModelEntity>(custommer_entity_path);

    Entity *entity = model->get_entity();
    if(!entity){
        UtilityFunctions::print("SuperClock: entity in custommer_entity is null");
        return;
    }

    EntityData *data = entity->get_data();
    if(!data){
        UtilityFunctions::print("SuperClock: data in custommer_entity is null");
        return;
    }
    UtilityFunctions::print("SuperClock: new custommer");

    Person person = day_custommer_pull[0];
    day_custommer_pull.erase(day_custommer_pull.begin());

    CustommerBuilder *builder = memnew(CustommerBuilder);
    builder->set_data(data);
    builder->set_state(0);
    builder->set_name(name_from_dialogue_id(person.dialogue_id));
    builder->set_min_req_level(person.min_req_lvl);
    builder->set_fact_level(person.fact_lvl);
    builder->set_dialogue_id(person.dialogue_id);
    builder->set_display_level(person.display_lvl);
    builder->set_sprite(person.sprite_id);
    entity->emit_signal("on_buffs_change");
    
    //UtilityFunctions::print("SuperClock: customer is seted");
    memdelete(builder);
}

void godot::SuperClock::update_quests()
{
    if(day_quest_lvl_pull.size() < custommer_count){
        UtilityFunctions::print("SuperClock: day_custommer_pull so little" + Util::int_to_godot_str(day_quest_lvl_pull.size()));
        return;
    }

    if(!(has_node(order_entity_path) && get_node<ModelEntity>(order_entity_path))){
        UtilityFunctions::print("SuperClock: order_entity_path is incorrect");
        return;
    }
    ModelEntity *model = get_node<ModelEntity>(order_entity_path);

    Entity *entity = model->get_entity();
    if(!entity){
        UtilityFunctions::print("SuperClock: entity in custommer_entity is null");
        return;
    }

    EntityData *data = entity->get_data();
    if(!data){
        UtilityFunctions::print("SuperClock: data in custommer_entity is null");
        return;
    }

    ContainerEntityData *container_data = Object::cast_to<ContainerEntityData>(data);
    if(!container_data){
        UtilityFunctions::print("SuperClock: data is not container");
        return;
    }

    OrderContainer *container = container_data->get_order_container();
    if(!container){
        UtilityFunctions::print("SuperClock: container_data doesn't have container");
        return;
    }


    UtilityFunctions::print("SuperClock: level pull:");
    for(auto i : day_quest_lvl_pull){
        UtilityFunctions::print(Util::int_to_godot_str(i));
    }

    RandomNumberGenerator *generator = new RandomNumberGenerator();
    OrderBuilder *order_builder = memnew(OrderBuilder);

    for(auto i : day_quest_lvl_pull){

        std::vector<Enemy> arr = get_by_diaposon(all_moster_pull, i-15, i);

        if(arr.size() == 0){
            int num = generator->randi_range(0, all_moster_pull.size()-1);
            arr.push_back(all_moster_pull[num]);
        }

        int num = generator->randi_range(0, arr.size()-1);
        //UtilityFunctions::print("SuperClock: arr size: " + Util::int_to_godot_str(arr.size()) + " num is: " + Util::int_to_godot_str(num));
        //continue;

        Enemy start_enemy = arr[num];
        int start_lvl = start_enemy.lvl + start_enemy.crowd_bonus;

        std::vector<std::vector<Enemy>> top = top_combinations(all_moster_pull, i-start_lvl);

        std::vector<Enemy> enemy_arr;
        if(top.size() != 0){
            int random_num = generator->randi_range(0, top.size() - 1);

            enemy_arr = top[random_num];
            
        }
        enemy_arr.push_back(start_enemy);
        int final_lvl = start_enemy.lvl;

        //UtilityFunctions::print("SuperClock: enemy pull");
        for(auto i : enemy_arr){
            final_lvl += i.crowd_bonus;
            //UtilityFunctions::print(i.name);
        }
        //UtilityFunctions::print(Util::int_to_godot_str(final_lvl));

        int random_order = generator->randi_range(0, all_quest_pull.size()-1);
        String name = all_quest_pull[random_order].name;
        String descr = all_quest_pull[random_order].descr + "\n";

        all_quest_pull.erase(all_quest_pull.begin() + random_order);
        
        for(auto i : enemy_arr){
            descr = descr + "- "+ i.name + "\n";
        }

        order_builder->create_order();

        order_builder->set_name(name);
        order_builder->set_descr(descr);
        order_builder->set_fact_level(final_lvl);

        container->add_order(order_builder->get_entity());
    }
    
    memdelete(order_builder);
}

void godot::SuperClock::new_day()
{
}

godot::SuperClock::SuperClock()
{
}

godot::SuperClock::~SuperClock()
{
}
