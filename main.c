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
	int i;
  rnd_Seed(time(NULL), 33);
  PtlSystem *PtSys[10];
  for(i=0;i<10;i++) {
	PtSys[i] = NewPtlSystem(rnd_R32n(0,800),rnd_R32n(0,600));
	PtSys[i]->Add(PtSys[i]);
  }
  SB_Init(800, 600, "Particle");
  SB_Image *mvr = NewSBImage("ship.bmp");
  while (!SB_Done()) {
    SB_Clear(RGB_Black);
    for(i=0;i<10;i++) {
		PtSys[i]->Add(PtSys[i]);
		update_draw(PtSys[i], mvr);
		PtSys[i]->Delete(PtSys[i]);
    }
    SB_Update();
    SB_Delay(16);
  }
  for(i=0;i<10;i++) {
	PtSys[i]->Destroy(PtSys[i]);
  }
  mvr->Destroy(mvr);
  SB_Fini();
  return 0;
}
