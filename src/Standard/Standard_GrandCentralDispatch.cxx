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
#include "Standard_GrandCentralDispatch.hxx"
#include <dispatch/dispatch.h>

static dispatch_queue_t parallel_queue;

ParallelProcessor::ParallelProcessor()
{
    group = dispatch_group_create();
}

void ParallelProcessor::AddOp(std::function<void()> op)
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        parallel_queue = dispatch_queue_create("parallel queue", DISPATCH_QUEUE_CONCURRENT);
    });
    dispatch_group_async(group, parallel_queue, ^{
        op();
    });
}

void ParallelProcessor::Sync()
{
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
}
#endif
