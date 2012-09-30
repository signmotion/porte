namespace porte {


/**
* ����� ������� ������ DungeonCrawl.
*/


inline void DungeonCrawl::init() {
#ifdef COMPONENT_DUNGEONCRAWL_PORTE
    initComponent();
#endif

#ifdef TEMPERATURE_DUNGEONCRAWL_PORTE
    initTemperature();
#endif

#ifdef SURFACE_TEMPERATURE_DUNGEONCRAWL_PORTE
    initSurfaceTemperature();
#endif

#ifdef RAINFALL_DUNGEONCRAWL_PORTE
    initRainfall();
#endif

#ifdef DRAINAGE_DUNGEONCRAWL_PORTE
    initDrainage();
#endif

#ifdef BIOME_DUNGEONCRAWL_PORTE
    initBiome();
#endif

#ifdef LIVING_DUNGEONCRAWL_PORTE
    initLiving();
#endif
}





#ifdef COMPONENT_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initComponent() {

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "���������� ������ ������� ..";
#endif

    static const size_t grid = pd::COMPONENT_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };

    // �������������� �����
    const cl_kernel kernel = kernelCL[ "scale/component/top/init" ];

    // 0
    errorCL = clSetKernelArg( kernel, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernel, 1, sizeof( cl_mem ), &componentCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernel,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // �������������
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // ���������
    errorCL = clEnqueueReadBuffer(
        commandQueueCL,
        componentCL,
        CL_TRUE,
        0,
        memsizeComponent,
        mPortulan->topology().topology().component.content,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
}
#endif





#ifdef TEMPERATURE_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initTemperature() {

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "����������� ������� ..";
#endif

    static const size_t grid = pd::TEMPERATURE_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };

    // ����� ����������� ��������� �������
    const cl_kernel kernelInit = kernelCL[ "scale/temperature/top/init" ];

    /* @test
    pd::test_t test;
    const size_t memsizeTest = sizeof( pd::test_t );
    cl_mem testCL = clCreateBuffer(
        gpuContextCL,
        // ���. ������ �� ����������
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
        memsizeTest,
        &test,
        &errorCL
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );
    errorCL = clSetKernelArg( kernel, 0, sizeof( cl_mem ), &testCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );
    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernel,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );
    */


    // 0
    errorCL = clSetKernelArg( kernelInit, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernelInit, 1, sizeof( cl_mem ), &temperatureCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernelInit,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // �������������
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // ���������
    errorCL = clEnqueueReadBuffer(
        commandQueueCL,
        temperatureCL,
        CL_TRUE,
        0,
        memsizeTemperature,
        mPortulan->topology().topology().temperature.content,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
}
#endif





#ifdef SURFACE_TEMPERATURE_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initSurfaceTemperature() {

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "������ ������ - ����������� ..";
#endif

    static const size_t grid = pd::SURFACE_TEMPERATURE_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };

    // ����� ����������� �� ����������� �������
    const cl_kernel kernelInit = kernelCL[ "scale/surface-temperature/top/init" ];

    // 0
    errorCL = clSetKernelArg( kernelInit, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernelInit, 1, sizeof( cl_mem ), &surfaceTemperatureCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernelInit,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // �������������
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // ���������
    errorCL = clEnqueueReadBuffer(
        commandQueueCL,
        surfaceTemperatureCL,
        CL_TRUE,
        0,
        memsizeSurfaceTemperature,
        mPortulan->topology().topology().surfaceTemperature.content,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
}
#endif





#ifdef RAINFALL_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initRainfall() {

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "������ ������ - ����������� ������ ..";
#endif

    static const size_t grid = pd::RAINFALL_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };

    // ����� ���. ������ �� ����������� �������
    const cl_kernel kernelInit = kernelCL[ "scale/rainfall/top/init" ];

    // 0
    errorCL = clSetKernelArg( kernelInit, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernelInit, 1, sizeof( cl_mem ), &rainfallCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 2
    const cl_uint rseed = randomGenerator();
    errorCL = clSetKernelArg( kernelInit, 2, sizeof( cl_uint ), &rseed );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernelInit,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // �������������
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // ���������
    errorCL = clEnqueueReadBuffer(
        commandQueueCL,
        rainfallCL,
        CL_TRUE,
        0,
        memsizeRainfall,
        mPortulan->topology().topology().rainfall.content,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
}
#endif





#ifdef DRAINAGE_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initDrainage() {

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "������ ������ - ������ ..";
#endif

    static const size_t grid = pd::DRAINAGE_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };


    // ����� ������ �� ����������� �������
    const cl_kernel kernelInit = kernelCL[ "scale/drainage/top/init" ];

    // 0
    errorCL = clSetKernelArg( kernelInit, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernelInit, 1, sizeof( cl_mem ), &drainageCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 2
    const cl_uint rseed = randomGenerator();
    errorCL = clSetKernelArg( kernelInit, 2, sizeof( cl_uint ), &rseed );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernelInit,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // �������������
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // ���������
    errorCL = clEnqueueReadBuffer(
        commandQueueCL,
        drainageCL,
        CL_TRUE,
        0,
        memsizeDrainage,
        mPortulan->topology().topology().drainage.content,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
}
#endif





#ifdef BIOME_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initBiome() {

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "��������� ����� ..";
#endif

    static const size_t grid = pd::BIOME_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };


    // ��������� �����
    // # ��� ������������ ������ ������ ���� �������������� ����������������.
    const cl_kernel kernelInit = kernelCL[ "scale/biome/top/init" ];

    // 0
    errorCL = clSetKernelArg( kernelInit, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernelInit, 1, sizeof( cl_mem ), &biomeCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 2
    errorCL = clSetKernelArg( kernelInit, 2, sizeof( cl_mem ), &temperatureCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 3
    errorCL = clSetKernelArg( kernelInit, 3, sizeof( cl_mem ), &surfaceTemperatureCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 4
    errorCL = clSetKernelArg( kernelInit, 4, sizeof( cl_mem ), &rainfallCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 5
    errorCL = clSetKernelArg( kernelInit, 5, sizeof( cl_mem ), &drainageCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 6
    const cl_uint rseed = randomGenerator();
    errorCL = clSetKernelArg( kernelInit, 6, sizeof( cl_uint ), &rseed );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernelInit,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // �������������
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // ���������
    errorCL = clEnqueueReadBuffer(
        commandQueueCL,
        biomeCL,
        CL_TRUE,
        0,
        memsizeBiome,
        mPortulan->topology().topology().biome.content,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
}
#endif





#ifdef LIVING_DUNGEONCRAWL_PORTE
inline void DungeonCrawl::initLiving() {
    // #! ��������� ��� �������� OpenCL ������ ���� ������������ � prepareComponent().

    namespace pd = portulan::planet::set::dungeoncrawl;

#ifdef _DEBUG
    std::cout << "�������� ������� ..";
#endif

    static const size_t grid = pd::LIVING_GRID;

    static const size_t GRID_WORK_DIM = 3;
    static const size_t GRID_GLOBAL_WORK_SIZE[] = { grid, grid, grid };

    auto& tp = mPortulan->topology().topology();

    // �������������� �����

    // ������� ������� ���������
    cl_kernel kernel = kernelCL[ "scale/living/top/clear" ];

    // 0
    errorCL = clSetKernelArg( kernel, 0, sizeof( cl_mem ), &livingCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clEnqueueNDRangeKernel(
        commandQueueCL,
        kernel,
        GRID_WORK_DIM,
        nullptr,
        GRID_GLOBAL_WORK_SIZE,
        nullptr,
        0, nullptr, nullptr
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    /** - �������������� ����� � ������ ����� (��. ����).
          ��������� ������������ ������ CPU � GPU ��� ��������
          �������� ���������� ����.
    errorCL = clFinish( commandQueueCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );
    */

#ifdef _DEBUG
    std::cout << ".";
#endif


    // �������� init() �� ��� ���, ���� ���-�� ������ �� �������
    // �� ����� ������ � ���������
    kernel = kernelCL[ "scale/living/top/init" ];

    // 0
    errorCL = clSetKernelArg( kernel, 0, sizeof( cl_mem ), &aboutPlanetCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 1
    errorCL = clSetKernelArg( kernel, 1, sizeof( cl_mem ), &livingCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 2
    // �� ������� �� ������������ � ���������� ��������� ���-�� ������.
    // �������������� ����������� ��������
    pd::zoneLivingCountComplete_t zoneCountComplete;
    static const size_t memsizeZoneCountComplete =
        sizeof( pd::zoneOneLivingCountComplete_t ) *
        pd::LIVING_COUNT * pd::LIFE_CYCLE_COUNT;
    cl_mem zoneCountCompleteCL = clCreateBuffer(
        gpuContextCL,
        // ���. ������ �� ����������
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
        memsizeZoneCountComplete,
        &zoneCountComplete,
        &errorCL
    );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    errorCL = clSetKernelArg( kernel, 2, sizeof( cl_mem ), &zoneCountCompleteCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 3
    // # �������� ��� ����� ������������� ��������� �������.
    const pd::LIFE_CYCLE lifeCycle = pd::LC_ADULT;
    errorCL = clSetKernelArg( kernel, 3, sizeof( pd::LIFE_CYCLE ), &lifeCycle );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 4
    errorCL = clSetKernelArg( kernel, 4, sizeof( cl_mem ), &componentCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 5
    errorCL = clSetKernelArg( kernel, 5, sizeof( cl_mem ), &temperatureCL );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

    // 6
    // ��� ������ ��������� ������ �������� ��� ������ ������ ����, �����
    // ������������� ���: � ���� OpenCL ������������� "���������� �����".
    const cl_uint rseed = randomGenerator();
    errorCL = clSetKernelArg( kernel, 6, sizeof( cl_uint ), &rseed );
    oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );


    const auto& al = tp.aboutPlanet.living;

    // �������� ���-�� ������
    float allZoneDesireCount = 0.0f;
    pd::zoneLivingCount_t zoneDesireCount = {};
    /* - ����� ���������� ���. ��. ����.
    const auto fnDesireCount = [ &zoneDesireCount, lifeCycle ] (
        float& zolValue,
        const pd::zoneLiving_t& zl
    ) -> void {
        const pd::CODE_LIVING code = zl.code;
        if (code != pd::CL_NONE) {
            const float q = zl.count;
            zolValue += q;
            zoneDesireCount[ code ][ lifeCycle ].all += q;
        }
    };
    */
    for (size_t k = 0; k < pd::LIVING_CELL; ++k) {
        // space
        {
            const auto& zk = al.space[k];
            const pd::CODE_LIVING code = zk.code;
            if (code != pd::CL_NONE) {
                zoneDesireCount[ code ][ lifeCycle ].space += zk.count;
                zoneDesireCount[ code ][ lifeCycle ].all += zk.count;
                allZoneDesireCount += zk.count;
            }
        }
        // atmosphere
        {
            const auto& zk = al.atmosphere[k];
            const pd::CODE_LIVING code = zk.code;
            if (code != pd::CL_NONE) {
                zoneDesireCount[ code ][ lifeCycle ].atmosphere += zk.count;
                zoneDesireCount[ code ][ lifeCycle ].all += zk.count;
                allZoneDesireCount += zk.count;
            }
        }
        // crust
        {
            const auto& zk = al.crust[k];
            const pd::CODE_LIVING code = zk.code;
            if (code != pd::CL_NONE) {
                zoneDesireCount[ code ][ lifeCycle ].crust += zk.count;
                zoneDesireCount[ code ][ lifeCycle ].all += zk.count;
                allZoneDesireCount += zk.count;
            }
        }
        // mantle
        {
            const auto& zk = al.mantle[k];
            const pd::CODE_LIVING code = zk.code;
            if (code != pd::CL_NONE) {
                zoneDesireCount[ code ][ lifeCycle ].mantle += zk.count;
                zoneDesireCount[ code ][ lifeCycle ].all += zk.count;
                allZoneDesireCount += zk.count;
            }
        }
        // core
        {
            const auto& zk = al.core[k];
            const pd::CODE_LIVING code = zk.code;
            if (code != pd::CL_NONE) {
                zoneDesireCount[ code ][ lifeCycle ].core += zk.count;
                zoneDesireCount[ code ][ lifeCycle ].all += zk.count;
                allZoneDesireCount += zk.count;
            }
        }
    } // for (size_t k


    // �������� init(), ����������� ���������� ���-��
    // @see ��������� ��� init().
    size_t iteration = 0;
    for ( ; ; ) {
        // �������������� ������
        // (��. ���� ����. ����� ������ ���� clear())
        errorCL = clFinish( commandQueueCL );
        oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

        // ���������
        // ������ ����� - ��������������������� ���� ������ ����������,
        // ����������� - ��������� ������ ���� init()
        // @todo optimize ����������� ������������ livingCL ���
        //       ������� ������ � tp.living.content.
        errorCL = clEnqueueReadBuffer(
            commandQueueCL,
            livingCL,
            CL_TRUE,
            0,
            memsizeLiving,
            tp.living.content,
            0, nullptr, nullptr
        );
        oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

        // ������������ ���-��
        float allZoneCount = 0.0f;
        pd::zoneLivingCount_t zoneCount = {};
        // �������� �� ���� �������
        static const size_t LG = pd::LIVING_GRID * pd::LIVING_GRID * pd::LIVING_GRID;
        for (size_t i = 0; i < LG; ++i) {
            // � ������ ������ ���������� �� ����� LIVING_CELL ������
            for (size_t k = 0; k < pd::LIVING_CELL; ++k) {
                // ���������� �� ������ ������������� �� LIFE_CYCLE
                for (size_t l = static_cast< size_t >( pd::LC_EMBRYO);
                     l < static_cast< size_t >( pd::LC_last );  ++l
                ) {
                    const pd::portionLiving_t& p = tp.living.content[i][k][l];
                    const pd::CODE_LIVING code = p.code;
                    assert( ((code >= pd::CL_NONE) && (code < pd::CL_last))
                        && "��� ����� �� ���������. ��������, ������ ��� ������������� �������." );
                    // ��������� (������������� ���� ����)
                    zoneCount[ code ][ l ].all += p.count;
                    allZoneCount += p.count;
                }
            }
        }

        // ���-�� ������ ������ ���� ������ � ���������
        std::memset( zoneCountComplete, false, memsizeZoneCountComplete );
        bool allComplete = true;
        for (size_t code = 0; code < pd::LIVING_COUNT; ++code) {
            for (size_t l = static_cast< size_t >( pd::LC_EMBRYO);
                 l < static_cast< size_t >( pd::LC_last );  ++l
            ) {
                const float desireCount = zoneDesireCount[ code ][ l ].all;
                const float count       = zoneCount[ code ][ l ].all;
                // # �� ���������� ����������� �� �����.
                auto& zcc = zoneCountComplete[ code ][ l ];
                zcc.all = (desireCount <= count * 1.1f);
                if ( !zcc.all ) {
                    allComplete = false;
                    break;
                }
            }
            if ( !allComplete ) {
                // true ��� �� �����
                break;
            }

        } // for (size_t code

        if ( allComplete ) {
            // ������� ��������, ���������� ������ �����. ��������
            break;
        }

        errorCL = clEnqueueNDRangeKernel(
            commandQueueCL,
            kernel,
            GRID_WORK_DIM,
            nullptr,
            GRID_GLOBAL_WORK_SIZE,
            nullptr,
            0, nullptr, nullptr
        );
        oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );

        // �������������
        /* - (�������������� � ������ �����)
        errorCL = clFinish( commandQueueCL );
        oclCheckErrorEX( errorCL, CL_SUCCESS, &fnErrorCL );
        */

        // ���������
        // (�������� � ������ �����)

        ++iteration;

#ifdef _DEBUG
        //std::cout << ".";
        // ���������� ��������� ���������
        static const size_t W = 50;
        static const size_t PRECISION_DIGIT = 0;
        static const float PRECISION_POW =
            boost::math::pow< PRECISION_DIGIT >( 10 );
        if (iteration % W == 0) {
            const float percent = std::floor(
                allZoneCount / allZoneDesireCount * 100.0f * PRECISION_POW
            ) / PRECISION_POW;
            std::ostringstream ss;
            ss << std::fixed << std::setprecision( PRECISION_DIGIT ) <<
                " " << percent << " %";
            std::cout << ss.str() <<
                std::string( ss.str().length(), '\b');
        }
#endif
    } // for ( ; ; )

#ifdef _DEBUG
    std::cout << " ��          " << std::endl;
#endif
}
#endif


} // porte
