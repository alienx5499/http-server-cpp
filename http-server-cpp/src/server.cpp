#include "../include/server.hpp"
#include <filesystem>
#include <algorithm>
#include <regex>

HTTPServer::HTTPServer(const std::string& host, int port, int max_threads) 
    : host(host), port(port), max_threads(max_threads), server_socket(-1), 
      running(false), active_connections(0), total_requests(0) {
}

HTTPServer::~HTTPServer() {
    stop();
}

std::string HTTPServer::get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void HTTPServer::log_message(const std::string& message) {
    std::cout << "[" << get_current_time() << "] " << message << std::endl;
}

void HTTPServer::log_request(const std::string& thread_id, const std::string& message) {
    std::cout << "[" << get_current_time() << "] [" << thread_id << "] " << message << std::endl;
}

std::string HTTPServer::generate_upload_filename() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    std::ostringstream oss;
    oss << "upload_" << std::put_time(&tm, "%Y%m%d_%H%M%S");
    
    // Add random ID
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    oss << "_" << dis(gen);
    
    return oss.str() + ".json";
}

bool HTTPServer::is_valid_json(const std::string& json_str) {
    // Simple JSON validation - check for basic structure
    if (json_str.empty()) {
        return false;
    }
    
    // Remove whitespace
    std::string trimmed = json_str;
    trimmed.erase(std::remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());
    
    // Check if it starts and ends with braces or brackets
    if ((trimmed.front() == '{' && trimmed.back() == '}') ||
        (trimmed.front() == '[' && trimmed.back() == ']')) {
        return true;
    }
    
    // Check for quoted strings (simple validation)
    if (trimmed.front() == '"' && trimmed.back() == '"') {
        return true;
    }
    
    // Check for numbers
    try {
        std::stod(trimmed);
        return true;
    } catch (...) {
        // Not a number
    }
    
    // Check for boolean values
    if (trimmed == "true" || trimmed == "false" || trimmed == "null") {
        return true;
    }
    
    return false;
}

HTTPServer::HTTPRequest HTTPServer::parse_request(const std::string& request_data) {
    HTTPRequest request;
    std::istringstream stream(request_data);
    std::string line;
    
    // Parse request line
    if (std::getline(stream, line)) {
        std::istringstream request_line(line);
        request_line >> request.method >> request.path >> request.version;
        
        // Remove trailing \r if present
        if (!request.version.empty() && request.version.back() == '\r') {
            request.version.pop_back();
        }
    }
    
    // Parse headers
    while (std::getline(stream, line) && line != "\r" && !line.empty()) {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 1);
            
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t\r"));
            key.erase(key.find_last_not_of(" \t\r") + 1);
            value.erase(0, value.find_first_not_of(" \t\r"));
            value.erase(value.find_last_not_of(" \t\r") + 1);
            
            // Convert to lowercase for case-insensitive comparison
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            request.headers[key] = value;
        }
    }
    
    // Parse body (if any)
    std::string body;
    while (std::getline(stream, line)) {
        body += line + "\n";
    }
    if (!body.empty()) {
        body.pop_back(); // Remove last newline
    }
    request.body = body;
    
    return request;
}

std::string HTTPServer::build_response(int status_code, const std::string& content_type, 
                                     const std::string& body, const std::string& filename) {
    std::ostringstream response;
    
    // Status line
    std::string status_text;
    switch (status_code) {
        case 200: status_text = "OK"; break;
        case 201: status_text = "Created"; break;
        case 400: status_text = "Bad Request"; break;
        case 403: status_text = "Forbidden"; break;
        case 404: status_text = "Not Found"; break;
        case 405: status_text = "Method Not Allowed"; break;
        case 415: status_text = "Unsupported Media Type"; break;
        case 500: status_text = "Internal Server Error"; break;
        case 503: status_text = "Service Unavailable"; break;
        default: status_text = "Unknown"; break;
    }
    
    response << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
    response << "Content-Type: " << content_type << "\r\n";
    response << "Content-Length: " << body.length() << "\r\n";
    response << "Date: " << get_current_time() << "\r\n";
    response << "Server: Multi-threaded HTTP Server\r\n";
    
    // Add Content-Disposition for binary files
    if (!filename.empty() && content_type == "application/octet-stream") {
        response << "Content-Disposition: attachment; filename=\"" << filename << "\"\r\n";
    }
    
    // Connection header
    response << "Connection: keep-alive\r\n";
    response << "Keep-Alive: timeout=30, max=100\r\n";
    response << "\r\n";
    response << body;
    
    return response.str();
}

