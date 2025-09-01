#pragma once
#include <string>
#include <iostream>

// Simulates a game asset (e.g., Texture, Mesh)
struct Asset {
    std::string name;
    int id;

    Asset(const std::string& assetName, int assetId)
        : name(assetName), id(assetId) {
    }

    // Simulate a time-consuming loading process
    void Load() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate 100ms load time
        std::cout << "[LOADER] Loaded: " << name << " (ID: " << id << ")\n";
    }

    // Simulate using the asset in the game
    void Use() {
        std::cout << "[GAME] Using asset: " << name << "\n";
    }
};