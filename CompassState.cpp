#include "CompassState.h"


CompassState::CompassState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
  btn = lw->getButtons();
}
void CompassState::start(){ //State switched to this
}
void CompassState::run(){ //Loop
}
void CompassState::stop(){ //State leaving this
}