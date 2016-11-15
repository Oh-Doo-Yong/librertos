/*
 Copyright 2016 Djones A. Boni

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef LIBRERTOS_H_
#define LIBRERTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "projdefs.h"

#ifndef LIBRERTOS_MAX_PRIORITY
#define LIBRERTOS_MAX_PRIORITY       2  /* integer > 0 */
#endif

#ifndef LIBRERTOS_PREEMPTION
#define LIBRERTOS_PREEMPTION         0  /* boolean */
#endif

#ifndef LIBRERTOS_TICK
#define LIBRERTOS_TICK               0  /* boolean */
#endif

#ifndef LIBRERTOS_ENABLE_TASKDELETE
#define LIBRERTOS_ENABLE_TASKDELETE  0  /* boolean */
#endif

typedef void* taskParameter_t;
typedef void(*taskFunction_t)(taskParameter_t);



void OS_init(void);
void OS_tick(void);

void OS_scheduler(void);
int8_t OS_schedulerIsLocked(void);
void OS_schedulerLock(void);
void OS_schedulerUnlock(void);

void OS_taskCreate(
        priority_t priority,
        taskFunction_t function,
        taskParameter_t parameter);
void OS_taskDelete(priority_t priority);
priority_t OS_taskGetCurrentPriority(void);
void OS_taskSuspend(priority_t priority);
void OS_taskResume(priority_t priority);
void OS_taskDelay(tick_t ticksToDelay);



struct taskListNode_t;

struct taskHeadList_t {
    struct taskListNode_t* ListHead;
    struct taskListNode_t* ListTail;
    tick_t                 TickToWakeup_Zero;
    int8_t                 ListLength;
};

struct taskListNode_t {
    struct taskListNode_t* ListNext;
    struct taskListNode_t* ListPrevious;
    tick_t                 TickToWakeup;
    priority_t             TaskPriority;
    struct taskHeadList_t* ListInserted;
};



struct event_t {
    struct taskHeadList_t ListRead;
    struct taskHeadList_t ListWrite;
};



struct Semaphore_t {
    volatile int8_t Count;
    const int8_t    Max;
    struct event_t  Event;
};

void Semaphore_initbinary(struct Semaphore_t* o);
void Semaphore_init(struct Semaphore_t* o, int8_t max);
int8_t Semaphore_lock(struct Semaphore_t* o);
int8_t Semaphore_unlock(struct Semaphore_t* o);
int8_t Semaphore_lockPend(struct Semaphore_t* o, tick_t ticksToWait);



#define LIBRERTOS_SCHEDULER_NOT_RUNNING  -1

#ifdef __cplusplus
}
#endif

#endif /* LIBRERTOS_H_ */
