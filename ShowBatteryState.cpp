#include "ShowBatteryState.h"


ShowBatteryState::ShowBatteryState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
}
void ShowBatteryState::start(){ //State switched to this
}
void ShowBatteryState::run(){ //Loop
  col->displayBatteryColors();
}
void ShowBatteryState::stop(){ //State leaving this
}