//
// AUTOGENERATED, DO NOT EDIT
//
#include "precomp.hpp"

#ifdef HAVE_CLAMDFFT

#include "opencv2/ocl/cl_runtime/cl_runtime.hpp"
#include "opencv2/ocl/cl_runtime/clamdfft_runtime.hpp"

#if defined(_WIN32)
    static void* WinGetProcAddress(const char* name)
    {
        static HMODULE opencl_module = NULL;
        if (!opencl_module)
        {
            opencl_module = GetModuleHandleA("clAmdFft.Runtime.dll");
            if (!opencl_module)
            {
                opencl_module = LoadLibraryA("clAmdFft.Runtime.dll");
                if (!opencl_module)
                    return NULL;
            }
        }
        return (void*)GetProcAddress(opencl_module, name);
    }
    #define CV_CL_GET_PROC_ADDRESS(name) WinGetProcAddress(name)
#endif // _WIN32

#if defined(__linux__)
    #include <dlfcn.h>
    #include <stdio.h>

    static void* GetProcAddress (const char* name)
    {
        static void* h = NULL;
        if (!h)
        {
            h = dlopen("libclAmdFft.Runtime.so", RTLD_LAZY | RTLD_GLOBAL);
            if (!h)
                return NULL;
        }

        return dlsym(h, name);
    }
    #define CV_CL_GET_PROC_ADDRESS(name) GetProcAddress(name)
#endif

#ifndef CV_CL_GET_PROC_ADDRESS
#define CV_CL_GET_PROC_ADDRESS(name) NULL
#endif

// generated by parser_clamdfft.py
enum OPENCLAMDFFT_FN_ID {
    OPENCLAMDFFT_FN_clAmdFftSetup = 0,
    OPENCLAMDFFT_FN_clAmdFftTeardown,
    OPENCLAMDFFT_FN_clAmdFftGetVersion,
    OPENCLAMDFFT_FN_clAmdFftCreateDefaultPlan,
    OPENCLAMDFFT_FN_clAmdFftCopyPlan,
    OPENCLAMDFFT_FN_clAmdFftBakePlan,
    OPENCLAMDFFT_FN_clAmdFftDestroyPlan,
    OPENCLAMDFFT_FN_clAmdFftGetPlanContext,
    OPENCLAMDFFT_FN_clAmdFftGetPlanPrecision,
    OPENCLAMDFFT_FN_clAmdFftSetPlanPrecision,
    OPENCLAMDFFT_FN_clAmdFftGetPlanScale,
    OPENCLAMDFFT_FN_clAmdFftSetPlanScale,
    OPENCLAMDFFT_FN_clAmdFftGetPlanBatchSize,
    OPENCLAMDFFT_FN_clAmdFftSetPlanBatchSize,
    OPENCLAMDFFT_FN_clAmdFftGetPlanDim,
    OPENCLAMDFFT_FN_clAmdFftSetPlanDim,
    OPENCLAMDFFT_FN_clAmdFftGetPlanLength,
    OPENCLAMDFFT_FN_clAmdFftSetPlanLength,
    OPENCLAMDFFT_FN_clAmdFftGetPlanInStride,
    OPENCLAMDFFT_FN_clAmdFftSetPlanInStride,
    OPENCLAMDFFT_FN_clAmdFftGetPlanOutStride,
    OPENCLAMDFFT_FN_clAmdFftSetPlanOutStride,
    OPENCLAMDFFT_FN_clAmdFftGetPlanDistance,
    OPENCLAMDFFT_FN_clAmdFftSetPlanDistance,
    OPENCLAMDFFT_FN_clAmdFftGetLayout,
    OPENCLAMDFFT_FN_clAmdFftSetLayout,
    OPENCLAMDFFT_FN_clAmdFftGetResultLocation,
    OPENCLAMDFFT_FN_clAmdFftSetResultLocation,
    OPENCLAMDFFT_FN_clAmdFftGetPlanTransposeResult,
    OPENCLAMDFFT_FN_clAmdFftSetPlanTransposeResult,
    OPENCLAMDFFT_FN_clAmdFftGetTmpBufSize,
    OPENCLAMDFFT_FN_clAmdFftEnqueueTransform,
};
// generated by parser_clamdfft.py
const char* openclamdfft_fn_names[] = {
    "clAmdFftSetup",
    "clAmdFftTeardown",
    "clAmdFftGetVersion",
    "clAmdFftCreateDefaultPlan",
    "clAmdFftCopyPlan",
    "clAmdFftBakePlan",
    "clAmdFftDestroyPlan",
    "clAmdFftGetPlanContext",
    "clAmdFftGetPlanPrecision",
    "clAmdFftSetPlanPrecision",
    "clAmdFftGetPlanScale",
    "clAmdFftSetPlanScale",
    "clAmdFftGetPlanBatchSize",
    "clAmdFftSetPlanBatchSize",
    "clAmdFftGetPlanDim",
    "clAmdFftSetPlanDim",
    "clAmdFftGetPlanLength",
    "clAmdFftSetPlanLength",
    "clAmdFftGetPlanInStride",
    "clAmdFftSetPlanInStride",
    "clAmdFftGetPlanOutStride",
    "clAmdFftSetPlanOutStride",
    "clAmdFftGetPlanDistance",
    "clAmdFftSetPlanDistance",
    "clAmdFftGetLayout",
    "clAmdFftSetLayout",
    "clAmdFftGetResultLocation",
    "clAmdFftSetResultLocation",
    "clAmdFftGetPlanTransposeResult",
    "clAmdFftSetPlanTransposeResult",
    "clAmdFftGetTmpBufSize",
    "clAmdFftEnqueueTransform",
};

