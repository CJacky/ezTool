/* Copyright (C) 2021 Jacky Chen <cjacky97@gmail.com>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include <stdint.h>
#include <stdbool.h>

struct ezQueue {
    uint8_t*    buffer;
    uint32_t    read_offset;
    uint32_t    write_offset;
    uint32_t    buf_size;
    uint32_t    free_size;
    uint32_t    flag;
};

enum ezQueueFlag {
    E_STATIC_BUF = 0x1,
};

int ezQueueCreate(struct ezQueue* queue, void* buf, uint32_t buf_size);
int ezQueueDelete(struct ezQueue* queue);
int ezQueueReset(struct ezQueue* queue);

int ezQueueWrite(struct ezQueue* queue, void* data, uint32_t data_size);
int ezQueueRead(struct ezQueue* queue, void* data, uint32_t data_size);
int ezQueueSize(struct ezQueue* queue);
