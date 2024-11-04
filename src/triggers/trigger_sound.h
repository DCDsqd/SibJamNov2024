#ifndef TRIGGER_SOUND_H
#define TRIGGER_SOUND_H


#include <godot_cpp/classes/trigger3d.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/game_controller.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/model_entity.hpp>
#include <godot_cpp/classes/audio_stream_player3d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/util.hpp>


namespace godot {

class TriggerSound : public Trigger3D {
	GDCLASS(TriggerSound, Trigger3D)

protected:
	static void _bind_methods();
	NodePath speaker_path;

    String sound;

public:
    void set_sound(String p_sound);
    String get_sound();

	void set_speaker(NodePath p_speaker_path);
	NodePath get_speaker();

	virtual bool _activate();

	TriggerSound();
	~TriggerSound();
};

}

#endif //TRIGGER_SOUND_H