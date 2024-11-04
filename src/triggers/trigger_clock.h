#ifndef TRIGGER_CLOCK_H
#define TRIGGER_CLOCK_H


#include <godot_cpp/classes/trigger3d.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/game_controller.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/model_entity.hpp>
#include <godot_cpp/classes/audio_stream_player3d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/util.hpp>

#include "util/super_clock.h"


namespace godot {

class TriggerClock : public Trigger3D {
	GDCLASS(TriggerClock, Trigger3D)

protected:
    static void _bind_methods();

	NodePath clock_path;

public:
	void set_clock_path(NodePath p_clock_path);
	NodePath get_clock_path();

	virtual bool _activate();

	TriggerClock();
	~TriggerClock();
};

}

#endif //TRIGGER_CLOCK_H