std::string HTTPServer::get_content_type(const std::string& filepath) {
    std::string ext = get_file_extension(filepath);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    if (ext == "html" || ext == "htm") {
        return "text/html; charset=utf-8";
    } else if (ext == "txt") {
        return "application/octet-stream";
    } else if (ext == "png") {
        return "application/octet-stream";
    } else if (ext == "jpg" || ext == "jpeg") {
        return "application/octet-stream";
    } else {
        return "application/octet-stream";
    }
}

std::string HTTPServer::get_file_extension(const std::string& filepath) {
    size_t dot_pos = filepath.find_last_of('.');
    if (dot_pos != std::string::npos) {
        return filepath.substr(dot_pos + 1);
    }
    return "";
}

bool HTTPServer::validate_path(const std::string& path) {
    // Check for directory traversal attempts
    if (path.find("..") != std::string::npos || 
        path.find("./") != std::string::npos ||
        path.find("//") != std::string::npos ||
        path.find("\\") != std::string::npos) {
        return false;
    }
    
    // Ensure path starts with /
    if (path.empty() || path[0] != '/') {
        return false;
    }
    
    return true;
}

bool HTTPServer::validate_host_header(const std::map<std::string, std::string>& headers) {
    auto host_it = headers.find("host");
    if (host_it == headers.end()) {
        return false; // Missing Host header
    }
    
    std::string host_value = host_it->second;
    std::string expected_host = host + ":" + std::to_string(port);
    std::string expected_host_alt = host;
    std::string localhost_alt = "localhost:" + std::to_string(port);
    std::string localhost_alt2 = "localhost";
    
    return (host_value == expected_host || 
            host_value == expected_host_alt ||
            host_value == localhost_alt ||
            host_value == localhost_alt2 ||
            (host == "127.0.0.1" && host_value == "localhost:" + std::to_string(port)) ||
            (host == "127.0.0.1" && host_value == "localhost"));
}

std::string HTTPServer::read_file(const std::string& filepath, bool binary) {
    std::ifstream file;
    if (binary) {
        file.open(filepath, std::ios::binary);
    } else {
        file.open(filepath);
    }
    
    if (!file.is_open()) {
        return "";
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool HTTPServer::write_file(const std::string& filepath, const std::string& content) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    return true;
}

void HTTPServer::send_error_response(int client_socket, int status_code, const std::string& message) {
    std::string body = "{\"error\": \"" + message + "\"}";
    std::string response = build_response(status_code, "application/json", body);
    send(client_socket, response.c_str(), response.length(), 0);
}

void HTTPServer::handle_get_request(int client_socket, const HTTPRequest& request) {
    std::string thread_id = "Thread-" + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) % 1000);
    
    // Determine file path
    std::string filepath = request.path;
    if (filepath == "/") {
        filepath = "/index.html";
    }
    
    // Remove leading slash and add resources prefix
    if (filepath.length() > 1) {
        filepath = "http-server-cpp/resources" + filepath;
    } else {
        filepath = "http-server-cpp/resources/index.html";
    }
    
    log_request(thread_id, "Request: " + request.method + " " + request.path + " " + request.version);
    
    // Validate host header
    if (!validate_host_header(request.headers)) {
        log_request(thread_id, "Host validation failed");
        send_error_response(client_socket, 403, "Forbidden: Invalid Host header");
        return;
    }
    log_request(thread_id, "Host validation: " + request.headers.at("host") + " ✓");
    
    // Validate path
    if (!validate_path(request.path)) {
        log_request(thread_id, "Path validation failed: " + request.path);
        send_error_response(client_socket, 403, "Forbidden: Invalid path");
        return;
    }
    
    // Check if file exists
    if (!std::filesystem::exists(filepath)) {
        log_request(thread_id, "File not found: " + filepath);
        send_error_response(client_socket, 404, "Not Found");
        return;
    }
    
    // Read file
    std::string content;
    bool is_binary = false;
    std::string ext = get_file_extension(filepath);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "txt") {
        content = read_file(filepath, true);
        is_binary = true;
    } else {
        content = read_file(filepath, false);
    }
    
    if (content.empty()) {
        log_request(thread_id, "Error reading file: " + filepath);
        send_error_response(client_socket, 500, "Internal Server Error");
        return;
    }
    
    // Get filename for Content-Disposition
    std::string filename = std::filesystem::path(filepath).filename().string();
    
    // Build response
    std::string content_type = get_content_type(filepath);
    std::string response = build_response(200, content_type, content, filename);
    
    // Send response
    ssize_t bytes_sent = send(client_socket, response.c_str(), response.length(), 0);
    
    if (is_binary) {
        log_request(thread_id, "Sending binary file: " + filename + " (" + std::to_string(content.length()) + " bytes)");
    } else {
        log_request(thread_id, "Sending HTML file: " + filename + " (" + std::to_string(content.length()) + " bytes)");
    }
    
    log_request(thread_id, "Response: 200 OK (" + std::to_string(bytes_sent) + " bytes transferred)");
    log_request(thread_id, "Connection: keep-alive");
}

