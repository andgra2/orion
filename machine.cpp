#include "machine.hpp"

namespace Orion
{
    Machine::Machine() : m_(), c_(m_, pc_destr_code_, pc_api_code_, pc_api_data_)
    {
        PCHandle h_dc(m_, 1024), h_ac(m_, 1024), h_ad(m_, 1024);

        Code c(m_);
        Cell x;

        x = h_ac.pc();
        c.wi(x, "t");

        x = h_dc.pc();
        c.wi(x, "d c",  h_ad.pc());
        c.wi(x, "d c",  h_ac.pc());
        c.wi(x, "dt c", h_dc.pc());

        pc_destr_code_ = h_dc.take_pc();
        pc_api_code_ = h_ac.take_pc();
        pc_api_data_ = h_ad.take_pc();
    }

    Machine::~Machine()
    {
        c_.run(pc_destr_code_);        
    }

    void Machine::api_call(void) noexcept
    {
        c_.run(pc_api_code_);
    }
    
    Cell &Machine::operator[](unsigned int i)
    {
        if (i >= num_api_data_cells) throw std::out_of_range("");

        return m_[pc_api_data_ + i];
    }
}

