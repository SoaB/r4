#include "particleSystem.h"
#include "rnd.h"
#include "sgi.h"
#include "v2d.h"
#include <stdlib.h>
#include <time.h>

void update_draw(PtlSystem *p, sgi_Image *d) {
  Particle *current = p->Head;
  if (p->Head == NULL)
    return;
  for (; current != NULL; current = current->next) {
    current->Update(current);
    if (!current->IsDead(current))
      d->Draw(d, (int)(current->location.x), (int)(current->location.y), 0);
  }
}
int main(int argc, char *argv[]) {
  PtlSystem *PtSys = NewPtlSystem(400, 300);
  rnd_Seed(time(NULL), 33);
  sgi_Init(800, 600, "Particle");
  sgi_Image *mvr = NewSgiImage("dot.bmp");
  while (!sgi_Done()) {
    sgi_Clear(RGB_Black);
    PtSys->Add(PtSys);
    update_draw(PtSys, mvr);
    PtSys->Delete(PtSys);
    sgi_Update();
    sgi_Delay(16);
  }
  PtSys->Destroy(PtSys);
  mvr->Destroy(mvr);
  sgi_Fini();
  return 0;
}
