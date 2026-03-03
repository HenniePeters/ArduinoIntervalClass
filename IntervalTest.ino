//-------------------------------------------------------------------------------
#include "IntervalMgr.h"
IntervalManager intervals; // INTERVAL_MAX_HANDLERS defined in IntervalMgr.h (default 10)
//-------------------------------------------------------------------------------
void flash( void ) { // flash will be executed every 50ms, it will turn on the LED during 50ms every second
    static uint8_t count = 0;
    digitalWrite( LED_BUILTIN, ( count == 0 ) ? HIGH : LOW );
    count = ( count + 1 ) % 20;
}
//-------------------------------------------------------------------------------
void dummy( void ) {
    //
}
//-------------------------------------------------------------------------------
void test0( void ) {
    Serial.print( "0" );
    Serial.flush();
}
//-------------------------------------------------------------------------------
void test1( void ) {
    Serial.print( "1" );
    Serial.flush();
}
//-------------------------------------------------------------------------------
void test2( void ) {
    Serial.println( "2" );
    Serial.flush();
}
//-------------------------------------------------------------------------------
void test3( void ) {
    intervals.set( 2, test2, 5000, millis() ); // raise interval for test2 from 1000 to 5000ms
    intervals.set( 3, nullptr, 0, 0 );         // disable itself on the first shot
    Serial.println( "3" );
    Serial.flush();
}
//-------------------------------------------------------------------------------
void oneshot( void ) {
    intervals.set( 4, nullptr, 0, 0 ); // disable itself on the first shot
    Serial.print( " oneshot " );
    Serial.flush();
}
//-------------------------------------------------------------------------------
void setup( void ) {
    Serial.begin( 115200 );
    pinMode( LED_BUILTIN, OUTPUT );
    uint32_t now = millis();
    //          index functie ms vanaf
    intervals.set( 0, test0, 100, now );  // test0 will be executed every 100 ms
    intervals.set( 1, test1, 333, now );  // test1 will be executed every 333 ms
    intervals.set( 2, test2, 1000, now ); // test2 will be executed every 1000 ms
    intervals.set( 3, test3, 5000, now ); // test3 will be executed after 5000 ms, changes the timing of test2 and disables itself
    intervals.set( 4, oneshot, 4000, now ); // oneshot will be executed after 4000 ms and it will disable itself in the callback
    intervals.set( 5, flash, 50, now );
    // intervals.set( 6, dummy,   1000, now );
    // intervals.set( 7, dummy,   1000, now );
    // intervals.set( 8, dummy,   1000, now );
    // intervals.set( 9, dummy,   1000, now );
}
//-------------------------------------------------------------------------------
void loop( void ) {
    intervals.loop();
}
//-------------------------------------------------------------------------------
