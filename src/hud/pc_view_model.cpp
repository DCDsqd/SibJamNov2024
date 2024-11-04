#include "pc_view_model.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/util.hpp"

void godot::PcViewModel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_monster_img"), &PcViewModel::get_monster_img);
    ClassDB::bind_method(D_METHOD("get_monster_lvl"), &PcViewModel::get_monster_lvl);
    ClassDB::bind_method(D_METHOD("get_monster_name"), &PcViewModel::get_monster_name);
    ClassDB::bind_method(D_METHOD("get_monster_crowd_bonus"), &PcViewModel::get_monster_crowd_bonus);
    ClassDB::bind_method(D_METHOD("get_monster_descr"), &PcViewModel::get_monster_descr);

    ClassDB::bind_method(D_METHOD("set_monster_list_path"), &PcViewModel::set_monster_list_path);
    ClassDB::bind_method(D_METHOD("get_monster_list_path"), &PcViewModel::get_monster_list_path);

    ClassDB::add_property("PcViewModel", PropertyInfo(Variant::NODE_PATH, "monster_list_path"), "set_monster_list_path", "get_monster_list_path");
}

std::string godot::PcViewModel::to_std(String str)
{
    return std::string(str.utf8().get_data());
}

godot::String godot::PcViewModel::to_gd(std::string str)
{
    return String(str.c_str());
}

void godot::PcViewModel::parse_monsters()
{
    String file_path = Util::get_value_from_config("story", "story_map");

    String text = FileAccess::get_file_as_string(file_path);
    if (text == String()) {
        UtilityFunctions::print("PcInteractor: " + text + " file not found");
        return;
    }

    Dictionary dict = JSON::parse_string(text);
    if(dict == Dictionary()){
        UtilityFunctions::print("PcInteractor: " + text + " bat structure");
        return;
    }

    if(!dict.has("Enemy")){
        UtilityFunctions::print("PcInteractor: Enemy is null");
        return;
    }

    Dictionary enemys = dict["Enemy"];
    Array enemys_keys = enemys.keys();

    for(int i = 0; i < enemys_keys.size(); ++i){
        String name = enemys_keys[i];
        parse_monster(enemys[name], name);
    }

}

void godot::PcViewModel::parse_monster(const Dictionary &dict, const String &name)
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
    if(!dict.has("descr")){
        UtilityFunctions::print("SuperClock: person name: " + name + " doesn't have descr");
        return;
    }
    String p_name = dict["name"];
    int lvl = dict["lvl"];
    String img = dict["image"];
    int crowd_bonus = dict["crowd_bonus"];
    String descr = dict["descr"];

    monsters.push_back(PcEnemy(p_name, to_gd(std::to_string(lvl)), img, to_gd(std::to_string(crowd_bonus)), descr));
}

void godot::PcViewModel::update_window()
{
    if(has_node(monster_list_path) && get_node<ItemList>(monster_list_path)){
        ItemList* list = get_node<ItemList>(monster_list_path);
        list->clear();
        for(auto i : monsters){
            list->add_item(i.name);
        }
    }
}

void godot::PcViewModel::_open_window(Entity *interaction, Entity *interactor)
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("OrderHud: hud is null");
        close_window();
        return;
    }

    hud->lock_game();
    set_physics_process_internal(true);
    parse_monsters();
    
    update_window();
}

void godot::PcViewModel::_close_window()
{
    Hud *hud = EternityData::get_singleton()->get_hud();
    if(hud == nullptr){
        UtilityFunctions::print("SimpleViewModel: hud is null");
        return;
    }

    hud->unlock_game();
}

void godot::PcViewModel::_int_process()
{
    if(Input::get_singleton()->is_action_just_released("e_cancel")){
        close_window();
    }
}

void godot::PcViewModel::set_monster_list_path(NodePath p_monster_list_path)
{
    this->monster_list_path = p_monster_list_path;
}

godot::NodePath godot::PcViewModel::get_monster_list_path()
{
    return this->monster_list_path;
}

godot::String godot::PcViewModel::get_monster_name(int i)
{
    if(monsters.size() < i )
        return String();

    return monsters[i].name;
}

godot::String godot::PcViewModel::get_monster_lvl(int i)
{
    if(monsters.size() < i )
        return String();

    return monsters[i].lvl;
}

godot::Ref<godot::Texture2D> godot::PcViewModel::get_monster_img(int i)
{
    if(monsters.size() < i )
        return String();

    return Util::load_image(monsters[i].img);
}

godot::String godot::PcViewModel::get_monster_crowd_bonus(int i)
{
    if(monsters.size() < i )
        return String();

    return monsters[i].crowd_bonus;
}

godot::String godot::PcViewModel::get_monster_descr(int i)
{
    if(monsters.size() < i )
        return String();

    return monsters[i].descr;
}

godot::PcViewModel::PcViewModel()
{
}

godot::PcViewModel::~PcViewModel()
{
}
