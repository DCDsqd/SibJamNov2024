#ifndef HERO_INPUT_H
#define HERO_INPUT_H

#include <godot_cpp/classes/void_input.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/moving_entity.hpp>
#include <godot_cpp/classes/game_controller.hpp>
#include <godot_cpp/classes/trigger3d.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include "godot_cpp/classes/eternity_data.hpp"
#include "godot_cpp/classes/e_camera.hpp"

#include "godot_cpp/classes/world3d.hpp"
#include "godot_cpp/classes/physics_direct_space_state3d.hpp"
#include "godot_cpp/classes/physics_ray_query_parameters3d.hpp"
#include "godot_cpp/classes/viewport.hpp"

namespace godot {

class HeroInput : public VoidInput {
	GDCLASS(HeroInput, VoidInput)

private:
	double time_passed;
	Input *input = nullptr;

    TypedArray<String> triggers;
    int carrera = 0;
	float interact_distance = 100.0f;

protected:
	static void _bind_methods();

    void move_carrera(int to);
    void set_camera();
	Dictionary get_mouse_collision(); 

public:
	void _int_process() override;
	void _on_death() override;
	void _set_entity() override;

	void set_carrera(int i);
    void add_trigger(String name);
	void move();
	void interact();
	

	HeroInput();
	~HeroInput();
};

}

#endif //HUMAN_INPUT_H