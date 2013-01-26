// @require ���������� �� "include".


/**
* ��������� �������������� �������� ������� ������� �������� ��������.
*
* @see �������. � starsystem::l0::EngineHybrid::pulse().
* @see ���� direct(), relative().
*
* #i NVIDIA 8800GTS �������� ������ � float.
*/




// @see world/dungeon-crawl/star-system/0/set/structure.h
__kernel void fix(
    __global const aboutStarSystem_t*  ass,      // 0
    __global aboutAsteroid_t*          aa,       // 1
    __global aboutPlanet_t*            ap,       // 2
    __global aboutStar_t*              as,       // 3
    const real_t                       timestep  // 4
) {
    // # ���� �������� ������� ������. ���������, ��� ���-�� ���������
    //   � ������� - ������.
    const uint i = get_global_id( 0 );

    if (i >= ASTEROID_COUNT) {
        //printf( "(!) Index %d / %d out of range for asteroid.\n",  i,  ASTEROID_COUNT - 1 );
        return;
    }

    if ( absentAsteroid( &aa[ i ] ) ) {
        return;
    }


    __global aboutAsteroid_t* element = &aa[ i ];
    const __global emitterEvent_t* ee = &element->emitterEvent;
#ifdef __DEBUG
    if ( !betweenInteger( ee->waldo, 0, EMITTER_EVENT_COUNT - 1 ) ) {
        //printf( "(?) Asteroid %d is not initialized or it memory is overfilled. Waldo = %i.\n",
        //    element->uid, ee->waldo );
    }
#endif

    int w = ee->waldo;


    // ������ �������������� �. � ����������� �� �������
    // # �� ���������� �� ������� �������: ���� ��� ������-��
    //   ��������� � ����� ��������.
    for (int w = ee->waldo - 1; w >= 0; --w) {
        __global const eventTwo_t* e = &ee->content[ w ];
        const enum EVENT uid = e->uid;
        // # ����������� �������� enum Event.
        switch ( uid ) {
            case E_NONE :
                // ������ ������, ������ �������
                // # � ������ �� ������ �����������.
#ifdef __DEBUG
                //printf( "(?) fix() Empty event for asteroid %d. Decrease perfomance.\n", element->uid );
#endif
                break;

            case E_COLLISION :
                // # ��������� �������.
                // # ������� ������������� ��� ����������.
                break;

            case E_CHANGE_COORD :
                element->today.coord.x += e->fReal[ 0 ];
                element->today.coord.y += e->fReal[ 1 ];
                element->today.coord.z += e->fReal[ 2 ];
#ifdef __DEBUG
                assertReal( element->today.coord.x, "(!) Overfill coord X for asteroid.\n" );
                assertReal( element->today.coord.y, "(!) Overfill coord Y for asteroid.\n" );
                assertReal( element->today.coord.z, "(!) Overfill coord Z for asteroid.\n" );
#endif
                break;

            case E_CHANGE_MASS :
                element->today.mass += e->fReal[ 1 ];
#ifdef __DEBUG
                assertReal( element->today.mass, "(!) Overfill mass for asteroid.\n" );
#endif
                break;

            case E_CHANGE_SIZE :
#ifdef __DEBUG
/*
                if ( !testReal( element->today.size[ 0 ] + e->fReal[ 3 ] )
                  || !testReal( element->today.size[ 1 ] + e->fReal[ 4 ] )
                  || !testReal( element->today.size[ 2 ] + e->fReal[ 5 ] )
                ) {
                    printf( "Asteroid %d before change size.\n"
                        "  Coord %e %e %e\n"
                        "  Velocity %e %e %e\n"
                        "  Size %e %e %e\n"
                        "",
                        element->uid,
                        element->today.coord.x,
                        element->today.coord.y,
                        element->today.coord.z,
                        element->today.velocity[ 0 ],
                        element->today.velocity[ 1 ],
                        element->today.velocity[ 2 ],
                        element->today.size[ 0 ],
                        element->today.size[ 1 ],
                        element->today.size[ 2 ]
                    );
                }
*/
#endif
                element->today.size.x += e->fReal[ 3 ];
                element->today.size.y += e->fReal[ 4 ];
                element->today.size.z += e->fReal[ 5 ];
#ifdef __DEBUG
                assertReal( element->today.size.x, "(!) Overfill size X for asteroid.\n" );
                assertReal( element->today.size.y, "(!) Overfill size Y for asteroid.\n" );
                assertReal( element->today.size.z, "(!) Overfill size Z for asteroid.\n" );
                //printf( "fix() Change size asteroid %d.  %e x %e x %e\n",
                //    element->uid,  e->fReal[ 3 ],  e->fReal[ 4 ],  e->fReal[ 5 ] );
#endif
                break;

            case E_CHANGE_TEMPERATURE :
                element->today.temperature += e->fReal[ 1 ];
                break;

            case E_CHANGE_VELOCITY :
                element->today.velocity.x += e->fReal[ 0 ];
                element->today.velocity.y += e->fReal[ 1 ];
                element->today.velocity.z += e->fReal[ 2 ];
#ifdef __DEBUG
                assertReal( element->today.velocity.x, "(!) Overfill velocity X for asteroid.\n" );
                assertReal( element->today.velocity.y, "(!) Overfill velocity Y for asteroid.\n" );
                assertReal( element->today.velocity.z, "(!) Overfill velocity Z for asteroid.\n" );
#endif
                break;

            case E_CRUSH_N :
                // @todo ...
                break;

            case E_DESTROY :
#ifdef __DEBUG
                //printf( "fix() Destroy asteroid %d.\n", element->uid );
#endif
                element->today.live = false;
                break;

            case E_GRAVITY :
                // # �������� ������� ���, ����� ������������� ��������������
                //   �� ������ ��������.
                // # ������� ������������� ��� ����������.
                break;

            case E_IMPACT_ACCELERATION :
                // # ������� ������������� ��� ����������.
                break;

            case E_IMPACT_FORCE :
                // # ������� ������������� ��� ����������.
                break;

            case E_RADIATION :
                // # ������� ������������� ��� ����������.
                break;

            case E_last :
                // ������ ������ ������� �� ���������� �����������
                // # �� ������ �����������.
                break;

            //default :
                // # ���� �������� �� ������.
#ifdef __DEBUG
                //printf( "(!) fix() Undefined event for asteroid %d.\n", element->uid );
#endif
        } // switch

    } // for (int w = ...

}
