#pragma once
#include <godot_cpp/templates/list.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/web_socket_multiplayer_peer.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <dataproto_cpp/dataproto.hpp>

#include "client_data.hpp"
#include "entity_info.hpp"

using namespace godot;
using namespace dataproto;

class Server : public Node {
	GDCLASS(Server, Node)

private:
	Engine* _engine;
	Ref<WebSocketMultiplayerPeer> _socket_server;
	Ref<Thread> _console_thread;
	ResourceLoader* _resource_loader;
	double _game_time;
	int _tick_count;
	HashMap<String, Node*> _phase_scenes;
	HashMap<int, ClientData*> _clients;
	HashMap<int, EntityInfo*> _entities;
	Error register_phase_scene(String identifier, String path);
	int hash_string(String value);
	void write_player_info(int id, ClientData* client, BufWriter& buffer);
	int next_entity_id();
	/*const String MODEL_VARIANTS[8] = {
		"lightblue",
		"navy",
		"green",
		"purple",
		"grey",
		"brown",
		"orangered",
		"gold"
	};*/

protected:
	static void _bind_methods();

public:
	Server();
	~Server();

	void _ready() override;
	void _physics_process(double delta) override;
	void _on_peer_connected(int id);
	void _on_peer_disconnected(int id);
	void run_console_loop();
	EntityInfo* register_entity(Node* entity, String parent_scene);
	EntityInfo* create_entity(String node_path, String parent_scene);
	void repl_set_phase(string name);
	void set_phase(String name);
	void update_entity(int id, string property, string value);
	void delete_entity(int id);
	void list_players();
	void kill_player(int id);
	void kick_player(int id);
	void tp_player(string scene, int x, int y, int z);
	void announce(string message);
	void send_to_all(const BufWriter& packet);
	void send_to_all(const char* data, size_t size);
	void send_to_others(int exclude_id, const BufWriter& packet);
	void send_to_others(int exclude_id, const char* data, size_t size);
	void send(int id, const BufWriter& packet);
	void send(int id, const char* data, size_t size);
};
