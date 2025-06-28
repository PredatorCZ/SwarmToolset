#pragma once
#include <cstdint>
#include <list>

struct Processable {
  virtual ~Processable();
  virtual void SetActiveStatus(bool /*isActive*/) {}
  virtual void func_8() {}
  virtual void Process();
  virtual void field_10() {}

  void SetActive(bool isActive);

  bool active;
  bool field_5;
  bool isDead;
  int32_t field_8;
  bool hasSessionListNode;
  std::list<Processable>::iterator *sessionListIter;
};
