#include "customer_behaivor.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "variants/const/customer_params.hpp"

void godot::CustomerBehaivor::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("update_texture"), &CustomerBehaivor::update_texture);

}

void godot::CustomerBehaivor::update_texture()
{
    ModelEntity *model = get_entity();
    if(!model){
        UtilityFunctions::print("CustomerBehaivor: model is null");
        return;
    }

    Entity *entity = model->get_entity();
    if(!entity){
        UtilityFunctions::print("CustomerBehaivor: entity is null");
        return;
    }

    EntityData *data = entity->get_data();
    if(!data){
        UtilityFunctions::print("CustomerBehaivor: data is null");
        return;
    }

    if(!data->has_string(CustomerParams::sprite_id())){
        UtilityFunctions::print("CustomerBehaivor: data not have: " + CustomerParams::sprite_id());
        return;
    }

    String anim = data->get_string(CustomerParams::sprite_id());
    get_entity()->set_animation(anim);

    UtilityFunctions::print("CustomerBehaivor: successfull change");
}

void godot::CustomerBehaivor::_set_entity(ModelEntity *p_entity)
{
    if(p_entity != nullptr && p_entity->get_entity() != nullptr)
        p_entity->get_entity()->connect("on_buffs_change", Callable(this, "update_texture"));
    else
        UtilityFunctions::print("HeroBehaivor: entity in mentity is null");

    update_texture();
}

void godot::CustomerBehaivor::_int_process()
{
}

godot::CustomerBehaivor::CustomerBehaivor()
{
}

godot::CustomerBehaivor::~CustomerBehaivor()
{
}
