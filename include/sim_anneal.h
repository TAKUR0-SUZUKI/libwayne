#ifdef __cplusplus
extern "C" {
#endif
#ifndef _SIM_ANNEAL_H
#define _SIM_ANNEAL_H

#include <math.h>
#include "misc.h"

typedef double (*pScoreFunc)(const foint); // user-provided function pointer that scores a solution

// User-provided functions of this type are called both to incrementally change the current solution to a new one,
// and later to indicate whether the new solution was accepted.
// In the former case, a new solution should be generated iff moveOrAccept is actually true, and return the resulting solution.
// In the latter case, moveOrAccept is true iff the move was accepted, and the user's code should act accordingly and return
// either the unchanged solution or the newly accepted one.
typedef foint (*pSolutionFunc)(Boolean moveOrAccept, const foint solution);

#define PBAD_CIRC_BUF 1000

typedef struct _sim_anneal {
    int iter, maxIters, direction, pBadBufPos, pBadBufLen;
    double temperature, tInitial, tDecay, pBadBuf[PBAD_CIRC_BUF], pBadSum;
    foint currentSolution;
    pSolutionFunc Move, Accept;
    pScoreFunc Score;
} SIM_ANNEAL;

// direction < 0 to minimize, > 0 to maximize
SIM_ANNEAL *SimAnnealAlloc(double direction, foint initSol, pSolutionFunc Move, pScoreFunc, pSolutionFunc Accept, int maxIters);
Boolean SimAnnealSetSchedule(SIM_ANNEAL *sa, double tInitial, double tDecay);
void SimAnnealAutoSchedule(SIM_ANNEAL *sa); // to automatically create schedule
int SimAnnealRun(SIM_ANNEAL *sa); // returns >0 if success, 0 if not done and can continue, <0 if error
foint SimAnnealSol(SIM_ANNEAL *sa);
void SimAnnealFree(SIM_ANNEAL *sa);

#endif  /* _SIM_ANNEAL_H */

#ifdef __cplusplus
} // end extern "C"
#endif
