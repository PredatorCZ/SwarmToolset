#pragma once
#include "game_object.hpp"
#include "positionable.hpp"

struct WorldObjectContext;
struct WorldObjectCollision;
struct IncomingDamage;
struct Collider;

struct WorldObject : GameObject, Positionable {
  virtual void GetDirection();
  virtual void SetDirection(Vector * direction);
  virtual void field_28();
  virtual void field_2C();
  virtual void field_30();
  virtual void field_34();
  virtual void field_38();
  virtual void field_3C();
  virtual void field_40();
  virtual void ApplyDamage(IncomingDamage &dmg);
  virtual void field_48(WorldObject &obj);
  virtual void field_4C();
  virtual void field_50();

  Vector *GetPosition() override;

  void _949700();
  bool _949860(Collider &collider);

  WorldObjectContext *debugContext;
  WorldObjectContext *workingContext;
  WorldObjectContext *context;
  WorldObjectCollision *collision;
  std::list<WorldObject>::iterator debugContextObjectsIter;
  std::list<WorldObject>::iterator debugContextCollisionObjectsIter;
  SLVariableSet *quicksave;
  SLVariableAbstractRef *sl_pContext;
};
