#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Asset.h"

// A thread-safe queue for passing assets between threads
class AssetQueue {
private:
    std::queue<Asset> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condVar;

public:
    void Push(Asset&& asset) {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.push(std::move(asset));
        }
        m_condVar.notify_one(); // Notify the waiting game thread
    }

    Asset Pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        // Wait until there is an asset in the queue
        m_condVar.wait(lock, [this]() { return !m_queue.empty(); });

        Asset asset = std::move(m_queue.front());
        m_queue.pop();
        return asset;
    }

    // Non-blocking check for UI updates
    bool IsEmpty() {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
};