#pragma once
#include "dataproto_cpp/dataproto.hpp"
#include <godot_cpp/templates/list.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/web_socket_multiplayer_peer.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/templates/hash_map.hpp>

using namespace godot;
using namespace std;
using namespace dataproto;

class Server : public Node {
	GDCLASS(Server, Node)

private:
	OS *_os;
	Engine *_engine;
	DisplayServer *_display_server;
	Ref<WebSocketMultiplayerPeer> _socket_server;
	Ref<Thread> _console_thread;
	double _game_time;
	HashMap<int, Ref<WebSocketPeer>> _clients;
	List<Node*> _entities;

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
	void set_phase(string name);
	void create_entity(string type);
	void delete_entity(int id);
	void update_entity(int id, string property, string value);
	void list_players();
	void kill_player(int id);
	void kick_player(int id);
	void tp_player(string scene, int x, int y, int z);
	void send_to_all(BufWriter* packet);
	void send_to_all(const char* data, size_t size);
	void send(int id, BufWriter* packet);
	void send(int id, const char* data, size_t size);
};
