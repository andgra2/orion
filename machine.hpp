#pragma once

#include <stdexcept>
#include "cpu.hpp"
#include "code.hpp"

namespace Orion
{
    class Machine
    {
    public: 
        static constexpr unsigned int num_api_data_cells = 1024;
 
        Machine();
        ~Machine();
        void api_call(void) noexcept;
        Cell &operator[](unsigned int i);
    private:
        Memory m_;
        CPU c_;
        Cell pc_destr_code_;
        Cell pc_api_code_;
        Cell pc_api_data_;
    };
}

