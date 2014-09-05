#pragma once

#include "memory.hpp"

namespace Orion
{
    class CPU
    {
    public:
        CPU(Memory &m, Cell &pc_destructor_code, Cell &pc_api_code, Cell &pc_api_data) noexcept;
        void run_init(Cell pc_start_instr) noexcept;
        bool run_step(void) noexcept;
        void run(Cell start_instr) noexcept;
    private:
        Memory & m_;
        Cell & pc_destructor_code_;
        Cell & pc_api_code_;
        Cell & pc_api_data_;
        Cell pc_next_instr_;
        Cell *a_[4];

        Cell &a(unsigned int ai) noexcept;
        void run_instr(unsigned int ii) noexcept;
    };
}

#include "cpu_.hpp"

