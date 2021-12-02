#ifndef __PARTICLES__H__
#define __PARTICLES__H__
#include "rnd.h"
#include "v2d.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct Particle {
  Vec2D location;
  Vec2D velocity;
  Vec2D acceleration;
  float lifespan;
  void (*Update)(struct Particle *pl);
  void (*Destroy)(struct Particle *pl);
  int (*IsDead)(struct Particle *pl);
  struct Particle *next;
} Particle;

static void _update_particle(Particle *pl) {
  pl->velocity = V2D_Add(pl->velocity, pl->acceleration);
  pl->location = V2D_Add(pl->location, pl->velocity);
  pl->lifespan -= 2.0;
}
static void _destroy_particle(Particle *pl) {
  if (pl != NULL) {
    free(pl);
    pl = NULL;
  }
}
static int _is_dead_particle(Particle *pl) {
  if (pl->lifespan < 0.0) {
    return 1;
  }
  return 0;
}
Particle *NewParticle(float x, float y) {
  Particle *pl = (Particle *)malloc(sizeof(Particle));
  pl->location = V2D_Set(x, y);
  pl->acceleration = V2D_Set(0, rnd_Fmn(0, 0.05));
  pl->velocity = V2D_Set(rnd_Fmn(-1, 1), rnd_Fmn(-2, 0));
  pl->lifespan = 255.0;
  pl->Update = &_update_particle;
  pl->Destroy = &_destroy_particle;
  pl->IsDead = &_is_dead_particle;
  pl->next = NULL;
  return pl;
}
#endif