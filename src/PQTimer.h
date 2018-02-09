// Copyright (C) 2018 ichenq@outlook.com. All rights reserved.
// Distributed under the terms and conditions of the Apache License. 
// See accompanying files LICENSE.

#pragma once

#include "ITimer.h"
#include <unordered_map>


// timer queue implemented with priority queue(min-heap)
//
// complexity:
//     AddTimer    CancelTimer   PerTick
//      O(log N)    O(log N)       O(1)
//
class PQTimer : public ITimerQueue
{
public:
    struct TimerNode;

public:
    PQTimer();
    ~PQTimer();

    PQTimer(const PQTimer&) = delete;
    PQTimer& operator=(const PQTimer&) = delete;

    int AddTimer(uint32_t time, TimerCallback cb) override;

    bool CancelTimer(int id) override;

    void Update() override;

    int Size() const { return (int)heap_.size(); }

private:
    void clear();
    bool siftdown(int x, int n);
    void siftup(int j);

private:
    int counter_ = 0;
    const int64_t twepoch; // custom epoch
    std::vector<TimerNode*> heap_;
    std::unordered_map<int, TimerNode*> ref_;
};