static void* openclamdfft_check_fn(int ID)
{
    void* func = CV_CL_GET_PROC_ADDRESS(openclamdfft_fn_names[ID]);
    if (!func)
    {
        std::ostringstream msg;
        msg << "OpenCL AMD FFT function is not available: [" << openclamdfft_fn_names[ID] << "]";
        CV_Error(CV_StsBadFunc, msg.str());
    }
    extern void* openclamdfft_fn_ptrs[];
    *(void**)(openclamdfft_fn_ptrs[ID]) = func;
    return func;
}

namespace {
// generated by parser_clamdfft.py
template <int ID, typename _R>
struct openclamdfft_fn0
{
    typedef _R (*FN)();
    static _R switch_fn()
    { return ((FN)openclamdfft_check_fn(ID))(); }
};

template <int ID, typename _R, typename _T1>
struct openclamdfft_fn1
{
    typedef _R (*FN)(_T1);
    static _R switch_fn(_T1 p1)
    { return ((FN)openclamdfft_check_fn(ID))(p1); }
};

template <int ID, typename _R, typename _T1, typename _T2>
struct openclamdfft_fn2
{
    typedef _R (*FN)(_T1, _T2);
    static _R switch_fn(_T1 p1, _T2 p2)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3>
struct openclamdfft_fn3
{
    typedef _R (*FN)(_T1, _T2, _T3);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4>
struct openclamdfft_fn4
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5>
struct openclamdfft_fn5
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6>
struct openclamdfft_fn6
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7>
struct openclamdfft_fn7
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8>
struct openclamdfft_fn8
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9>
struct openclamdfft_fn9
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10>
struct openclamdfft_fn10
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11>
struct openclamdfft_fn11
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12>
struct openclamdfft_fn12
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13>
struct openclamdfft_fn13
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14>
struct openclamdfft_fn14
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15>
struct openclamdfft_fn15
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16>
struct openclamdfft_fn16
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16, typename _T17>
struct openclamdfft_fn17
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16, _T17 p17)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16, typename _T17, typename _T18>
struct openclamdfft_fn18
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16, _T17 p17, _T18 p18)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16, typename _T17, typename _T18, typename _T19>
struct openclamdfft_fn19
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16, _T17 p17, _T18 p18, _T19 p19)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16, typename _T17, typename _T18, typename _T19, typename _T20>
struct openclamdfft_fn20
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16, _T17 p17, _T18 p18, _T19 p19, _T20 p20)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16, typename _T17, typename _T18, typename _T19, typename _T20, typename _T21>
struct openclamdfft_fn21
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16, _T17 p17, _T18 p18, _T19 p19, _T20 p20, _T21 p21)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21); }
};

template <int ID, typename _R, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7, typename _T8, typename _T9, typename _T10, typename _T11, typename _T12, typename _T13, typename _T14, typename _T15, typename _T16, typename _T17, typename _T18, typename _T19, typename _T20, typename _T21, typename _T22>
struct openclamdfft_fn22
{
    typedef _R (*FN)(_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22);
    static _R switch_fn(_T1 p1, _T2 p2, _T3 p3, _T4 p4, _T5 p5, _T6 p6, _T7 p7, _T8 p8, _T9 p9, _T10 p10, _T11 p11, _T12 p12, _T13 p13, _T14 p14, _T15 p15, _T16 p16, _T17 p17, _T18 p18, _T19 p19, _T20 p20, _T21 p21, _T22 p22)
    { return ((FN)openclamdfft_check_fn(ID))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22); }
};

}

