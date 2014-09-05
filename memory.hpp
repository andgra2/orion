#pragma once

#include <cstdint>
#include <limits>
#include <new>

namespace Orion
{
    using Cell = uint64_t;

    constexpr Cell pc_null = 0;

    class Memory
    {
    public:
        Cell new_block_nothrow(Cell s) noexcept;
        Cell new_block(Cell s);
        void delete_block(Cell pc) noexcept;
        Cell &operator[](Cell pc) noexcept;
    private:
        static Cell *to_ptr(Cell pc) noexcept;
        static Cell to_pc(Cell *ptr) noexcept;
    };

    class PCHandle
    {
    public:
        PCHandle(Memory &m, Cell s);
        ~PCHandle();
        Cell pc(void) noexcept;
        Cell take_pc(void) noexcept;
    private:
        Memory &m_;
        Cell pc_;
    };
}

#include "memory_.hpp"

