#include <iostream>
#include "machine.hpp"

using namespace std;
using namespace Orion;

int main(void)
{
    try
    {
        Machine w;

        w.api_call();
    }
    catch (...)
    {
        std::cout << "Boom!" << std::endl;
    }
}

