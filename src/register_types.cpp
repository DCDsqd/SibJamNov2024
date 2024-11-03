#include "register_types.h"

#include "test_dir/gdexample.h"

#include "entity/builder/simple_entity_builder.h"
#include "entity/hero/hero_input.h"
#include "entity/pc/pc_interaction.h"
#include "entity/customer/customer_interactor.h"
#include "entity/arc_dialogue/arc_interactor.h"
#include "entity/order/order_interactor.h"
#include "entity/order/order_container.h"
#include "entity/builder/order_builder.h"
#include "entity/hero/container_entity_data.h"
//#include "entity/order/order_container.h"

#include "variants/dialogues/arc_dialogue.h"
#include "hud/arc_view_model.h"
#include "hud/order_hud.h"
//#include "hud/arc_hud_dialogue.h"

#include "triggers/trigger_camera.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	//ClassDB::register_class<GDExample>();

	ClassDB::register_class<SimpleEntityBuilder>();
	ClassDB::register_class<HeroInput>();
	ClassDB::register_class<OrderContainer>();
	ClassDB::register_class<CustomerInteractor>();
	ClassDB::register_class<ArcInteractor>();
	ClassDB::register_class<PcInteractor>();

	ClassDB::register_class<ContainerEntityData>();
	ClassDB::register_class<OrderInteractor>();
	ClassDB::register_class<OrderHud>();
	ClassDB::register_class<OrderBuilder>();

	ClassDB::register_class<ArcDialogue>();
	ClassDB::register_class<ArcViewModel>();
	//ClassDB::register_class<ArcHudDialogue>();

	ClassDB::register_class<TriggerCamera>();
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_example_module);
	init_obj.register_terminator(uninitialize_example_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}