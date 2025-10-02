#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <random>
#include <iomanip>

class HTTPServer {
private:
    std::string host;
    int port;
    int max_threads;
    int server_socket;
    std::atomic<bool> running;
    
    // Thread pool
    std::vector<std::thread> thread_pool;
    std::queue<int> connection_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    
    // Statistics
    std::atomic<int> active_connections;
    std::atomic<int> total_requests;
    
    // Helper methods
    void log_message(const std::string& message);
    void log_request(const std::string& thread_id, const std::string& message);
    std::string get_current_time();
    std::string generate_upload_filename();
    bool is_valid_json(const std::string& json_str);
    
    // HTTP parsing
    struct HTTPRequest {
        std::string method;
        std::string path;
        std::string version;
        std::map<std::string, std::string> headers;
        std::string body;
    };
    
    HTTPRequest parse_request(const std::string& request_data);
    std::string build_response(int status_code, const std::string& content_type, 
                              const std::string& body, const std::string& filename = "");
    std::string get_content_type(const std::string& filepath);
    
    // Security
    bool validate_path(const std::string& path);
    bool validate_host_header(const std::map<std::string, std::string>& headers);
    
    // File operations
    std::string read_file(const std::string& filepath, bool binary = false);
    bool write_file(const std::string& filepath, const std::string& content);
    std::string get_file_extension(const std::string& filepath);
    
    // Request handlers
    void handle_get_request(int client_socket, const HTTPRequest& request);
    void handle_post_request(int client_socket, const HTTPRequest& request);
    void send_error_response(int client_socket, int status_code, const std::string& message);
    
    // Connection management
    void handle_client(int client_socket);
    void worker_thread();
    bool should_keep_alive(const HTTPRequest& request);
    
public:
    HTTPServer(const std::string& host = "127.0.0.1", int port = 8080, int max_threads = 10);
    ~HTTPServer();
    
    bool start();
    void stop();
    void run();
};

#endif // SERVER_HPP
