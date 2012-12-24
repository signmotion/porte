#pragma once

#include "../../configure.h"
#include "AEngine.h"
#include <typelib/typelib.h>
#include <portulan/portulan.h>
#include <limits>
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/date_time/local_time/local_time.hpp>


namespace porte {


/**
* ����� ����� ��� �������� ������� ��� "���������" ���������� (3D-����)
* ��� ������������� ������������� booster-��������.
*
* @template P  ��������, � ������� �������� ������.
* @template R  � ����� ��������� ������������ �����.
*
* @see ������ "portulan" > https://github.com/savdalion/portulan
*/
template< class P, typename R >
class EngineWithoutBooster : public AEngine {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< EngineWithoutBooster >  Ptr;
    typedef std::unique_ptr< EngineWithoutBooster >  UPtr;


    typedef P  portulan_t;
    typedef R  real_t;




public:
    inline EngineWithoutBooster( R timestep ) :
        mPortulan( nullptr ),
        mPulselive( 0 ),
        mTimestep( timestep ),
        mTimelive( 0 )
    {
        assert( (mTimestep >= 1.0)
            && "��� ������� �� ����� ���� ������ �������." );
    }



    inline EngineWithoutBooster( std::unique_ptr< portulan_t >  p,  R timestep ) :
        mPortulan( std::move( p ) ),
        mTimestep( timestep )
    {
        assert( p && "����� �� ������� (�������� �� ������)." );
        assert( (mTimestep >= 1.0)
            && "��� ������� �� ����� ���� ������ �������." );
    }




    /**
    * ��������� ������� ������� � ������.
    * 
    * @param extentPortulan ������������ ���������. ���� �� �������,
    *        ����������� � ������� extent().
    */
    virtual inline void incarnate( std::unique_ptr< portulan_t >  p,  real_t extentPortulan = 0 ) {
        assert( p && "�������� �� ������." );
        assert( (extentPortulan >= 0)
            && "������������ ��������� �� ����� ���� ������ 0." );

        mPortulan = std::move( p );
        mExtent = typelib::empty( extentPortulan ) ? extent() : extentPortulan;
    }



    inline long long pulselive() const {
        return mPulselive;
    }



    inline real_t timestep() const {
        return mTimestep;
    }



    inline void timestep( real_t timestep ) {
        mTimestep = timestep;
    }



    inline double timelive() const {
        return mTimelive;
    }



    /**
    * @return ������������ ���������.
    *         ����� ������ ��������� ������������, ���� ��� ���
    *         �� ������� � 'mExtent'.
    */
    virtual real_t extent() = 0;



    inline portulan_t const*  portulan() const {
        return mPortulan.get();
    }


    inline portulan_t*  portulan() {
        return mPortulan.get();
    }




    /**
    * ����� ��������� ������� ��������� ��������� (�����) �������.
    *
    * @param ���-�� ������� (���������� ��������� ����������), �������
    *        ����������� ������ ������, ��� ������� ���������.
    *
    * @see operator>>()
    */
    inline void operator()( int n ) {
        assert( (n != 0) && "����� � n == 0 �� ����� ������." );
        assert( (n > 0) && "������ ����� �������� ������ � ������������� �������. @todo ..." );

        pulse( n );
    }




    /**
    * @alias operator()( portulan, 1 )
    *
    * ����-�� ����� ������ �������� ��������� ����. ���� �����?
    *   engine << 1;
    */
    inline EngineWithoutBooster& operator<<( int n ) {
        ( *this )( n );
        return *this;
    }




protected:
    /**
    * ��������� ����� �������.
    */
    virtual void pulse( int n ) = 0;




protected:
    /**
    * ��������, � ������� �������� ������.
    */
    std::unique_ptr< portulan_t >  mPortulan;

    /**
    * ������� ������� ������� �������.
    */
    long long mPulselive;

    /**
    * �����, ������� �������� �� 1 �����.
    * ����������� � ��������.
    */
    real_t mTimestep;

    /**
    * ������� ������� ������� �������.
    * ���� ��� ������� �� �������� �������, ����� ����� =
    * = ��� * ���������� �������� �������.
    *
    * @todo fine? �� ������� ����������� ���������� ��������.
    */
    double mTimelive;

    /**
    * ������������ ���������.
    *
    * @see extent()
    */
    real_t mExtent;
};




} // porte
