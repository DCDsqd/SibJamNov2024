#ifndef CUSTOMER_VIE_MODEL_H
#define CUSTOMER_VIE_MODEL_H

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

class CustomerViewModel : public ViewModel {
	GDCLASS(CustomerViewModel, ViewModel)

protected:
    static void _bind_methods();
    int carrera = 0;
    
    NodePath custommer_name_path;
    NodePath custommer_lvl_path;
    NodePath order_name_path;
    NodePath order_lvl_path;
    NodePath output_path;

    OrderContainer *order_container = nullptr;
    EntityData *custommer_data = nullptr;

    OrderContainer *get_container_data(Entity *entity);

    bool check_request();
    
    void update_window();
    void update_customer();
    void update_order();
    void reset_quest();

    void try_switch_state();

public:
    void set_custommer_name_path(NodePath p_custommer_name_path);
    NodePath get_custommer_name_path();
    void set_custommer_lvl_path(NodePath p_custommer_lvl_path);
    NodePath get_custommer_lvl_path();
    void set_order_name_path(NodePath p_order_name_path);
    NodePath get_order_name_path();
    void set_order_lvl_path(NodePath p_order_lvl_path);
    NodePath get_order_lvl_path();
    void set_output_path(NodePath p_output_path);
    NodePath get_output_path();

    void swap_carrera(int to);

    void request_quest();

	void _open_window(Entity *interaction, Entity *interactor) override;
	void _close_window() override;
	void _int_process() override;

	CustomerViewModel();
	~CustomerViewModel();
};
}


#endif // CUSTOMER_VIE_MODEL_H