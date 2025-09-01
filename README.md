# Multithreaded Asset Pipeline Demo

A C++ console application demonstrating a core game engine technique: **asynchronous asset loading** using a producer-consumer pattern. The main game thread runs at a consistent 60 FPS while a background worker thread loads assets without causing stalls.

## 📁 Project Overview

This demo simulates a critical problem in game engine programming: loading large assets (textures, models, sounds) can take time and must not freeze the game. This is solved by offloading the loading work to a separate thread.

**Key Concept:** The **Loader Thread** (producer) loads assets and places them in a thread-safe queue. The **Game Thread** (consumer) checks the queue each frame and uses any newly loaded assets, all without blocking its main update/render loop.

## 🛠️ Technical Implementation

- **Language:** C++20
- **Libraries:** Standard Library (`<thread>`, `<mutex>`, `<condition_variable>`, `<queue>`)
- **Pattern:** Producer-Consumer with a Thread-Safe Queue
- **Synchronization:** `std::mutex` and `std::condition_variable` for safe cross-thread communication.

## ✨ Features & Demonstrations

This project provides tangible evidence of the following skills relevant to a **Junior Engine Programmer** role:

| Feature | Implementation | Relevance to Engine Programming |
| :--- | :--- | :--- |
| **Multithreaded Programming** | Dedicated loader thread running concurrently with the main game thread. | Essential for keeping games responsive during streaming or loading screens. |
| **Thread Synchronization** | A thread-safe queue using a `mutex` and `condition_variable` to prevent data races. | Core to any engine system where data is shared between threads (e.g., rendering, physics, audio). |
| **Streaming** | Simulates the continuous loading and passing of assets, the foundation of open-world streaming systems. | Directly related to `streaming` core functionality in engines like **Northlight**. |
| **Performance-Critical Design** | The game thread uses a non-blocking check (`IsEmpty()`) to avoid stalling the main loop. | Shows focus on maintaining consistent frame rates—the #1 priority in engine code. |
| **Debugging & Logging** | Extensive console output clearly shows the state and hand-off between threads. | Demonstrates the practice of building and using debugging tools to visualize system behavior. |

## 🚀 Building and Running

### Prerequisites
- **Visual Studio 2022** with the "Desktop development with C++" workload installed.
- (Optional) GitHub Desktop or another Git client.

### Steps
1. Clone this repository or download the source files.
2. Open Visual Studio 2022.
3. Select **File > Open > CMake...** and navigate to the folder containing the `CMakeLists.txt` file.
4. Alternatively, create a new Empty C++ Project and add the `.h` and `.cpp` files.
5. Ensure **C++20** or later is enabled in the project settings (`/std:c++20` for MSVC).
6. Build the solution (Ctrl+Shift+B).
7. Run the executable (F5).

### Expected Output
The console will output messages from both the main game thread (`[GAME]`) and the loader thread (`[LOADER]`). You will see the game simulating a 60 FPS loop while assets are loaded in the background.
