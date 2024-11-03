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

namespace godot {

class ArcDialogue : public Dialogue {
	GDCLASS(ArcDialogue, Dialogue)

protected:
	static void _bind_methods();


	String cur_id;

	std::vector<String> cur_speakers;
	//std::vector<String> cur_audios;
	std::vector<std::pair<String, std::pair<String, bool>>> cur_answers;

	String cur_text;
	//String cur_cover;


	bool check_condition(String condition);
	String check_condition_bit(ArcConditionBit *bit);
	std::pair<String, bool> parse_answer(String id, String label, bool avaible, int num);

public:
	void set_id(String p_cur_id);

	String get_text();
	//String get_cover();
	
	int get_speaker_count();
	String get_speaker(int i);

	int get_answer_count();
	String get_answer_id(int i);
	bool get_answer_avaible(int i);
	String get_answer_text(int i);
	
	void answer(int i);

	void update_text();

	ArcDialogue();
	~ArcDialogue();
};

}

#endif