#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "Asset.h"
#include "AssetQueue.h"

// Function for the loader thread (Producer)
void LoaderThread(AssetQueue& queue, const std::vector<Asset>& assetsToLoad) {
    std::cout << "[LOADER] Thread started. Beginning to load assets...\n";
    for (const auto& asset : assetsToLoad) {
        std::cout << "[LOADER] Loading started for: " << asset.name << "\n";

        Asset newAsset = asset; // Simulate 'fetching' asset data
        newAsset.Load();        // This is the blocking, time-consuming part

        std::cout << "[LOADER] Sending to game: " << newAsset.name << "\n";
        queue.Push(std::move(newAsset)); // Send the loaded asset to the game thread
    }
    std::cout << "[LOADER] Thread finished. All assets loaded.\n";
}

// Function for the game thread (Main thread/Consumer)
void GameThread(AssetQueue& queue) {
    std::cout << "[GAME] Main thread running. Waiting for assets...\n\n";

    // Simple game loop
    int frames = 0;
    while (frames < 600) { // Run for 600 simulated frames (~10 secs)

        // --- Simulate other game work (physics, input, etc.) ---
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
        frames++;
        // -------------------------------------------------------

        // NON-BLOCKING CHECK: Try to get a new asset without waiting
        if (!queue.IsEmpty()) {
            Asset loadedAsset = queue.Pop(); // This is now safe and won't block for long
            loadedAsset.Use();
        }

        // Simple UI update every 60 frames
        if (frames % 60 == 0) {
            std::cout << "[GAME] Frame: " << frames << " | FPS: 60 (simulated) | Assets in queue: " << (queue.IsEmpty() ? "0" : ">0") << "\n";
        }
    }
}

int main() {
    std::cout << "--- Multithreaded Asset Pipeline Demo ---\n";
    std::cout << "Simulating a game loop running at 60 FPS.\n";
    std::cout << "Asset loading (100ms) happens without blocking the game.\n\n";

    // Create our thread-safe queue
    AssetQueue assetQueue;

    // Create a list of assets to simulate loading
    std::vector<Asset> assets = {
        Asset("PlayerTexture", 1),
        Asset("EnemyMesh", 2),
        Asset("Environment", 3),
        Asset("WeaponSound", 4),
        Asset("UIFont", 5)
    };

    // Launch the loader thread, passing the queue and assets by reference
    std::thread loader(LoaderThread, std::ref(assetQueue), std::ref(assets));

    // Run the game loop on the main thread
    GameThread(assetQueue);

    // Wait for the loader thread to finish its work
    loader.join();

    std::cout << "\n--- Demo Complete ---\n";
    std::cout << "The game loop continued to run at 60 FPS while assets were loading.\n";

    return 0;
}