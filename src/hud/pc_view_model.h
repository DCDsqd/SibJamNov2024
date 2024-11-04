#ifndef PC_VIEW_MODEL_H
#define PC_VIEW_MODEL_H

#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/item_list.hpp>

#include <vector>
#include <unordered_map>

#include "entity/hero/container_entity_data.h"
#include "entity/order/order_container.h"


namespace godot {

    
struct PcEnemy{
public:
    String name;
    String lvl;
    String crowd_bonus;
    String img;
    String descr;

    PcEnemy(String p_name, String p_lvl, String p_img, String p_crowd_bonus, String p_descr){
        this->name = p_name;
        this->lvl = p_lvl;
        this->img = p_img;
        this->crowd_bonus = p_crowd_bonus;
        this->descr = p_descr;
    }
    PcEnemy(){};

};


class PcViewModel : public ViewModel {
	GDCLASS(PcViewModel, ViewModel)

protected:
    static void _bind_methods();

    std::vector<PcEnemy> monsters;

    std::string to_std(String str);
    String to_gd(std::string str);

    NodePath monster_list_path;

    void parse_monsters();
    void parse_monster(const Dictionary &dict, const String &name);

    void update_window();

public:
	void _open_window(Entity *interaction, Entity *interactor) override;
	void _close_window() override;
	void _int_process() override;

    void set_monster_list_path(NodePath p_monster_list_path);
    NodePath get_monster_list_path();

    String get_monster_name(int i);
    String get_monster_lvl(int i);
    Ref<Texture2D> get_monster_img(int i);
    String get_monster_crowd_bonus(int i);
    String get_monster_descr(int i);


	PcViewModel();
	~PcViewModel();
};
}


#endif // PC_VIEW_MODEL_H