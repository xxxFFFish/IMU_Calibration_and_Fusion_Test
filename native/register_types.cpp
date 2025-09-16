#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "manager/chief_manager.hpp"
#include "manager/data_manager.hpp"
#include "manager/text_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/level_manager.hpp"
#include "manager/gui_manager.hpp"

#include "main/main.hpp"

#include "level/main_level.hpp"

#include "gui/level/main_canvas.hpp"

using namespace godot;

void initialize_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

// Autoload node
	// Manager node
	GDREGISTER_RUNTIME_CLASS(framework::ChiefManager);
	GDREGISTER_RUNTIME_CLASS(framework::DataManager);
	GDREGISTER_RUNTIME_CLASS(framework::TextManager);
	GDREGISTER_RUNTIME_CLASS(framework::SignalManager);
	GDREGISTER_RUNTIME_CLASS(framework::LevelManager);
	GDREGISTER_RUNTIME_CLASS(framework::GuiManager);

// Scene node
	// Main node
	GDREGISTER_RUNTIME_CLASS(Main);

	// Level node
	GDREGISTER_RUNTIME_CLASS(MainLevel);

	// GUI canvas node
	GDREGISTER_RUNTIME_CLASS(MainCanvas);
}

void uninitialize_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_module);
	init_obj.register_terminator(uninitialize_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}