
#include "move_ordering.h"

int mvvlvaScore[12][12];
void initMvvLva(){
    for (int attacker = P; attacker <= k; attacker++){
        for (int victim = P; victim <= k; victim++){
            mvvlvaScore[victim][attacker] = victimScore[victim] + 6 - (victimScore[attacker])/100;
        }
    }
}

