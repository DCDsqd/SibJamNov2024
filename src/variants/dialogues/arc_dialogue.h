#ifndef ARC_DIALOGUE_H
#define ARC_DIALOGUE_H

#include <godot_cpp/classes/dialogue.hpp>
#include <godot_cpp/classes/god.hpp>
#include <godot_cpp/classes/arc_asset.hpp>
#include <godot_cpp/classes/arc_condition_bit.hpp>
#include <godot_cpp/classes/arc_element_bit.hpp>
#include <godot_cpp/classes/arc_jumper.hpp>
#include <godot_cpp/classes/arc_component.hpp>
#include <godot_cpp/classes/arc_connect.hpp>
#include <godot_cpp/classes/reg_ex.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

namespace godot {

class ArcDialogue : public Dialogue {
	GDCLASS(ArcDialogue, Dialogue)

protected:
	static void _bind_methods();

	String cur_id;

	String cur_text;
	std::vector<String> cur_speakers;
	std::vector<std::pair<String, std::pair<String, bool>>> cur_answers;
	std::vector<String> cur_audio;

	bool end = false;

	bool check_condition(String gd_condition);
	String check_condition_bit(ArcConditionBit *bit);
	std::pair<String, bool> parse_answer(String id, String label, bool avaible, int num);
	String step_carrera(String id);

	String erase_markup(String input);

public:
	void set_id(String p_cur_id);

	String get_text();
	//String get_cover();
	bool is_end();

	int get_speaker_count();
	String get_speaker(int i);

	int get_answer_count();
	String get_answer_id(int i);
	bool get_answer_avaible(int i);
	String get_answer_text(int i);

	String get_audio();
	
	bool answer(int i);
	bool answer(String name);

	void update_text();

	ArcDialogue();
	~ArcDialogue();
};

}

#endif