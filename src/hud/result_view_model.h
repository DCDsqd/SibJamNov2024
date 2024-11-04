#ifndef RESULT_VIEWMODEL_H
#define RESULT_VIEWMODEL_H

#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <vector>

#include "entity/hero/container_entity_data.h"
#include "entity/order/order_container.h"


namespace godot {

class ResultViewModel : public ViewModel {
	GDCLASS(ResultViewModel, ViewModel)

protected:
    static void _bind_methods();

    bool death;
    bool time_end;
    String str_descr;

    bool is_end;
    
    NodePath descr_path;
    NodePath result_path;
    NodePath button_path;

    void update_window();

public:
    void set_result(bool p_death, bool p_time_end, String p_str_descr);

    void press();

    void set_descr_path(NodePath p_descr_path);
    NodePath get_descr_path();

    void set_result_path(NodePath p_result_path);
    NodePath get_result_path();

    void set_button_path(NodePath p_button_path);
    NodePath get_button_path();


	void _open_window(Entity *interaction, Entity *interactor) override;
	void _close_window() override;
	void _int_process() override;

	ResultViewModel();
	~ResultViewModel();
};
}


#endif // RESULT_VIEWMODEL_H