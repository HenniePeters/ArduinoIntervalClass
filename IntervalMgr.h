#ifndef INTERVALMGR_H
#define INTERVALMGR_H
//-------------------------------------------------------------------------------
#define INTERVAL_MAX_HANDLERS 10 // set the maximumum array size
//-------------------------------------------------------------------------------
// compile time check
#if INTERVAL_MAX_HANDLERS <= 0
#error "INTERVAL_MAX_HANDLERS must be > 0"
#endif
//-------------------------------------------------------------------------------
// compile time check
#if INTERVAL_MAX_HANDLERS > 50 
#warning "Large INTERVAL_MAX_HANDLERS may consume significant RAM"
#endif
//-------------------------------------------------------------------------------
#include <stdint.h>
#include "Arduino.h"
//-------------------------------------------------------------------------------
class Handler {
    public:
        using Callback = void ( * )();

        Handler();
        void set( Callback func, uint32_t interval, uint32_t now );
        void poll(uint32_t now);
        void disable();
        bool isEnabled() const;

    private:
        Callback callback_;
        uint32_t interval_;
        uint32_t oldTime_;
};
//-------------------------------------------------------------------------------
class IntervalManager {
    public:
        IntervalManager( void );        
        void set( int index, Handler::Callback func, uint32_t interval, uint32_t now );
        void loop();
    private:
        Handler handlers_[INTERVAL_MAX_HANDLERS];
};
//-------------------------------------------------------------------------------
#endif // INTERVALMGR_H
