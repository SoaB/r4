#include "particle.h"
#include "particleSystem.h"
#include "rnd.h"
#include "SB.h"
#include "v2d.h"
#include <stdlib.h>
#include <time.h>

void update_draw(PtlSystem *p, SB_Image *d) {
  Particle *current = p->Head;
  if (p->Head == NULL)
    return;
  for (; current != NULL; current = current->next) {
    current->Update(current);
    if (!current->IsDead(current))
      d->Draw(d, (int)(current->location.x), (int)(current->location.y),
              current->dir);
  }
}
int main(int argc, char *argv[]) {
  PtlSystem *PtSys = NewPtlSystem(400, 300);
  PtSys->Add(PtSys);
  rnd_Seed(time(NULL), 33);
  SB_Init(800, 600, "Particle");
  SB_Image *mvr = NewSBImage("ship.bmp");
  while (!SB_Done()) {
    SB_Clear(RGB_Black);
    PtSys->Add(PtSys);
    update_draw(PtSys, mvr);
    PtSys->Delete(PtSys);
    SB_Update();
    SB_Delay(16);
  }
  PtSys->Destroy(PtSys);
  mvr->Destroy(mvr);
  SB_Fini();
  return 0;
}
