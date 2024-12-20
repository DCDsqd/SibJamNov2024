#ifndef SUPER_CLOCK_H
#define SUPER_CLOCK_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/Entity.hpp>
#include <godot_cpp/classes/interaction.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/god.hpp>
#include <godot_cpp/classes/void_bit.hpp>
#include <godot_cpp/classes/arc_element_bit.hpp>
#include <godot_cpp/classes/void_component.hpp>
#include <godot_cpp/classes/arc_component.hpp>
#include <godot_cpp/classes/model_entity.hpp>
#include <godot_cpp/classes/label3d.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "entity/hero/container_entity_data.h"

#include "entity/builder/custommer_builder.h"
#include "entity/builder/order_builder.h"
#include "hud/result_view_model.h"

#include <vector>

namespace godot {

struct Person{
public:
    String name;
    String dialogue_id;
    int display_lvl = -1;
    int fact_lvl = -1;
    int min_req_lvl = -1;
    String sprite_id;
    String stage_var;
    
    Person(String p_name, String p_dialogue_id, int p_display_lvl, int p_fact_lvl, int p_min_req_lvl, String p_sprite_id, String p_stage_var){
        this->name = p_name;
        this->dialogue_id = p_dialogue_id;
        this->display_lvl = p_display_lvl;
        this->fact_lvl = p_fact_lvl;
        this->min_req_lvl = p_min_req_lvl;
        this->sprite_id = p_sprite_id;
        this->stage_var = p_stage_var;
    }
    Person(){}
};

struct Quest{
public:
    String name;
    String descr;
    String img;

    Quest(String p_name, String p_descr, String p_img){
        this->name = p_name;
        this->descr = p_descr;
        this->img = p_img;
    }
    Quest(){};

};

struct Enemy{
public:
    String name;
    int lvl = 0;
    int crowd_bonus = 0;
    String img;

    Enemy(String p_name, int p_lvl, String p_img, int p_crowd_bonus){
        this->name = p_name;
        this->lvl = p_lvl;
        this->img = p_img;
        this->crowd_bonus = p_crowd_bonus;
    }
    Enemy(){};

};

class SuperClock : public Node3D{
    GDCLASS(SuperClock, Node3D);

protected:
    static void _bind_methods();

    int custommer_count = 3;
    int custommer_min = 3;
    int day = 0;

    bool timer_tick = true;
    float start_time = 240;
    float time = start_time;

    NodePath clock_path;
    Label3D *clock;

    NodePath order_entity_path;
    Entity *order_entity;

    NodePath custommer_entity_path;
    Entity *custommer_entity;

    std::vector<Person> all_custommer_pull;
    std::vector<Quest> all_quest_pull;
    std::vector<Enemy> all_moster_pull;

    std::vector<Person> day_custommer_pull;
    std::vector<int> day_quest_lvl_pull;
    std::vector<Quest> day_quest_pull;

    std::vector<std::pair<String, int>> answers;

    void parse_custommer(const Dictionary &dict, const String &name);
    void parse_quest(const Dictionary &dict, const String &name);
    void parse_monster(const Dictionary &dict, const String &name);
    void collect_custommer();
    void update_day_pulls();
    void update_quests();
    void update_custommer();

    void results();
    void spawn_view_model(bool death, bool time, String descrt);
    void check_end();

    void update_clock(int itime);
    

    String name_from_dialogue_id(const String &dialogue_id);

    std::vector<std::vector<Enemy>> top_combinations(const std::vector<Enemy>& enemies, int max_sum);
    std::vector<Enemy> get_by_diaposon(const std::vector<Enemy>& enemies, int min, int max);

public:
    void parse_all();
    void new_day();
    void acess_customer();

    void activate_timer();

    void _process(float delta);

    void set_order_entity_path(NodePath p_order_entity_path);
    NodePath get_order_entity_path();

    void set_custommer_entity_path(NodePath p_custommer_entity_path);
    NodePath get_custommer_entity_path();

    void set_clock_path(NodePath p_clock_path);
    NodePath get_clock_path();

    SuperClock();
    ~SuperClock();

};

}

#endif //SUPER_CLOCK_H