// generated by parser_clamdfft.py
clAmdFftStatus (*clAmdFftSetup)(const clAmdFftSetupData*) = openclamdfft_fn1<OPENCLAMDFFT_FN_clAmdFftSetup, clAmdFftStatus, const clAmdFftSetupData*>::switch_fn;
clAmdFftStatus (*clAmdFftTeardown)() = openclamdfft_fn0<OPENCLAMDFFT_FN_clAmdFftTeardown, clAmdFftStatus>::switch_fn;
clAmdFftStatus (*clAmdFftGetVersion)(cl_uint*, cl_uint*, cl_uint*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetVersion, clAmdFftStatus, cl_uint*, cl_uint*, cl_uint*>::switch_fn;
clAmdFftStatus (*clAmdFftCreateDefaultPlan)(clAmdFftPlanHandle*, cl_context, const clAmdFftDim, const size_t*) = openclamdfft_fn4<OPENCLAMDFFT_FN_clAmdFftCreateDefaultPlan, clAmdFftStatus, clAmdFftPlanHandle*, cl_context, const clAmdFftDim, const size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftCopyPlan)(clAmdFftPlanHandle*, cl_context, clAmdFftPlanHandle) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftCopyPlan, clAmdFftStatus, clAmdFftPlanHandle*, cl_context, clAmdFftPlanHandle>::switch_fn;
clAmdFftStatus (*clAmdFftBakePlan)(clAmdFftPlanHandle, cl_uint, cl_command_queue*, void (CL_CALLBACK*) (clAmdFftPlanHandle plHandle, void* user_data), void*) = openclamdfft_fn5<OPENCLAMDFFT_FN_clAmdFftBakePlan, clAmdFftStatus, clAmdFftPlanHandle, cl_uint, cl_command_queue*, void (CL_CALLBACK*) (clAmdFftPlanHandle plHandle, void* user_data), void*>::switch_fn;
clAmdFftStatus (*clAmdFftDestroyPlan)(clAmdFftPlanHandle*) = openclamdfft_fn1<OPENCLAMDFFT_FN_clAmdFftDestroyPlan, clAmdFftStatus, clAmdFftPlanHandle*>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanContext)(const clAmdFftPlanHandle, cl_context*) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftGetPlanContext, clAmdFftStatus, const clAmdFftPlanHandle, cl_context*>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanPrecision)(const clAmdFftPlanHandle, clAmdFftPrecision*) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftGetPlanPrecision, clAmdFftStatus, const clAmdFftPlanHandle, clAmdFftPrecision*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanPrecision)(clAmdFftPlanHandle, clAmdFftPrecision) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftSetPlanPrecision, clAmdFftStatus, clAmdFftPlanHandle, clAmdFftPrecision>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanScale)(const clAmdFftPlanHandle, clAmdFftDirection, cl_float*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetPlanScale, clAmdFftStatus, const clAmdFftPlanHandle, clAmdFftDirection, cl_float*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanScale)(clAmdFftPlanHandle, clAmdFftDirection, cl_float) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftSetPlanScale, clAmdFftStatus, clAmdFftPlanHandle, clAmdFftDirection, cl_float>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanBatchSize)(const clAmdFftPlanHandle, size_t*) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftGetPlanBatchSize, clAmdFftStatus, const clAmdFftPlanHandle, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanBatchSize)(clAmdFftPlanHandle, size_t) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftSetPlanBatchSize, clAmdFftStatus, clAmdFftPlanHandle, size_t>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanDim)(const clAmdFftPlanHandle, clAmdFftDim*, cl_uint*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetPlanDim, clAmdFftStatus, const clAmdFftPlanHandle, clAmdFftDim*, cl_uint*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanDim)(clAmdFftPlanHandle, const clAmdFftDim) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftSetPlanDim, clAmdFftStatus, clAmdFftPlanHandle, const clAmdFftDim>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanLength)(const clAmdFftPlanHandle, const clAmdFftDim, size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetPlanLength, clAmdFftStatus, const clAmdFftPlanHandle, const clAmdFftDim, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanLength)(clAmdFftPlanHandle, const clAmdFftDim, const size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftSetPlanLength, clAmdFftStatus, clAmdFftPlanHandle, const clAmdFftDim, const size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanInStride)(const clAmdFftPlanHandle, const clAmdFftDim, size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetPlanInStride, clAmdFftStatus, const clAmdFftPlanHandle, const clAmdFftDim, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanInStride)(clAmdFftPlanHandle, const clAmdFftDim, size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftSetPlanInStride, clAmdFftStatus, clAmdFftPlanHandle, const clAmdFftDim, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanOutStride)(const clAmdFftPlanHandle, const clAmdFftDim, size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetPlanOutStride, clAmdFftStatus, const clAmdFftPlanHandle, const clAmdFftDim, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanOutStride)(clAmdFftPlanHandle, const clAmdFftDim, size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftSetPlanOutStride, clAmdFftStatus, clAmdFftPlanHandle, const clAmdFftDim, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanDistance)(const clAmdFftPlanHandle, size_t*, size_t*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetPlanDistance, clAmdFftStatus, const clAmdFftPlanHandle, size_t*, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanDistance)(clAmdFftPlanHandle, size_t, size_t) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftSetPlanDistance, clAmdFftStatus, clAmdFftPlanHandle, size_t, size_t>::switch_fn;
clAmdFftStatus (*clAmdFftGetLayout)(const clAmdFftPlanHandle, clAmdFftLayout*, clAmdFftLayout*) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftGetLayout, clAmdFftStatus, const clAmdFftPlanHandle, clAmdFftLayout*, clAmdFftLayout*>::switch_fn;
clAmdFftStatus (*clAmdFftSetLayout)(clAmdFftPlanHandle, clAmdFftLayout, clAmdFftLayout) = openclamdfft_fn3<OPENCLAMDFFT_FN_clAmdFftSetLayout, clAmdFftStatus, clAmdFftPlanHandle, clAmdFftLayout, clAmdFftLayout>::switch_fn;
clAmdFftStatus (*clAmdFftGetResultLocation)(const clAmdFftPlanHandle, clAmdFftResultLocation*) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftGetResultLocation, clAmdFftStatus, const clAmdFftPlanHandle, clAmdFftResultLocation*>::switch_fn;
clAmdFftStatus (*clAmdFftSetResultLocation)(clAmdFftPlanHandle, clAmdFftResultLocation) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftSetResultLocation, clAmdFftStatus, clAmdFftPlanHandle, clAmdFftResultLocation>::switch_fn;
clAmdFftStatus (*clAmdFftGetPlanTransposeResult)(const clAmdFftPlanHandle, clAmdFftResultTransposed*) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftGetPlanTransposeResult, clAmdFftStatus, const clAmdFftPlanHandle, clAmdFftResultTransposed*>::switch_fn;
clAmdFftStatus (*clAmdFftSetPlanTransposeResult)(clAmdFftPlanHandle, clAmdFftResultTransposed) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftSetPlanTransposeResult, clAmdFftStatus, clAmdFftPlanHandle, clAmdFftResultTransposed>::switch_fn;
clAmdFftStatus (*clAmdFftGetTmpBufSize)(const clAmdFftPlanHandle, size_t*) = openclamdfft_fn2<OPENCLAMDFFT_FN_clAmdFftGetTmpBufSize, clAmdFftStatus, const clAmdFftPlanHandle, size_t*>::switch_fn;
clAmdFftStatus (*clAmdFftEnqueueTransform)(clAmdFftPlanHandle, clAmdFftDirection, cl_uint, cl_command_queue*, cl_uint, const cl_event*, cl_event*, cl_mem*, cl_mem*, cl_mem) = openclamdfft_fn10<OPENCLAMDFFT_FN_clAmdFftEnqueueTransform, clAmdFftStatus, clAmdFftPlanHandle, clAmdFftDirection, cl_uint, cl_command_queue*, cl_uint, const cl_event*, cl_event*, cl_mem*, cl_mem*, cl_mem>::switch_fn;

