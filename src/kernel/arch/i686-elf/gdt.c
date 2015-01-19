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

#include <arch.h>

#include <stdint.h>

extern gdt_entry_t gdt[256];

gdt_entry_t gdt_encode(
        addr_t     offset,
        uint32_t   length,
        uint8_t    access,
        uint8_t    granularity
        ) {
    return (gdt_entry_t) {
        .offsetlo    = (uint16_t)(offset & 0xffff),
        .offsetmd    = (uint8_t)(offset >> 16 & 0xff),
        .offsethi    = (uint8_t)(offset >> 24 & 0xff),
        .lengthlo    = (uint16_t)(length & 0xffff),
        .granularity = (length >> 16 & 0x0f) | (granularity & 0xf0),
        .access      = access
    };
}

void gdt_setup() {
    gdt[1] = gdt_encode(0, UINT32_MAX, 0b10011010, 0b11000000);
    gdt[2] = gdt_encode(0, UINT32_MAX, 0b10010010, 0b11000000);
    gdt[3] = gdt_encode(0, UINT32_MAX, 0b11111010, 0b11000000);
    gdt[4] = gdt_encode(0, UINT32_MAX, 0b11110010, 0b11000000);
}