void HTTPServer::handle_post_request(int client_socket, const HTTPRequest& request) {
    std::string thread_id = "Thread-" + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) % 1000);
    
    log_request(thread_id, "Request: " + request.method + " " + request.path + " " + request.version);
    
    // Validate host header
    if (!validate_host_header(request.headers)) {
        log_request(thread_id, "Host validation failed");
        send_error_response(client_socket, 403, "Forbidden: Invalid Host header");
        return;
    }
    
    // Check Content-Type
    auto content_type_it = request.headers.find("content-type");
    if (content_type_it == request.headers.end() || 
        content_type_it->second.find("application/json") == std::string::npos) {
        log_request(thread_id, "Invalid Content-Type: " + 
                   (content_type_it != request.headers.end() ? content_type_it->second : "missing"));
        send_error_response(client_socket, 415, "Unsupported Media Type");
        return;
    }
    
    // Validate JSON (simple validation)
    if (!is_valid_json(request.body)) {
        log_request(thread_id, "Invalid JSON data");
        send_error_response(client_socket, 400, "Bad Request: Invalid JSON");
        return;
    }
    
    // Generate filename
    std::string filename = generate_upload_filename();
    std::string filepath = "http-server-cpp/resources/uploads/" + filename;
    
    // Write file
    if (!write_file(filepath, request.body)) {
        log_request(thread_id, "Error writing file: " + filepath);
        send_error_response(client_socket, 500, "Internal Server Error");
        return;
    }
    
    // Build success response
    std::string response_body = "{\n";
    response_body += "  \"status\": \"success\",\n";
    response_body += "  \"message\": \"File created successfully\",\n";
    response_body += "  \"filepath\": \"/uploads/" + filename + "\"\n";
    response_body += "}";
    
    std::string response = build_response(201, "application/json", response_body);
    
    send(client_socket, response.c_str(), response.length(), 0);
    
    log_request(thread_id, "File created: " + filepath);
    log_request(thread_id, "Response: 201 Created");
}

bool HTTPServer::should_keep_alive(const HTTPRequest& request) {
    auto connection_it = request.headers.find("connection");
    if (connection_it != request.headers.end()) {
        std::string connection_value = connection_it->second;
        std::transform(connection_value.begin(), connection_value.end(), connection_value.begin(), ::tolower);
        return connection_value == "keep-alive";
    }
    
    // Default behavior based on HTTP version
    return request.version == "HTTP/1.1";
}

