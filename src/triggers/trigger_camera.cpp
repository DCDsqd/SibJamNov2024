#include "trigger_camera.h"
#include "godot_cpp/variant/utility_functions.hpp"

void godot::TriggerCamera::_bind_methods()
{

    ClassDB::bind_method(D_METHOD("set_reset_default"), &TriggerCamera::set_reset_default);
    ClassDB::bind_method(D_METHOD("get_reset_default"), &TriggerCamera::get_reset_default);

    ClassDB::bind_method(D_METHOD("set_rotation_camera_change"), &TriggerCamera::set_rotation_camera_change);
    ClassDB::bind_method(D_METHOD("get_rotation_camera_change"), &TriggerCamera::get_rotation_camera_change);
    
    ClassDB::bind_method(D_METHOD("set_rotation_camera"), &TriggerCamera::set_rotation_camera);
    ClassDB::bind_method(D_METHOD("get_rotation_camera"), &TriggerCamera::get_rotation_camera);

    ClassDB::bind_method(D_METHOD("set_outside_delta_change"), &TriggerCamera::set_outside_delta_change);
    ClassDB::bind_method(D_METHOD("get_outside_delta_change"), &TriggerCamera::get_outside_delta_change);

    ClassDB::bind_method(D_METHOD("set_outside_delta"), &TriggerCamera::set_outside_delta);
    ClassDB::bind_method(D_METHOD("get_outside_delta"), &TriggerCamera::get_outside_delta);
    
    ClassDB::bind_method(D_METHOD("set_target_path_change"), &TriggerCamera::set_target_path_change);
    ClassDB::bind_method(D_METHOD("get_target_path_change"), &TriggerCamera::get_target_path_change);

    ClassDB::bind_method(D_METHOD("set_target_path"), &TriggerCamera::set_target_path);
    ClassDB::bind_method(D_METHOD("get_target_path"), &TriggerCamera::get_target_path);

    ClassDB::bind_method(D_METHOD("set_speed_scale_change"), &TriggerCamera::set_speed_scale_change);
    ClassDB::bind_method(D_METHOD("get_speed_scale_change"), &TriggerCamera::get_speed_scale_change);
    
    ClassDB::bind_method(D_METHOD("set_speed_scale"), &TriggerCamera::set_speed_scale);
    ClassDB::bind_method(D_METHOD("get_speed_scale"), &TriggerCamera::get_speed_scale);
    
    ClassDB::bind_method(D_METHOD("set_inside_offset_change"), &TriggerCamera::set_inside_offset_change);
    ClassDB::bind_method(D_METHOD("get_inside_offset_change"), &TriggerCamera::get_inside_offset_change);
    
    ClassDB::bind_method(D_METHOD("set_inside_offset"), &TriggerCamera::set_inside_offset);
    ClassDB::bind_method(D_METHOD("get_inside_offset"), &TriggerCamera::get_inside_offset);
    
    ClassDB::bind_method(D_METHOD("set_offset_delta_change"), &TriggerCamera::set_offset_delta_change);
    ClassDB::bind_method(D_METHOD("get_offset_delta_change"), &TriggerCamera::get_offset_delta_change);

    ClassDB::bind_method(D_METHOD("set_offset_delta"), &TriggerCamera::set_offset_delta);
    ClassDB::bind_method(D_METHOD("get_offset_delta"), &TriggerCamera::get_offset_delta);

    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "ResetDefault"), "set_reset_default", "get_reset_default");

    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "OutsideDeltaChange"), "set_outside_delta_change", "get_outside_delta_change");
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::VECTOR3, "OutsideDelta"), "set_outside_delta", "get_outside_delta");

    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "RotationCameraChange"), "set_rotation_camera_change", "get_rotation_camera_change");
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::VECTOR3, "RotationCamera"), "set_rotation_camera", "get_rotation_camera");
    
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "TargetPathChange"), "set_target_path_change", "get_target_path_change");
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::NODE_PATH, "TargetPath"), "set_target_path", "get_target_path");

    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "SpeedScaleChange"), "set_speed_scale_change", "get_speed_scale_change");
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::FLOAT, "SpeedScale"), "set_speed_scale", "get_speed_scale");

    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "InsideOffsetChange"), "set_inside_offset_change", "get_inside_offset_change");
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::FLOAT, "InsideOffset"), "set_inside_offset", "get_inside_offset");

    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::BOOL, "OffsetDeltaChange"), "set_offset_delta_change", "get_offset_delta_change");
    ClassDB::add_property("TriggerCamera", PropertyInfo(Variant::FLOAT, "OffsetDelta"), "set_offset_delta", "get_offset_delta");

}

