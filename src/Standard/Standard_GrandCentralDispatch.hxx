// Created on: 2013-12-12
// Created by: Istvan Csanady
// Copyright (c) 2013-2014 Istvan Csanady
//
// This file is part of OCE software library.
//
// This library is free software; you can redistribute it and / or modify it
// under the terms of the GNU Lesser General Public version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCE
// distribution for complete text of the license and disclaimer of any warranty.

#if(defined(__APPLE__) && defined(USE_GCD))
#include <functional>
#include <dispatch/dispatch.h>

class ParallelProcessor
{
public:
    ParallelProcessor();
    void AddOp(std::function<void()> op);
    void Sync();
private:
    dispatch_group_t group;
};

template <typename InputIterator, typename Function>
void parallel_for_each(InputIterator first, InputIterator last, Function function) {
    ParallelProcessor processor;
    for (auto iterator = first; iterator != last; ++iterator)
        processor.AddOp([function, iterator]() {
            function(iterator);
        });
    processor.Sync();
}

#endif
