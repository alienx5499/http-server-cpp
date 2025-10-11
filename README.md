<div align="center">

# 🚀 **Multi-threaded HTTP Server** 🚀

### _C++ HTTP Server with Socket Programming_

[![Build Passing](https://img.shields.io/badge/build-passing-success?style=flat-square)](https://github.com/alienx5499/http-server-cpp/actions)
[![C++](https://img.shields.io/badge/C++-17-blue?style=flat-square)](https://isocpp.org/)
[![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat-square)](https://github.com/alienx5499/http-server-cpp/blob/main/CONTRIBUTING.md)
[![License: MIT](https://custom-icon-badges.herokuapp.com/github/license/alienx5499/http-server-cpp?logo=law&logoColor=white)](https://github.com/alienx5499/http-server-cpp/blob/main/LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-brightgreen?style=flat-square)](https://github.com/alienx5499/http-server-cpp)
[![Views](https://visitor-badge.laobi.icu/badge?page_id=alienx5499.http-server-cpp)](https://visitor-badge.laobi.icu/badge?page_id=alienx5499.http-server-cpp)
[![⭐ GitHub stars](https://img.shields.io/github/stars/alienx5499/http-server-cpp?style=social)](https://github.com/alienx5499/http-server-cpp/stargazers)
[![🍴 GitHub forks](https://img.shields.io/github/forks/alienx5499/http-server-cpp?style=social)](https://github.com/alienx5499/http-server-cpp/network)
[![Commits](https://badgen.net/github/commits/alienx5499/http-server-cpp)](https://github.com/alienx5499/http-server-cpp/commits/main)
[![🐛 GitHub issues](https://img.shields.io/github/issues/alienx5499/http-server-cpp)](https://github.com/alienx5499/http-server-cpp/issues)
[![📂 GitHub pull requests](https://img.shields.io/github/issues-pr/alienx5499/http-server-cpp)](https://github.com/alienx5499/http-server-cpp/pulls)
[![💾 GitHub code size](https://img.shields.io/github/languages/code-size/alienx5499/http-server-cpp)](https://github.com/alienx5499/http-server-cpp)

</div>

---

## 🎯 **What is Multi-threaded HTTP Server?**

A high-performance HTTP server built from scratch using C++ and low-level socket programming. This server demonstrates advanced computer networking concepts including concurrent programming, HTTP protocol implementation, and network security principles.

### 🌟 **Key Features**

- **Multi-threaded Architecture**: Configurable thread pool for handling concurrent clients
- **HTTP/1.1 Compliance**: Full support for GET and POST requests with proper protocol handling
- **Binary File Support**: Serve HTML files and download binary files (images, text) with integrity
- **JSON Processing**: Handle POST requests with JSON data uploads
- **Security Features**: Path traversal protection and host header validation
- **Connection Management**: Keep-alive support with timeout handling and connection limits

> _"Built for Computer Networks course assignment demonstrating HTTP protocol implementation, multi-threading, and network security principles."_

<div align="center">

### 🚀 **Help Us Build Something Amazing Together!**

**Learning networking concepts? You're exactly who we built this for!** ✨
_Help other developers discover what you just experienced_ 💝

<a href="https://github.com/alienx5499/http-server-cpp">
  <img src="https://img.shields.io/badge/⭐%20Star%20this%20repo-Be%20part%20of%20our%20community!-yellow?style=for-the-badge&logo=github" alt="Star this repo" />
</a>

<a href="https://twitter.com/intent/tweet?text=🔥%20WOW!%20This%20C%2B%2B%20HTTP%20server%20made%20socket%20programming%20finally%20click%20for%20me!%20Multi-threaded%20architecture%20is%20a%20game-changer%20🧠✨%0AIf%20you're%20learning%20networking,%20prepping%20for%20system%20design,%20or%20just%20want%20to%20understand%20HTTP%20protocols%20better%20-%20you%20NEED%20this!%20%F0%9F%9A%80%0Ahttps://github.com/alienx5499/http-server-cpp%0A@alienx5499">
  <img src="https://img.shields.io/badge/🐦%20Share%20the%20love-Help%20a%20fellow%20developer!-1DA1F2?style=for-the-badge&logo=twitter" alt="Tweet about HTTP Server" />
</a>

<a href="https://github.com/alienx5499/http-server-cpp">
  <img src="https://img.shields.io/badge/🎮%20Experience%20the%20Magic-Try%20it%20NOW!-brightgreen?style=for-the-badge&logo=github" alt="Try HTTP Server" />
</a>

<a href="https://github.com/alienx5499/http-server-cpp/contributors">
  <img src="https://img.shields.io/badge/🌟%20Meet%20Our%20Heroes-View%20Contributors-purple?style=for-the-badge&logo=github" alt="View Contributors" />
</a>

**💭 "Every star motivates us to add more networking features and optimizations!" - The HTTP Server Team**

</div>

---

## 📚 **Table of Contents**

1. [✨ Features](#-features)
2. [🦾 Tech Stack](#-tech-stack)
3. [📂 Project Structure](#-project-structure)
4. [📸 Screenshots](#-screenshots)
5. [🚀 Quick Start](#-quick-start)
6. [👨‍🔧 Detailed Setup](#-detailed-setup)
7. [🛠️ Testing & Usage](#️-testing--usage)
8. [🎯 Target Audience](#-target-audience)
9. [🤝 Contributing](#-contributing)
10. [🌟 Awesome Contributors](#-awesome-contributors)
11. [📜 License](#-license)
12. [📬 Feedback & Suggestions](#-feedback--suggestions)

---

## ✨ **Features**

### 🎮 **Multi-threaded Architecture**

- Configurable thread pool for concurrent client handling
- Connection queue management when thread pool is saturated
- Proper synchronization with mutexes and condition variables
- Thread-safe resource management

### 📊 **HTTP Protocol Support**

- **GET Requests**: Serve HTML files and binary downloads
- **POST Requests**: Handle JSON data uploads
- **HTTP/1.1 Compliance**: Full protocol implementation
- **Method Validation**: Returns 405 for unsupported methods

### 📈 **File Handling**

- **HTML Files**: Served with proper Content-Type headers
- **Binary Files**: PNG, JPEG, TXT files with download support
- **Content-Disposition**: Triggers browser downloads for binary files
- **File Integrity**: Binary mode reading preserves data integrity

### 🎨 **Security Features**

- **Path Traversal Protection**: Blocks malicious path access attempts
- **Host Header Validation**: Ensures requests match server configuration
- **Input Sanitization**: Validates and sanitizes all inputs
- **Security Logging**: Comprehensive violation tracking

---

## 🦾 **Tech Stack**

### 🌐 **Core Technologies**

- **Language**: C++17 with modern features
- **Networking**: POSIX sockets (TCP/IP)
- **Threading**: std::thread with mutex synchronization
- **HTTP**: Custom HTTP/1.1 protocol implementation
- **JSON**: Built-in JSON validation and processing
- **Build System**: Make with GCC/Clang support

### 🛠️ **Development Tools**

- **Build Tool**: Make
- **Compiler**: GCC/Clang with C++17 support
- **Code Quality**: Comprehensive error handling
- **Version Control**: Git
- **Testing**: Automated test suite

### 🔧 **System Requirements**

- POSIX-compatible operating system (Linux, macOS, Windows with WSL)
- C++17 compatible compiler
- No external dependencies required
- Standard C++ libraries only

---

## 📂 **Project Structure**

```
http-server-cpp/
├─ .gitignore                  # Git ignore configuration
├─ LICENSE                     # MIT license file
├─ README.md                   # Project documentation (this file)
├─ Makefile                    # Build configuration and targets
├─ aim.txt                     # Assignment requirements and specifications
└─ http-server-cpp/            # Main server implementation directory
   ├─ include/                 # Header files
   │  └─ server.hpp            # Main server class definition
   ├─ src/                     # Source code directory
   │  └─ server.cpp            # Server implementation
   ├─ resources/               # Static files and test resources
   │  ├─ index.html            # Home page
   │  ├─ about.html            # About page
   │  ├─ contact.html          # Contact page
   │  ├─ downloads_guide.txt   # Sample text file for testing
   │  ├─ clubs.txt             # Larger football-themed text file
   │  ├─ realmadrid.png        # Large PNG image (>1MB)
   │  ├─ ronaldo.png           # PNG image
   │  ├─ gerrard.jpeg          # JPEG image
   │  ├─ liverpool.jpeg        # JPEG image
   │  └─ uploads/              # Directory for POST uploads
   │     └─ .gitkeep           # Keep directory in git
   └─ build/                   # Build output directory (generated)
      └─ server                # Compiled executable
```

### 📁 **Key Directories and Files**:

- **`include/server.hpp`**: Complete server class definition with all method declarations
- **`src/server.cpp`**: Full server implementation with HTTP parsing, threading, and security
- **`resources/`**: Test files including HTML pages, binary files, and upload directory
- **`Makefile`**: Comprehensive build system with testing and deployment targets
- **`build/`**: Generated directory containing compiled executable and object files

---

## 📸 **Screenshots**

<div align="center">

### **Server Logs & Terminal Output**

<table>
<tr>
  <td><img src="https://github.com/user-attachments/assets/85b41973-4728-4f3b-a865-846f908dcff1" alt="Server Startup" width="1200px" loading="lazy"></td>
  <td><img src="https://github.com/user-attachments/assets/c7a631d4-6c10-4f51-8f35-2452dbe000d8" width="1200px" loading="lazy"></td>
</tr>
<tr>
  <td><b>Server Startup</b></td>
  <td><b>Request Processing</b></td>
</tr>
<tr>
  <td><img src="https://github.com/user-attachments/assets/cbdc3be6-724c-4bb8-84d1-844ec3015223" width="1200px" loading="lazy"></td>
  <td><img src="https://github.com/user-attachments/assets/e587d24e-5393-43b1-a081-948448161c84" width="1200px" loading="lazy"></td>
</tr>
<tr>
  <td><b>Binary File Download</b></td>
  <td><b>JSON Upload Response</b></td>
</tr>
</table>

</div>

---

## 🚀 **Quick Start**

1. **Clone the Repository**
   ```bash
   git clone https://github.com/alienx5499/http-server-cpp.git
   cd http-server-cpp
   ```

2. **Build the Server**
   ```bash
   make
   ```

3. **Run the Server**
   ```bash
   # Default: localhost:8080 with 10 threads
   make run
   
   # Or run manually
   ./build/server
   ```

4. **Test the Server**
   ```bash
   # Test HTML serving
   curl -H "Host: localhost:8080" http://localhost:8080/

   # Test binary download
   curl -H "Host: localhost:8080" -o realmadrid.png http://localhost:8080/realmadrid.png
   curl -H "Host: localhost:8080" -o ronaldo.png http://localhost:8080/ronaldo.png
   curl -H "Host: localhost:8080" -o gerrard.jpeg http://localhost:8080/gerrard.jpeg
   curl -H "Host: localhost:8080" -o liverpool.jpeg http://localhost:8080/liverpool.jpeg

   # Test text downloads
   curl -H "Host: localhost:8080" -o guide.txt http://localhost:8080/downloads_guide.txt
   curl -H "Host: localhost:8080" -o clubs.txt http://localhost:8080/clubs.txt

   # Test JSON upload
   curl -H "Host: localhost:8080" \
        -X POST \
        -H "Content-Type: application/json" \
        -d '{"club":"Real Madrid","opponent":"Juventus","player":"Cristiano Ronaldo","event":"bicycle_kick","minute":64,"competition":"UEFA Champions League","season":"2017-18","venue":"Allianz Stadium (Turin)","metadata":{"assist":"Dani Carvajal","xG":0.07}}' \
        http://localhost:8080/upload
   ```

---

## 🛠️ **Testing & Usage**

The HTTP server includes comprehensive testing capabilities and usage examples designed to verify all functionality, test security features, and demonstrate proper usage patterns. The server provides detailed logging and monitoring for development and debugging purposes.

### **🔐 Security Testing**

The server implements comprehensive security features that can be tested:

- **Path Traversal Protection**: Blocks malicious path access attempts
- **Host Header Validation**: Ensures requests match server configuration
- **Input Sanitization**: Validates and sanitizes all inputs
- **Security Logging**: Comprehensive violation tracking

### **⚡ Automated Testing**

#### **Prerequisites**

- C++17 compatible compiler
- Make build system
- curl for HTTP testing

#### **Test Commands**

1. **Build and Test**:

   ```bash
   make test
   ```

2. **Manual Testing**:

```bash
# Start server
./build/server 9000 127.0.0.1 5 &

# Test HTML serving
curl -H "Host: localhost:9000" http://localhost:9000/

# Test binary downloads (PNG/JPEG)
curl -H "Host: localhost:9000" -o realmadrid.png http://localhost:9000/realmadrid.png
curl -H "Host: localhost:9000" -o ronaldo.png http://localhost:9000/ronaldo.png
curl -H "Host: localhost:9000" -o gerrard.jpeg http://localhost:9000/gerrard.jpeg
curl -H "Host: localhost:9000" -o liverpool.jpeg http://localhost:9000/liverpool.jpeg

# Test text downloads
curl -H "Host: localhost:9000" -o downloads_guide.txt http://localhost:9000/downloads_guide.txt
curl -H "Host: localhost:9000" -o clubs.txt http://localhost:9000/clubs.txt

# Test JSON upload
curl -H "Host: localhost:9000" -X POST -H "Content-Type: application/json" -d '{"test": "data"}' http://localhost:9000/upload
```

### **🧰 Testing Features**

#### **📊 Performance Testing**

**Real-time performance monitoring with detailed metrics:**

- **Thread Pool Monitoring**

  - Active thread count tracking
  - Connection queue status
  - Thread utilization metrics
  - Performance bottleneck detection

- **Request Processing**

  - Request/response timing
  - Throughput measurement
  - Error rate tracking
  - Connection handling efficiency

- **Memory Usage**

  - Memory consumption monitoring
  - Resource leak detection
  - Buffer management analysis
  - Memory usage patterns

#### **📱 Security Testing**

**Comprehensive security validation:**

- **Path Traversal Tests**

  ```bash
  # These should return 403 Forbidden
  curl -H "Host: localhost:9000" http://localhost:9000/../etc/passwd
  curl -H "Host: localhost:9000" http://localhost:9000/../../config
  ```

- **Host Header Validation**

  ```bash
  # This should return 403 Forbidden
  curl -H "Host: evil.com:9000" http://localhost:9000/
  
  # This should return 400 Bad Request
  curl http://localhost:9000/  # Missing Host header
  ```

- **Input Validation**
  - JSON format validation
  - Content-Type checking
  - Request size limits
  - Method validation

#### **💻 Logging & Monitoring**

**Enhanced debugging capabilities:**

- **Comprehensive Logging**

  - Timestamped log entries
  - Thread ID tracking
  - Request/response details
  - Error stack traces

- **Real-time Monitoring**
  - Server status updates
  - Connection statistics
  - Performance metrics
  - Security violation alerts

### **🔍 Usage Examples**

#### **Basic Server Operations**

1. **Start Server with Custom Configuration**:

   ```bash
   # Custom port, host, and thread count
   ./build/server 9000 0.0.0.0 20
   ```

2. **Test Different File Types**:

   ```bash
   # HTML files (rendered in browser)
   curl -H "Host: localhost:9000" http://localhost:9000/about.html
   
   # Binary files (downloaded)
   curl -H "Host: localhost:9000" -o logo.png http://localhost:9000/logo.png
   
   # Text files (downloaded)
   curl -H "Host: localhost:9000" -o lorem.txt http://localhost:9000/lorem.txt
   ```

#### **Advanced Testing Scenarios**

1. **Concurrent Client Testing**

   ```bash
   # Test multiple simultaneous connections
   for i in {1..10}; do
     curl -H "Host: localhost:9000" http://localhost:9000/ &
   done
   wait
   ```

2. **JSON Upload Testing**

   ```bash
   # Test various JSON formats
   curl -H "Host: localhost:9000" -X POST -H "Content-Type: application/json" \
        -d '{"name": "Test", "data": [1,2,3]}' http://localhost:9000/upload
   ```

3. **Error Handling Tests**

   ```bash
   # Test 404 errors
   curl -H "Host: localhost:9000" http://localhost:9000/nonexistent.html
   
   # Test 405 errors
   curl -H "Host: localhost:9000" -X PUT http://localhost:9000/index.html
   
   # Test 415 errors
   curl -H "Host: localhost:9000" -X POST -H "Content-Type: text/plain" \
        -d "invalid data" http://localhost:9000/upload
   ```

### **⚙️ Make Targets**

#### **Available Commands**

```bash
make              # Build the server
make run          # Run on localhost:8080
make run-port     # Run on localhost:9000
make run-custom   # Run on 0.0.0.0:8080 with 20 threads
make test         # Run automated tests
make clean        # Clean build files
make help         # Show all available targets
```

### **🚨 Troubleshooting**

#### **Common Issues**

1. **Port Already in Use**

   ```bash
   # Check what's using the port
   lsof -i :8080
   
   # Kill existing processes
   pkill -f server
   
   # Use a different port
   ./build/server 9000
   ```

2. **Permission Denied**

   ```bash
   # Make sure the executable has proper permissions
   chmod +x build/server
   ```

3. **Build Errors**

   ```bash
   # Clean and rebuild
   make clean
   make
   ```

#### **Performance Considerations**

- **Thread Pool Size**: Adjust based on expected load
- **Connection Queue**: Monitor queue size during high load
- **Memory Usage**: Watch for memory leaks during long runs
- **File I/O**: Binary files require more memory for large files

### **🎪 Advanced Features**

#### **Custom Configuration**

```bash
# High-performance configuration
./build/server 8080 0.0.0.0 50

# Development configuration
./build/server 9000 127.0.0.1 5

# Production configuration
./build/server 80 0.0.0.0 100
```

#### **Monitoring & Logging**

- Real-time server statistics
- Request/response logging
- Thread pool status monitoring
- Security violation tracking
- Performance metrics collection

> **💡 Pro Tip**: Use the comprehensive logging to monitor server performance and identify optimization opportunities.

---

## 👨‍🔧 **Detailed Setup**

### **Prerequisites**

- **C++17 compatible compiler** (GCC 7+ or Clang 5+)
- **Make** build system
- **Git** for version control
- **POSIX-compatible OS** (Linux, macOS, Windows with WSL)

### **Installation Steps**

1. **Clone the Repository**

   ```bash
   git clone https://github.com/alienx5499/http-server-cpp.git
   ```

2. **Navigate to Project Directory**

   ```bash
   cd http-server-cpp
   ```

3. **Build the Server**

   ```bash
   make
   ```

4. **Run the Server**

   ```bash
   # Default configuration
   make run
   
   # Or run manually with custom settings
   ./build/server [port] [host] [max_threads]
   ```

5. **Test the Server**
   - Visit `http://localhost:8080` in your browser
   - Or use curl: `curl -H "Host: localhost:8080" http://localhost:8080/`

### 🔧 **Build Configuration**

The server uses a comprehensive Makefile with multiple build targets:

#### **Available Make Targets**

```bash
make              # Build the server executable
make run          # Run server with default settings (localhost:8080)
make run-port     # Run server on localhost:9000
make run-custom   # Run server on 0.0.0.0:8080 with 20 threads
make test         # Run automated test suite
make clean        # Clean build files
make help         # Show all available targets
```

#### **Custom Build Options**

```bash
# Build with debug symbols
make CXXFLAGS="-g -O0" 

# Build with specific compiler
make CXX=clang++

# Build with additional flags
make CXXFLAGS="-std=c++17 -Wall -Wextra -O2 -pthread -DDEBUG"
```

#### **System Requirements**

- **Linux**: GCC 7+ or Clang 5+
- **macOS**: Xcode Command Line Tools or Homebrew GCC
- **Windows**: WSL with Ubuntu/Debian or MinGW-w64
- **Memory**: Minimum 512MB RAM
- **Disk**: 50MB free space

---

## 🎯 **Target Audience**

### 👨‍🎓 **Computer Science Students**

- Learning HTTP protocol implementation
- Understanding socket programming concepts
- Multi-threading and concurrency principles
- Network security fundamentals

### 👨‍🏫 **Educators & Instructors**

- Teaching networking concepts
- Demonstrating HTTP server architecture
- Multi-threaded programming examples
- Security implementation patterns

### 👨‍💻 **System Developers**

- HTTP server implementation reference
- Socket programming best practices
- Thread pool management techniques
- Network security implementation

### 🔒 **Security Researchers**

- HTTP security vulnerability analysis
- Path traversal protection examples
- Host header validation techniques
- Input sanitization patterns

---

## 🤝 **Contributing**

We ❤️ open source! Your contributions make this project better.

### **How to Contribute**

1. **Fork the Repository**

   ```bash
   git clone https://github.com/your-username/http-server-cpp.git
   ```

2. **Create Feature Branch**

   ```bash
   git checkout -b feature/amazing-feature
   ```

3. **Make Changes**

   ```bash
   # Make your changes to the code
   # Test your changes
   make test
   ```

4. **Commit Changes**

   ```bash
   git commit -m "Add amazing feature"
   ```

5. **Push to Branch**

   ```bash
   git push origin feature/amazing-feature
   ```

6. **Open Pull Request**

### **Contribution Guidelines**

- Follow C++17 coding standards
- Add comprehensive error handling
- Update documentation and comments
- Test all new features thoroughly
- Keep commits clean and meaningful
- Ensure thread safety for concurrent code

---

## <img src="https://fonts.gstatic.com/s/e/notoemoji/latest/1f31f/512.webp" width="35" height="30"> **Awesome Contributors**

<div align="center">
	<h3>Thank you for contributing to our repository</h3><br>
	<p align="center">
		<a href="https://github.com/alienx5499/http-server-cpp/contributors">
			<img src="https://contrib.rocks/image?repo=alienx5499/http-server-cpp" width="720" height="380" />
		</a>
	</p>
</div>

---

## 📜 **License**

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">

### 📬 **Feedback & Suggestions**

_We value your input! Share your thoughts through [GitHub Issues](https://github.com/alienx5499/http-server-cpp/issues)._

💡 _Let's work together to enhance the understanding of HTTP protocols and network programming!_

</div>
