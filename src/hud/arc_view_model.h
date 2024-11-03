#ifndef ARC_VIEW_MODEL_H
#define ARC_VIEW_MODEL_H

#include <godot_cpp/classes/move_component.hpp>
#include <godot_cpp/classes/moving_entity.hpp>
#include <godot_cpp/classes/view_model.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/box_container.hpp>
#include <godot_cpp/classes/text_edit.hpp>

#include "variants/dialogues/arc_dialogue.h"

namespace godot {

class ArcViewModel : public ViewModel {
	GDCLASS(ArcViewModel, ViewModel)

protected:
    static void _bind_methods();

	NodePath answer_container_path;
    NodePath speaker_name_field_path;
    NodePath text_field_path;

    ArcDialogue *dialogue;

    void update_winow();
    void update_answer(const std::vector<String> &answers);

public:
	void set_answer_container_path(NodePath p_answer_container_path);
	NodePath get_answer_container_path();
	void set_speaker_name_field_path(NodePath p_speaker_name_field_path);
	NodePath get_speaker_name_field_path();
	void set_text_field_path(NodePath p_text_field_path);
	NodePath get_text_field_path();

	void _open_window(Entity *interaction, Entity *interactor) override;
	void _close_window() override;
	void _int_process() override;

	ArcViewModel();
	~ArcViewModel();
};
}


#endif // USE_IMPACT_MODEL_H