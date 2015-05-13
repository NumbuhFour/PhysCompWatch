#include "FlashlightState.h"


FlashlightState::FlashlightState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
}
void FlashlightState::start(){ //State switched to this
    previousBrightness = col->getStrength();
    col->setStrength(1);
    col->setColors(127, 255,255,255);
    col->pushColors();
}
void FlashlightState::run(){ //Loop
}
void FlashlightState::stop(){ //State leaving this
    col->setStrength(previousBrightness);
}