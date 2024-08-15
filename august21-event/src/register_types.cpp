#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "register_types.hpp"
#include "entity_player_base.hpp"
#include "player_body.hpp"
#include "entity_player.hpp"
#include "loading_screen.hpp"
#include "climbable_area.hpp"
#include "portal.hpp"
#include "intro.hpp"
#include "board_mesh.hpp"
#include "roof.hpp"
#include "end.hpp"
#include "server.hpp"
#include "client.hpp"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Client);
	GDREGISTER_CLASS(LoadingScreen);
	GDREGISTER_CLASS(PlayerBody);
	GDREGISTER_CLASS(EntityPlayerBase);
	GDREGISTER_CLASS(EntityPlayer);
	GDREGISTER_CLASS(ClimbableArea);
	GDREGISTER_CLASS(Portal);
	GDREGISTER_CLASS(Intro);
	GDREGISTER_CLASS(Roof);
	GDREGISTER_CLASS(End);
	GDREGISTER_CLASS(BoardMesh);
	GDREGISTER_CLASS(Server);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT august21_event_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
