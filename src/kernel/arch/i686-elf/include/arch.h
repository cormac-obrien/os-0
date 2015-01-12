#ifndef _ARCH_H
#define _ARCH_H

#include <stdint.h>

typedef uint32_t addr_t;

typedef struct {
    uint16_t baselo;
    uint16_t select;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t basehi;
} __attribute__((__packed__)) idt_entry_t;

typedef struct {
    uint16_t limitlo;
    uint16_t baselo;
    uint8_t basemid;
    uint8_t access;
    uint8_t granularity;
    uint8_t basehi;
} __attribute__((__packed__)) gdt_entry_t;

#endif /* ARCH_H */
