/* Copyright (C) 2014 Cormac O'Brien.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef _ARCH_H
#define _ARCH_H

#include <stdint.h>

typedef uint32_t addr_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute((__packed__)) idt_ptr_t;

typedef struct {
    uint16_t offsetlo;
    uint16_t selector;
    uint8_t  mustzero;
    uint8_t  typeattr;
    uint16_t offsethi;
} __attribute__((__packed__)) idt_entry_t;

typedef struct {
    uint16_t limitlo;
    uint16_t baselo;
    uint8_t  basemid;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  basehi;
} __attribute__((__packed__)) gdt_entry_t;

#endif /* ARCH_H */
