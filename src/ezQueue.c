/* Copyright (C) 2021 Jacky Chen <cjacky97@gmail.com>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "ezQueue.h"

int ezQueueCreate(struct ezQueue* queue, void* buf, uint32_t buf_size) {
    if (queue == NULL || buf == NULL || buf_size == 0) {
        return -EINVAL;
    }
    memset(queue, 0, sizeof(struct ezQueue));
    queue->buffer = buf;
    queue->buf_size = buf_size;
    queue->free_size = buf_size;
    return 0;
}

int ezQueueDelete(struct ezQueue* queue) {
    if (queue == NULL) {
        return -EINVAL;
    }
    memset(queue, 0, sizeof(struct ezQueue));
    return 0;
}

int ezQueueReset(struct ezQueue* queue) {
    if (queue == NULL) {
        return -EINVAL;
    }
    queue->read_offset = 0;
    queue->write_offset = 0;
    queue->free_size = queue->buf_size;
    return 0;
}

int ezQueueWrite(struct ezQueue* queue, void* data, uint32_t data_size) {
    if (queue == NULL || data == NULL || data_size == 0) {
        return -EINVAL;
    }
    if (queue->free_size < data_size) {
        return -EAGAIN;
    }
    queue->free_size -= data_size;
    if (queue->write_offset + data_size >= queue->buf_size) {
        int remain = queue->buf_size - queue->write_offset;
        memcpy(queue->buffer + queue->write_offset, data, remain);
        queue->write_offset = 0;
        data_size -= remain;
        data += remain;
    }
    if (data_size > 0) {
        memcpy(queue->buffer + queue->write_offset, data, data_size);
        queue->write_offset += data_size;
    }
    return 0;
}

int ezQueueRead(struct ezQueue* queue, void* data, uint32_t data_size) {
    if (queue == NULL || data == NULL || data_size == 0) {
        return -EINVAL;
    }
    if (queue->buf_size - queue->free_size < data_size) {
        return -EAGAIN;
    }
    queue->free_size += data_size;
    if (queue->read_offset + data_size >= queue->buf_size) {
        int remain = queue->buf_size - queue->read_offset;
        memcpy(data, queue->buffer + queue->read_offset, remain);
        queue->read_offset = 0;
        data_size -= remain;
        data += remain;
    }
    if (data_size > 0) {
        memcpy(data, queue->buffer + queue->read_offset, data_size);
        queue->read_offset += data_size;
    }
    return 0;
}

int ezQueueSize(struct ezQueue* queue) {
    if (queue == NULL) {
        return -EINVAL;
    }
    return queue->buf_size - queue->free_size;
}
