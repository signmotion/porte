#pragma once

#include "..\..\..\configure.h"
#include "../../porte/EngineWithoutBooster.h"
#include <numeric>
#include <boost/assign.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/random.hpp>
 #include <boost/math/special_functions/pow.hpp> 
#include <ctime>


/* - ���. ���������� C-������ �� NVIDIA.
     ��. http://nvidia.com/content/cuda/cuda-downloads.html
#include "../../external/opencl/cl.hpp"
*/
#include <oclUtils.h>
#include <CL/cl_gl.h>    

// (i) ��� Apple: "cl_APPLE_gl_sharing"
#define GL_SHARING_EXTENSION "cl_khr_gl_sharing"


// ���������� ��������� define
#undef CL_NONE



namespace porte {

class DungeonCrawl;

}




namespace porte {


/**
* ������ ��� ������������� �������, ��������� ���������� �� DungeonCrawl.
*
* @template ��. Engine.
*/
class DungeonCrawl : public EngineWithoutBooster {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< DungeonCrawl >  Ptr;
    typedef std::unique_ptr< DungeonCrawl >  UPtr;



public:
    DungeonCrawl( portulan_t* );

    virtual ~DungeonCrawl();



    /**
    * �������������� ������� �������.
    */
    void init();


    /**
    * �������������� ���������� � ������� �������.
    */
    void initComponent();


    /**
    * �������������� ����� ���������� � ������� �������.
    */
    void initTemperature();


    /**
    * �������������� ����� ��������� � ������� �������.
    */
    void initLiving();


    

protected:
    /**
    * @virtual EngineWithoutBooster
    */
    virtual void pulse( int n );




private:
    void prepareCLContext();
    void prepareCLCommandQueue();

    // # ������� ���������� ������� �����. ������� �������������.
    void prepareCLKernel();
    void prepareComponentCLKernel();
    void prepareTemperatureCLKernel();
    void prepareLivingCLKernel();

    template< size_t G >
    void compileCLKernel(
        const std::vector< std::string >&  kernelKeys,
        const std::string& options = ""
    );


    /**
    * ����� ��������� � ����� ��� �������� ���� OpenCL.
    *
    *   #! ��� ���������, ������������ � OpenCL ���� "define" ������� � ���� OpenCL
    *      ��������� � ��������� ���� ����. ������ ����� ��� float-��������, �������
    *      ����� ��������� ����� ������ �����. � ��������� ������, ���������� � ��
    *      �������� ����� ������������ ������������ ��� �������������. ������� - ������.
    */
    static std::string commonConstantCLKernel();
    static std::string commonOptionCLKernel();


    static void fnErrorCL( int exitCode );




private:
    /**
    * ����������, �������� � ���� OpenCL ��� ������ � ���������� ����.
    */
    std::map< std::string, cl_kernel >  kernelCL;

    /**
    * ��������� ��� OpenCL-����������.
    *   # ������� "work" ����������� � ���������, ������� ������������ ������ ���
    *     ������������� ����������.
    *   # ���������� ���������� ����������� �� ��������.
    */
    cl_mem aboutPlanetCL;
    const size_t memsizeAboutPlanet;

    cl_mem componentCL;
    const size_t memsizeComponent;

    cl_mem livingCL;
    const size_t memsizeLiving;

    cl_mem temperatureCL;
    const size_t memsizeTemperature;


    /**
    * ��������� ����. �����.
    */
    boost::mt19937 randomCore;
    boost::uniform_int< cl_uint >  randomDistribution;
    boost::variate_generator<
        boost::mt19937&, boost::uniform_int< unsigned int >
    > randomGenerator;
    cl_uint randomSeed;


    /**
    * ��������������� ����������.
    */
    cl_int errorCL;

    cl_device_id* devicesCL;
    cl_uint deviceUsedCL;
    cl_uint devCountCL;
    cl_platform_id platformCL;

    cl_context gpuContextCL;

    // @todo optimize? ������������ ����. �������� ������?
    cl_command_queue commandQueueCL;
};




} // porte






void __stdcall pfn_notify_cl(
    const char* errinfo, const void* private_info,
    size_t cb, void* user_data
);


/* - �� ������, ������ ����� ����� ����������.
void __stdcall pfn_notify_program_cl(
    cl_program, void* user_data
);
*/







// ������� �� ����. ������ ��� ��������
#include "DungeonCrawl.inl"
#include "prepare.inl"
#include "init.inl"