/* Copyright (C) 2021 Jacky Chen <cjacky97@gmail.com>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ezQueue.h"

int main(int argc, char** argv) {
    struct ezQueue q;
    int i, n;

    ezQueueCreate(&q, NULL, 29);

    for (i = 0; i < 10; ++i) {
        if (ezQueueWrite(&q, &i, sizeof(int))) {
            printf("write %d fail\n", i);
        }
    }
    for (i = 0; i < 20; ++i) {
        ezQueueRead(&q, &n, sizeof(int));
        ezQueueWrite(&q, &n, sizeof(int));
        printf("w/r %d\n", n);
    }
    ezQueueDelete(&q);
    return 0;
}