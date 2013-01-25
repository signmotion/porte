// @require ���������� �� "include".


/**
* �������������� �������� ������� ������� � ����� ���������� �������.
*
* @see �������. � starsystem::l0::EngineHybrid::pulse().
* @see ���� direct(), relative(), fix().
*
* #i NVIDIA 8800GTS �������� ������ � float.
*/




// @see world/dungeon-crawl/star-system/0/set/structure.h
__kernel void begin(
    __global const aboutStarSystem_t*  ass,      // 0
    __global aboutAsteroid_t*          aa,       // 1
    __global aboutPlanet_t*            ap,       // 2
    __global aboutStar_t*              as,       // 3
    const real_t                       timestep  // 4
) {
    // # ���� �������� ������� ������. ���������, ��� ���-�� ���������
    //   � ������� - ������.
    const uint i = get_global_id( 0 );

    /* @test
    if (i == 0) {
        printf( "aboutStarSystem_t %i\n", sizeof( aboutStarSystem_t ) );
        printf( "aboutAsteroid_t %i\n", sizeof( aboutAsteroid_t ) );
        printf( "aboutPlanet_t %i\n", sizeof( aboutPlanet_t ) );
        printf( "aboutStar_t %i\n", sizeof( aboutStar_t ) );
        printf( "real_t %i\n", sizeof( real_t ) );
        printf( "real2_t %i\n", sizeof( real2_t ) );
        printf( "real3_t %i\n", sizeof( real3_t ) );
        printf( "real4_t %i\n", sizeof( real4_t ) );
        printf( "characteristicAsteroid_t %i\n", sizeof( characteristicAsteroid_t ) );
        printf( "bool %i\n", sizeof( bool ) );
        printf( "eventTwo_t %i\n", sizeof( eventTwo_t ) );
        printf( "pointerElement_t %i\n", sizeof( pointerElement_t ) );
        printf( "enum EVENT %i\n", sizeof( enum EVENT ) );
    }
    return;
    */



    if (i >= ASTEROID_COUNT) {
        printf( "(!) Index %d / %d out of range for asteroid.\n",  i,  ASTEROID_COUNT - 1 );
        return;
    }

    if ( absentAsteroid( &aa[ i ] ) ) {
        return;
    }


    __global aboutAsteroid_t* element = &aa[ i ];
    __global emitterEvent_t* ee = &element->emitterEvent;
#ifdef __DEBUG
    if ( !betweenInteger( ee->waldo, 0, EMITTER_EVENT_COUNT - 1 ) ) {
        printf( "(?) Asteroid %d is not initialized or it memory is overfilled. Waldo = %i.\n",
            element->uid, ee->waldo );
    }
#endif


    // �������� �������
    /* - optimize ���������� �������� ������.
    for (int w = ee->waldo; w > 0; --w) {
        ee->content[ w ].uid = E_NONE;
    }
    */

    // �������� ������
    ee->waldo = 0;

}
