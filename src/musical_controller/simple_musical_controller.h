#ifndef SIMPLE_MUSICAL_CONTROLLER
#define SIMPLE_MUSICAL_CONTROLLER

#include <godot_cpp/classes/music_controller.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/menu_element.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/util.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

namespace godot {

class SimpleMusicalController : public MusicController {
	GDCLASS(SimpleMusicalController, MusicController)

protected:
	static void _bind_methods();

    NodePath player1_path;
	NodePath player2_path;
	AudioStreamPlayer *player1 = nullptr;
	AudioStreamPlayer *player2 = nullptr;

	bool transition = false;
	String current_track = String();
	float current_duration = 0.0f;

public:
    void set_player1_path(NodePath p_player1_path);
	NodePath get_player1_path();
	void set_player2_path(NodePath p_player2_path);
	NodePath get_player2_path();

    void change_players();

	void music_swapper();
	void music_listen();

	void _swap_music(const String &name) override;
	void _init_links() override;
	void _int_process() override;
    void _play_music(const Ref<AudioStream> &sound) override;

	SimpleMusicalController();
	~SimpleMusicalController();
};

}

#endif //SIMPLE_MUSICAL_CONTROLLER