#ifndef EAEB_H
#define EAEB_H

#include "constants.h"
#include "nxt_interface.h"
#include "controller.h"
#include "aeb.h"
#include "abs.h"

typedef enum {
	STATE_NOT_ACTIVATED,
	STATE_BRAKING,
	STATE_TURNING,
	STATE_STRAIGHTENING
}EAEB_STATES;

S8 EAEB_flag = OFF;

int calculateTurnDegrees(float overlap, float distToImpact);

void runEAEB();

#endif
