#ifndef ARC_HUD_DIALOGUE_H
#define ARC_HUD_DIALOGUE_H

#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/box_container.hpp>
#include <godot_cpp/classes/hud.hpp>
#include <godot_cpp/classes/hud_dialogue.hpp>
#include <godot_cpp/classes/dialogue.hpp>
#include "variants/dialogues/arc_dialogue.h"

namespace godot {

class ArcHudDialogue : public HudDialogue {
	GDCLASS(ArcHudDialogue, HudDialogue)

protected:
	static void _bind_methods();

	NodePath text_field_path;
	RichTextLabel *text_field = nullptr;

	NodePath speaker_name_field_path;
	Label *speaker_name_field = nullptr;

	NodePath answer_container_path;
	BoxContainer *answer_container = nullptr;
	

public:
	void _play_dialogue(Dialogue *dialogue) override;
    void _end_dialogue() override;
    void _int_process() override;
    void _init_links() override;

	void set_text_field_path(NodePath p_text_field_path);
	NodePath get_text_field_path();

	void set_speaker_name_field_path(NodePath p_speaker_name_field_path);
	NodePath get_speaker_name_field_path();

	void set_answer_container_path(NodePath p_answer_container_path);
	NodePath get_answer_container_path();

	ArcHudDialogue();
	~ArcHudDialogue();
};

}

#endif