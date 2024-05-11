//
// Created by Jakit on 2024/5/11.
//

#include "cc/dispatch_queue.h"
#include "cc/zone.h"
#include <thread>
#include <queue>
#include <mutex>
#include <unordered_map>

const auto Hash = std::hash<std::thread::id>();
const auto MainID = Hash(std::this_thread::get_id());
static std::mutex QueueLock;

struct DispatchQueueContext {
    using ContextsType = std::unordered_map<CC::UInt64, DispatchQueueContext>;

    std::mutex Lock;
    std::queue<CC::DispatchQueue::Block> Queue;

    DispatchQueueContext() = default;

    DispatchQueueContext(const DispatchQueueContext &dispatchQueueContext)
            : Queue(dispatchQueueContext.Queue) {}

    DispatchQueueContext(DispatchQueueContext &&dispatchQueueContext) noexcept
            : Queue(std::move(dispatchQueueContext.Queue)) {}

    void Dispatch(const CC::DispatchQueue::Block &block) {
        std::lock_guard<std::mutex> lockGuard(Lock);
        Queue.push(block);
    }

    void Dispatch(CC::DispatchQueue::Block &&block) {
        std::lock_guard<std::mutex> lockGuard(Lock);
        Queue.push(static_cast<CC::DispatchQueue::Block &&>(block));
    }

    void Process() {
        std::lock_guard<std::mutex> lockGuard(Lock);

        while (!Queue.empty()) {
            Queue.front()();
            Queue.pop();
        }
    }

    DispatchQueueContext &operator=(const DispatchQueueContext &context) {
        Queue = context.Queue;

        return *this;
    }

    DispatchQueueContext &operator=(DispatchQueueContext &&context) noexcept {
        Queue = std::move(context.Queue);

        return *this;
    }

    static ContextsType &GlobalQueues() {
        static ContextsType queues{{MainID, {}}};

        return queues;
    };

    static DispatchQueueContext *GetQueue(CC::UInt64 id) {
        std::lock_guard<std::mutex> lockGuard(QueueLock);
        auto &globalQueues = GlobalQueues();
        auto queue = globalQueues.find(id);

        if (queue == globalQueues.end()) return nullptr;

        return &queue->second;
    }

    static void SetQueue(CC::UInt64 id, bool create = true) {
        std::lock_guard<std::mutex> lockGuard(QueueLock);
        auto &globalQueues = GlobalQueues();
        auto queue = globalQueues.find(id);

        if (create) {
            if (queue == globalQueues.end()) globalQueues[id] = {};
            return;
        }

        if (queue == globalQueues.end()) return;

        if (id == MainID) queue->second.Queue = {};
        else globalQueues.erase(id);
    }
};

void CC::DispatchQueue::Dispatch(const CC::DispatchQueue::Block &block) {
    DispatchQueueContext::GetQueue(MainID)->Dispatch(block);
}

void CC::DispatchQueue::Dispatch(CC::DispatchQueue::Block &&block) {
    DispatchQueueContext::GetQueue(MainID)->Dispatch(
            static_cast<CC::DispatchQueue::Block &&>(block));
}

void CC::DispatchQueue::Dispatch(UInt64 id, const CC::DispatchQueue::Block &block) {
    auto context = DispatchQueueContext::GetQueue(id);

    if (context) context->Dispatch(block);
}

void CC::DispatchQueue::Dispatch(UInt64 id, CC::DispatchQueue::Block &&block) {
    auto context = DispatchQueueContext::GetQueue(id);

    if (context) context->Dispatch(static_cast<CC::DispatchQueue::Block &&>(block));
}

void CC::DispatchQueue::Process() {
    DispatchQueueContext::GetQueue(MainID)->Process();
}

void CC::DispatchQueue::Process(UInt64 id) {
    auto context = DispatchQueueContext::GetQueue(id);

    if (context) context->Process();
}

CC::UInt64 CC::DispatchQueue::Make() {
    auto id = GetID();

    DispatchQueueContext::SetQueue(id);

    return id;
}

void CC::DispatchQueue::Destroy(CC::UInt64 id) {
    DispatchQueueContext::SetQueue(id, false);
}

CC::UInt64 CC::DispatchQueue::GetID() {
    return Hash(std::this_thread::get_id());
}
