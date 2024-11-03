#ifndef TRIGGER_CAMERA_H
#define TRIGGER_CAMERA_H


#include <godot_cpp/classes/trigger3d.hpp>
#include <godot_cpp/classes/eternity_data.hpp>
#include <godot_cpp/classes/e_camera.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/model_entity.hpp>
#include <godot_cpp/classes/entity.hpp>
#include <godot_cpp/classes/entity_data.hpp>
#include <godot_cpp/classes/e_camera.hpp>


namespace godot {

class TriggerCamera : public Trigger3D {
	GDCLASS(TriggerCamera, Trigger3D)

protected:
	static void _bind_methods();


	bool reset_default = false;

	bool target_path_change = false;
	NodePath target_path = NodePath();
	bool outside_delta_change = false;
	Vector3 outside_delta = Vector3(0.0f, 0.0f, 0.0f);
	bool speed_scale_change = false;
	float speed_scale = 0.0f;
	bool inside_offset_change = false;
	float inside_offset = 0.0f;
	bool offset_delta_change = false;
	float offset_delta = 0.0f;
	bool rotation_camera_change = false;
	Vector3 rotation_camera = Vector3(0.0f, 0.0f, 0.0f);

	void set_target(ECamera *camera);
	void set_default(ECamera *camera);

public:
	virtual bool _activate() override;

	void set_reset_default(bool p_reset_default);
	bool get_reset_default();

	void set_target_path_change(bool p_target_path_change);
	bool get_target_path_change();

	void set_target_path(NodePath p_target_path);
	NodePath get_target_path();

	void set_outside_delta_change(bool p_outside_delta_change);
	bool get_outside_delta_change();

	void set_outside_delta(Vector3 p_outside_delta);
	Vector3 get_outside_delta();

	void set_speed_scale_change(bool p_speed_scale_change);
	bool get_speed_scale_change();

	void set_speed_scale(float p_speed_scale);
	float get_speed_scale();

	void set_inside_offset_change(bool p_inside_offset_change);
	bool get_inside_offset_change();

	void set_inside_offset(float p_inside_offset);
	float get_inside_offset();

	void set_offset_delta_change(bool p_offset_delta_change);
	bool get_offset_delta_change();

	void set_offset_delta(float p_offset_delta);
	float get_offset_delta();

	void set_rotation_camera_change(bool p_rotation_camera_change);
	bool get_rotation_camera_change();

	void set_rotation_camera(Vector3 p_rotation_camera);
	Vector3 get_rotation_camera();

	TriggerCamera();
	~TriggerCamera();
};

}

#endif //TRIGGER_CAMERA_H