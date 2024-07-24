#pragma once
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/web_socket_peer.hpp>

#include "network_manager.hpp"

using namespace godot;

class LoadingScreen : public Node3D {
	GDCLASS(LoadingScreen, Node3D);

protected:
	OS *_os;
	Engine *_engine;
	DisplayServer *_display_server;
	NetworkManager* _network_manager;
	Label* _players_label;
	static void _bind_methods();

public:
	LoadingScreen();
	~LoadingScreen();
	void _ready() override;
	void _process(double delta) override;
};
