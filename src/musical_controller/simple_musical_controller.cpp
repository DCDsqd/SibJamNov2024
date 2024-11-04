#include "simple_musical_controller.h"
#include "godot_cpp/variant/utility_functions.hpp"


void godot::SimpleMusicalController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_player1_path"), &SimpleMusicalController::set_player1_path);
	ClassDB::bind_method(D_METHOD("get_player1_path"), &SimpleMusicalController::get_player1_path);
	ClassDB::bind_method(D_METHOD("set_player2_path"), &SimpleMusicalController::set_player2_path);
	ClassDB::bind_method(D_METHOD("get_player2_path"), &SimpleMusicalController::get_player2_path);

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "player1_path"), "set_player1_path", "get_player1_path");
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "player2_path"), "set_player2_path", "get_player2_path");

    ADD_SIGNAL(MethodInfo("last_seconds"));
}

void godot::SimpleMusicalController::set_player1_path(NodePath p_player1_path)
{
    this->player1_path = p_player1_path;
}

godot::NodePath godot::SimpleMusicalController::get_player1_path()
{
    return this->player1_path;
}

void godot::SimpleMusicalController::set_player2_path(NodePath p_player2_path)
{
    this->player2_path = p_player2_path;
}

godot::NodePath godot::SimpleMusicalController::get_player2_path()
{
    return this->player2_path;
}

void godot::SimpleMusicalController::change_players()
{
    AudioStreamPlayer *player = player1;
	player1 = player2;
	player2 = player;
}

void godot::SimpleMusicalController::music_swapper()
{
    float loud1 = player1->get_volume_db();
	if (loud1 < 1)
		player1->set_volume_db(loud1 + 0.1);

	float loud2 = player2->get_volume_db();
	if (loud2 > -20)
		player2->set_volume_db(loud2 - 0.1);

	if (loud1 >= 1 && loud2 <= -20)
		transition = false;
}

void godot::SimpleMusicalController::music_listen()
{
    if (current_track == String())
		return;

	if (player1->get_playback_position() + 5 >= current_duration) {
		swap_music(current_track);
		transition = true;
	}
}

void godot::SimpleMusicalController::_swap_music(const String &name)
{
    Ref<AudioStream> sound = Util::load_music(name);
	if (sound == Ref<AudioStream>()) {
		UtilityFunctions::print("SimpleMusicController: music not found");
		return;
	}
	current_track = name;
	play_music(sound);
}

void godot::SimpleMusicalController::_init_links()
{
    EternityData::get_singleton()->set_music_controller(this);

	if (has_node(player1_path) && get_node<AudioStreamPlayer>(player1_path)) {
		this->player1 = get_node<AudioStreamPlayer>(player1_path);
	} else {
		UtilityFunctions::print("SimpleMusicController: player1 is incorrect");
	}

	if (has_node(player2_path) && get_node<AudioStreamPlayer>(player2_path)) {
		this->player2 = get_node<AudioStreamPlayer>(player2_path);
	} else {
		UtilityFunctions::print("SimpleMusicController: player2 is incorrect");
	}

	set_physics_process_internal(true);
}

void godot::SimpleMusicalController::_int_process()
{
    music_listen();
	if (transition)
		music_swapper();
}

void godot::SimpleMusicalController::_play_music(const Ref<AudioStream> &sound)
{
    change_players();

	if (player1 == nullptr || player2 == nullptr) {
		UtilityFunctions::print("players is null");
		return;
	}

	this->current_duration = sound->get_length();
	UtilityFunctions::print(current_duration);
	player1->set_stream(sound);
	player1->play();

	transition = true;
}

godot::SimpleMusicalController::SimpleMusicalController()
{
}

godot::SimpleMusicalController::~SimpleMusicalController()
{
}
