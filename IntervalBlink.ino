//-------------------------------------------------------------------------------
// NON-BLOCKING-BLINK
//-------------------------------------------------------------------------------
#include "IntervalMgr.h"
// INTERVAL_MAX_HANDLERS defined in IntervalMgr.h (default 10)
// In this sketch we are using 1 handler from 10 available
IntervalManager intervals;
//-------------------------------------------------------------------------------
void flash( void ) { // non blocking function to flash the built in led, call every 50ms
    static uint8_t count = 0;
    digitalWrite( LED_BUILTIN, ( count == 0 ) ? HIGH : LOW );
    count = ( count + 1 ) % 20; // reset the counter when it reaches 20 ( 20x 50ms => 1 second )
}
//-------------------------------------------------------------------------------
void setup( void ) {
    Serial.begin( 115200 );
    pinMode( LED_BUILTIN, OUTPUT );
    uint32_t now = millis();
    //         index function ms from
    intervals.set( 0, flash, 50, now ); // The flash function will be executed every 50ms
    // intervals.set( 1, dummy, 1000, now ); // call up to 10 functions with custom intervals
    //  ...
    // intervals.set( 9, dummy, 10000, now ); // for more than 10, modify INTERVAL_MAX_HANDLERS in IntervalMgr.h
}
//-------------------------------------------------------------------------------
void loop( void ) {
    intervals.loop();
}
//-------------------------------------------------------------------------------