void HTTPServer::handle_client(int client_socket) {
    std::string thread_id = "Thread-" + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) % 1000);
    
    char buffer[8192];
    int request_count = 0;
    const int MAX_REQUESTS_PER_CONNECTION = 100;
    
    while (running && request_count < MAX_REQUESTS_PER_CONNECTION) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytes_received <= 0) {
            break;
        }
        
        buffer[bytes_received] = '\0';
        std::string request_data(buffer);
        
        HTTPRequest request = parse_request(request_data);
        
        if (request.method == "GET") {
            handle_get_request(client_socket, request);
        } else if (request.method == "POST") {
            handle_post_request(client_socket, request);
        } else {
            log_request(thread_id, "Unsupported method: " + request.method);
            send_error_response(client_socket, 405, "Method Not Allowed");
        }
        
        total_requests++;
        request_count++;
        
        // Check if connection should be kept alive
        if (!should_keep_alive(request)) {
            break;
        }
    }
    
    close(client_socket);
    active_connections--;
    
    if (request_count >= MAX_REQUESTS_PER_CONNECTION) {
        log_request(thread_id, "Connection closed: reached max requests limit");
    } else {
        log_request(thread_id, "Connection closed");
    }
}

void HTTPServer::worker_thread() {
    std::string thread_id = "Thread-" + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) % 1000);
    
    while (running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [this] { return !connection_queue.empty() || !running; });
        
        if (!running) {
            break;
        }
        
        int client_socket = connection_queue.front();
        connection_queue.pop();
        lock.unlock();
        
        active_connections++;
        log_request(thread_id, "Connection from client assigned");
        
        handle_client(client_socket);
    }
}

bool HTTPServer::start() {
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        log_message("Error creating socket");
        return false;
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        log_message("Error setting socket options");
        close(server_socket);
        return false;
    }
    
    // Bind socket
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(host.c_str());
    address.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        log_message("Error binding socket");
        close(server_socket);
        return false;
    }
    
    // Listen for connections
    if (listen(server_socket, 50) < 0) {
        log_message("Error listening on socket");
        close(server_socket);
        return false;
    }
    
    running = true;
    
    // Start worker threads
    for (int i = 0; i < max_threads; i++) {
        thread_pool.emplace_back(&HTTPServer::worker_thread, this);
    }
    
    log_message("HTTP Server started on http://" + host + ":" + std::to_string(port));
    log_message("Thread pool size: " + std::to_string(max_threads));
    log_message("Serving files from 'resources' directory");
    log_message("Press Ctrl+C to stop the server");
    
    return true;
}

void HTTPServer::stop() {
    if (running) {
        running = false;
        queue_cv.notify_all();
        
        for (auto& thread : thread_pool) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        
        if (server_socket >= 0) {
            close(server_socket);
            server_socket = -1;
        }
        
        log_message("Server stopped");
    }
}

void HTTPServer::run() {
    if (!start()) {
        return;
    }
    
    while (running) {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);
        
        if (client_socket < 0) {
            if (running) {
                log_message("Error accepting connection");
            }
            continue;
        }
        
        // Check if thread pool is saturated
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            if (connection_queue.size() >= 50) {
                log_message("Warning: Thread pool saturated, rejecting connection");
                close(client_socket);
                continue;
            }
            
            connection_queue.push(client_socket);
        }
        
        queue_cv.notify_one();
        
        // Log thread pool status periodically
        static int log_counter = 0;
        if (++log_counter % 100 == 0) {
            std::lock_guard<std::mutex> lock(queue_mutex);
            log_message("Thread pool status: " + std::to_string(active_connections) + "/" + std::to_string(max_threads) + " active");
        }
    }
}

// Signal handler for graceful shutdown
std::unique_ptr<HTTPServer> g_server;

void signal_handler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        std::cout << "\nReceived signal " << signal << ", shutting down gracefully...\n";
        if (g_server) {
            g_server->stop();
        }
    }
}

int main(int argc, char* argv[]) {
    // Parse command line arguments
    std::string host = "127.0.0.1";
    int port = 8080;
    int max_threads = 10;
    
    if (argc >= 2) {
        port = std::atoi(argv[1]);
    }
    if (argc >= 3) {
        host = argv[2];
    }
    if (argc >= 4) {
        max_threads = std::atoi(argv[3]);
    }
    
    // Create server instance
    g_server = std::make_unique<HTTPServer>(host, port, max_threads);
    
    // Set up signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    // Create resources directory if it doesn't exist
    std::filesystem::create_directories("http-server-cpp/resources/uploads");
    
    // Run server
    g_server->run();
    
    return 0;
}
