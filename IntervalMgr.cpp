#include "IntervalMgr.h"
//-------------------------------------------------------------------------------
Handler::Handler() : callback_( nullptr ), interval_( 0 ), oldTime_( 0 ) {}
//-------------------------------------------------------------------------------
void Handler::set( Callback func, uint32_t interval, uint32_t now ) {
    callback_ = func;
    interval_ = interval;
    oldTime_ = now;
}
//-------------------------------------------------------------------------------
void Handler::poll(uint32_t now) {
    if( callback_ != nullptr && now - oldTime_ >= interval_ ) {
        oldTime_ += interval_;
        callback_();
    }
}
//-------------------------------------------------------------------------------
bool Handler::isEnabled() const {
    return( callback_ != nullptr && interval_ > 0 );
}
//-------------------------------------------------------------------------------
void Handler::disable() {
    callback_ = nullptr;
}
//-------------------------------------------------------------------------------
IntervalManager::IntervalManager( void ) {
    for( int i = 0; i < INTERVAL_MAX_HANDLERS; i++ ) {
        handlers_[i].disable();
    }
}
//-------------------------------------------------------------------------------
void IntervalManager::set( int index, Handler::Callback func, uint32_t interval, uint32_t time ) {
    if( index < 0 || index >= INTERVAL_MAX_HANDLERS ) return;
    handlers_[index].set( func, interval, time );
}
//-------------------------------------------------------------------------------
void IntervalManager::loop() {
    uint32_t now = millis();
    for( int i = 0; i < INTERVAL_MAX_HANDLERS; i++ ) {
        if( handlers_[i].isEnabled() ) {
            handlers_[i].poll(now);
        }
    }
}
//-------------------------------------------------------------------------------
