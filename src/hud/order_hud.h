#ifndef ORDER_HUD_H
#define ORDER_HUD_H

#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/input.hpp>

#include <vector>

#include "entity/hero/container_entity_data.h"
#include "entity/order/order_container.h"


namespace godot {

class OrderHud : public ViewModel {
	GDCLASS(OrderHud, ViewModel)

protected:
    static void _bind_methods();
    int raw_carrera = 0;
    int sorted_carrera = 0;
    
    NodePath raw_img_path;
    NodePath raw_name_path;
    NodePath raw_descr_path;

    NodePath sorted_img_path;
    NodePath sorted_name_path;
    NodePath sorted_desr_path;
    NodePath sorted_rank_path;

    OrderContainer *order_container = nullptr;
    OrderContainer *hero_container = nullptr;

    OrderContainer *get_container_data(Entity *entity);
    void update_window();
    void draw_raw();
    void draw_sorted();

    void reset_raw();
    void reset_sorted();

public:
    void set_raw_img_path(NodePath p_raw_img_path);
    NodePath get_raw_img_path();
    void set_raw_name_path(NodePath p_raw_name_path);
    NodePath get_raw_name_path();
    void set_raw_descr_path(NodePath p_raw_descr_path);
    NodePath get_raw_descr_path();

    void set_sorted_img_path(NodePath p_sorted_img_path);
    NodePath get_sorted_img_path();
    void set_sorted_name_path(NodePath p_sorted_name_path);
    NodePath get_sorted_name_path();
    void set_sorted_desr_path(NodePath p_sorted_desr_path);
    NodePath get_sorted_desr_path();
    void set_sorted_rank_path(NodePath p_sorted_rank_path);
    NodePath get_sorted_rank_path();

    void rate_current_order(int rank);
    void unrate_current_order();

    void swap_sorted(int to);
    void swap_raw(int to);

	void _open_window(Entity *interaction, Entity *interactor) override;
	void _close_window() override;
	void _int_process() override;

	OrderHud();
	~OrderHud();
};
}


#endif // MULTI_SELECTOR_MODEL_H