void godot::TriggerCamera::set_target(ECamera *camera)
{
    if(!target_path_change){
        return;
    }
    if(target_path == NodePath()){
        UtilityFunctions::print("TriggerCamera: TargetPath is null");
        return;
    }
    Node3D *node = get_node<Node3D>(target_path);
    if(!node){
        UtilityFunctions::print("TriggerCamera: Target is null");
        return;
    }

    camera->set_target(node);

}

void godot::TriggerCamera::set_default(ECamera *camera)
{
    camera->set_default_inside_offset(camera->get_inside_offset());
    camera->set_default_offset_delta(camera->get_offset_delta());
    camera->set_default_outside_delta(camera->get_outside_delta());
    camera->set_default_rotation(camera->get_global_rotation());
    camera->set_default_speed_scale(camera->get_speed_scale());
    //camera->set_default_target(camera->get_targ);
}

bool godot::TriggerCamera::_activate()
{
    if(!EternityData::get_singleton()){
        UtilityFunctions::print("TriggerCamera: EternityData is null");
        return false;
    }

    ECamera *camera = EternityData::get_singleton()->get_camera();
    if(!camera){
        UtilityFunctions::print("TriggerCamera: Camera is null");
        return false;
    }


    if(reset_default)
        set_default(camera);
    
    set_target(camera);

    if(this->outside_delta_change){
        camera->set_outside_delta(outside_delta);
    }
    if(this->speed_scale_change){
        camera->set_speed_scale(speed_scale);
    }
    if(this->inside_offset_change){
        camera->set_inside_offset(inside_offset);
    }
    if(this->offset_delta_change){
        camera->set_offset_delta(offset_delta);
    }
    if(this->rotation_camera_change){
        camera->set_target_rotation(rotation_camera);
    }

    return true;
}

void godot::TriggerCamera::set_reset_default(bool p_reset_default)
{
    this->reset_default = p_reset_default;
}

bool godot::TriggerCamera::get_reset_default()
{
    return this->reset_default;
}

void godot::TriggerCamera::set_target_path_change(bool p_target_path_change)
{
    this->target_path_change = p_target_path_change;
}

bool godot::TriggerCamera::get_target_path_change()
{
    return this->target_path_change;
}

void godot::TriggerCamera::set_target_path(NodePath p_target_path)
{
    this->target_path = p_target_path;
}

godot::NodePath godot::TriggerCamera::get_target_path()
{
    return this->target_path;
}

void godot::TriggerCamera::set_outside_delta_change(bool p_outside_delta_change)
{
    this->outside_delta_change = p_outside_delta_change;
}

bool godot::TriggerCamera::get_outside_delta_change()
{
    return this->outside_delta_change;
}

void godot::TriggerCamera::set_outside_delta(Vector3 p_outside_delta)
{
    this->outside_delta = p_outside_delta;
}

godot::Vector3 godot::TriggerCamera::get_outside_delta()
{
    return this->outside_delta;
}

void godot::TriggerCamera::set_speed_scale_change(bool p_speed_scale_change)
{
    this->speed_scale_change = p_speed_scale_change;
}

bool godot::TriggerCamera::get_speed_scale_change()
{
    return this->speed_scale_change;
}

void godot::TriggerCamera::set_speed_scale(float p_speed_scale)
{
    this->speed_scale = p_speed_scale;
}

float godot::TriggerCamera::get_speed_scale()
{
    return this->speed_scale;
}

void godot::TriggerCamera::set_inside_offset_change(bool p_inside_offset_change)
{
    this->inside_offset_change = p_inside_offset_change;
}

bool godot::TriggerCamera::get_inside_offset_change()
{
    return this->inside_offset_change;
}

void godot::TriggerCamera::set_inside_offset(float p_inside_offset)
{
    this->inside_offset = p_inside_offset;
}

float godot::TriggerCamera::get_inside_offset()
{
    return this->inside_offset;
}

void godot::TriggerCamera::set_offset_delta_change(bool p_offset_delta_change)
{
    this->offset_delta_change = p_offset_delta_change;
}

bool godot::TriggerCamera::get_offset_delta_change()
{
    return this->offset_delta_change;
}

void godot::TriggerCamera::set_offset_delta(float p_offset_delta)
{
    this->offset_delta = p_offset_delta;
}

float godot::TriggerCamera::get_offset_delta()
{
    return this->offset_delta;
}

void godot::TriggerCamera::set_rotation_camera_change(bool p_rotation_camera_change)
{
    this->rotation_camera_change = p_rotation_camera_change;
}

bool godot::TriggerCamera::get_rotation_camera_change()
{
    return this->rotation_camera_change;
}

void godot::TriggerCamera::set_rotation_camera(Vector3 p_rotation_camera)
{
    this->rotation_camera = p_rotation_camera;
}

godot::Vector3 godot::TriggerCamera::get_rotation_camera()
{
    return this->rotation_camera;
}

godot::TriggerCamera::TriggerCamera()
{
}

godot::TriggerCamera::~TriggerCamera()
{
}
