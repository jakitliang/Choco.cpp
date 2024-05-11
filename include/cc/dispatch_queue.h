//
// Created by Jakit on 2024/5/11.
//

#ifndef CHOCO_CPP_DISPATCH_QUEUE_H
#define CHOCO_CPP_DISPATCH_QUEUE_H

#include "cc/types.h"
#include <functional>

namespace CC {
    struct DispatchQueue {
        using Block = std::function<void ()>;

        static UInt64 Make();

        static void Destroy(UInt64 id);

        // Main thread
        static void Dispatch(const Block & block);

        // Main thread
        static void Dispatch(Block && block);

        static void Dispatch(UInt64 id, const Block & block);

        static void Dispatch(UInt64 id, Block && block);

        // Main thread
        static void Process();

        static void Process(UInt64 id);

        static UInt64 GetID();
    };
}

#endif //CHOCO_CPP_DISPATCH_QUEUE_H
