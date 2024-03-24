//
// Created by Jakit on 2024/3/11.
//

#ifndef CC_STREAM_H
#define CC_STREAM_H

#include "types.h"

namespace CC {
    template<typename T>
    struct IStream {
        virtual Size Write();
        virtual Size Read();
    };

    template<typename T>
    struct Stream;

    template<typename T, template<typename> class IO>
    struct Stream<IO<T>> : IStream<T> {

    };
}

#endif //CC_STREAM_H
