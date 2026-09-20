#include <iostream>
#include <cmath>
#include <iomanip>

#include "scope_timer.hpp"

#ifdef DISABLE_DENORMALS
#ifdef _MSC_VER
#include <xmmintrin.h>
#endif


void enable_ftz_daz(){
#ifdef _MSC_VER
    auto mxcsr = _mm_getcsr();        /*read the old MXCSR setting  */    \
    mxcsr |= 0x8040;  /* set DAZ and FZ bits        */    \
    _mm_setcsr( mxcsr );             /* write the new MXCSR setting to the MXCSR */
#else
    asm volatile (
            ".intel_syntax noprefix;\n"
            "sub rsp, 8;\n"
            "stmxcsr [rsp];\n"
            "or word ptr[rsp],0x8040;\n"
            "ldmxcsr [rsp];\n"
            "add rsp, 8;\n"
            ".att_syntax;\n"
            :
            :
            : "memory"
            );
#endif
}
#endif


constexpr size_t COUNT  =10000000;
const float MULTIPLIER1 = 1.0000001;
const float MULTIPLIER2 = 0.99;


float g_sum_t(float start_value, float multiplier, size_t count)
{
    return start_value*(1-powf(multiplier, static_cast<float>(count)))/(1-multiplier);
}

float g_sum(float start_value, float multiplier, size_t count)
{
    float a = start_value;
    float result = 0;
    for (int i =0; i < count; ++i)
    {
        result += a;
        a*=multiplier;
    }
    return result;
}


void do_experiment(float multiplier, size_t count)
{
    std::cout << std::setprecision(8);
    std::cout << "Progression of size " << count << " with multiplier " << multiplier<< std::endl;
    std::cout << "Theoretical answer:" <<  g_sum_t(1, multiplier, count)<< std::endl;
    volatile float sum; // volatile - to prevent optimizations
    {
        scope_timer _("\tSum");
        sum = g_sum(1, multiplier, count);
    }
    std::cout << "Direct sum:" <<  sum << std::endl;
}

int main()
{
    do_experiment(MULTIPLIER1, COUNT);

    #ifdef DISABLE_DENORMALS
        enable_ftz_daz();
    #endif

    do_experiment(MULTIPLIER2, COUNT);
}