// generated by parser_clamdfft.py
void* openclamdfft_fn_ptrs[] = {
    &clAmdFftSetup,
    &clAmdFftTeardown,
    &clAmdFftGetVersion,
    &clAmdFftCreateDefaultPlan,
    &clAmdFftCopyPlan,
    &clAmdFftBakePlan,
    &clAmdFftDestroyPlan,
    &clAmdFftGetPlanContext,
    &clAmdFftGetPlanPrecision,
    &clAmdFftSetPlanPrecision,
    &clAmdFftGetPlanScale,
    &clAmdFftSetPlanScale,
    &clAmdFftGetPlanBatchSize,
    &clAmdFftSetPlanBatchSize,
    &clAmdFftGetPlanDim,
    &clAmdFftSetPlanDim,
    &clAmdFftGetPlanLength,
    &clAmdFftSetPlanLength,
    &clAmdFftGetPlanInStride,
    &clAmdFftSetPlanInStride,
    &clAmdFftGetPlanOutStride,
    &clAmdFftSetPlanOutStride,
    &clAmdFftGetPlanDistance,
    &clAmdFftSetPlanDistance,
    &clAmdFftGetLayout,
    &clAmdFftSetLayout,
    &clAmdFftGetResultLocation,
    &clAmdFftSetResultLocation,
    &clAmdFftGetPlanTransposeResult,
    &clAmdFftSetPlanTransposeResult,
    &clAmdFftGetTmpBufSize,
    &clAmdFftEnqueueTransform,
};

#endif
