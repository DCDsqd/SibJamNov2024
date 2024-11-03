#include "hero_input.h"
#include "godot_cpp/variant/utility_functions.hpp"


void godot::HeroInput::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("add_trigger"), &HeroInput::add_trigger);

}

void godot::HeroInput::move_carrera(int to)
{
    int new_carrera = carrera + to;
    int size = triggers.size();

    new_carrera = (new_carrera % size + size) % size;

    carrera = new_carrera;
}

void godot::HeroInput::set_camera()
{
    GameController *controller = EternityData::get_singleton()->get_controller();
    if(controller == nullptr){
        UtilityFunctions::print("HeroInput: controller is null");
        return;
    }

    String name = triggers[carrera];

    Trigger3D *trigger = controller->get_trigger(name);
    if(!trigger){
        UtilityFunctions::print("HeroInput: trigger is null");
        return;
    }

    //UtilityFunctions::print("HeroInput: " + name);
    trigger->activate();

}

godot::Dictionary godot::HeroInput::get_mouse_collision()
{
    ECamera *camera = EternityData::get_singleton()->get_camera();
    if(!camera){
        UtilityFunctions::print("HeroInput: camera is null");
        return Dictionary();
    }
    
    Vector2 mouse = camera->get_viewport()->get_mouse_position();
    PhysicsDirectSpaceState3D *space = camera->get_world_3d().ptr()->get_direct_space_state();
    Vector3 start = camera->project_ray_origin(mouse);
    Vector3 end = camera->project_position(mouse, interact_distance);

    PhysicsRayQueryParameters3D *params = new PhysicsRayQueryParameters3D();
    params->set_from(start);
    params->set_to(end);
    params->set_collision_mask(4);

    Dictionary dict = space->intersect_ray(params);
    //UtilityFunctions::print(dict);
    return dict;
}

void godot::HeroInput::_int_process()
{
    move();
    interact();
}

void godot::HeroInput::_on_death()
{

}

void godot::HeroInput::_set_entity()
{
}

void godot::HeroInput::add_trigger(String name)
{
    triggers.append(name);
}

void godot::HeroInput::move()
{
    if(input->is_action_just_released("e_left")){
        move_carrera(-1);
        set_camera();
    }

    if(input->is_action_just_released("e_right")){
        move_carrera(1);
        set_camera();
    }
}

void godot::HeroInput::interact()
{
    if(input->is_action_just_released("e_interact")){
        if(get_entity() == nullptr){
            UtilityFunctions::print("HeroInput: entity is null");
            return;
        }

        if(get_entity()->get_entity() == nullptr){
            UtilityFunctions::print("HeroInput: entity in entity is null");
            return;
        }
        

        Dictionary dict = get_mouse_collision();

        Array dict_keys = dict.keys();
        for(int i = 0; i < dict_keys.size(); ++i){
            Node3D *node =  Object::cast_to<Node3D>(dict.get(dict_keys[i], nullptr));

            if(!node){
                continue;
            }

            ModelEntity *entity = Object::cast_to<ModelEntity>(node);
            if(!entity){
                continue;
            }

            if(entity->on_interact(get_entity()->get_entity()))
                return;
        }
        
    }
}

godot::HeroInput::HeroInput()
{
    this->input = Input::get_singleton();
}

godot::HeroInput::~HeroInput()
{
}
