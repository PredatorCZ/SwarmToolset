#include "abstract_manager.hpp"
#include "abstract.hpp"
#include "sl_variable_abstract_ref.hpp"

void AbstractManager::LinkAbstract(Abstract *abstract) {

  if (abstract->doNotDelete) {
    return;
  }

  for (SLVariableAbstractRef *a : abstract->referencedBy) {
    a->SetGUIDFromReference();
  }

  if (field_20)
    delete field_20;

  field_20 = 0;
  field_24 = 0;
  field_28 = 0;

  auto lbound = refs.lower_bound(*abstract->GetGUID());
  auto hbound = refs.upper_bound(*abstract->GetGUID());

  for (auto it = lbound; it != hbound; it++) {
    it->second->SetReference(abstract);
  }

  refs.erase(*abstract->GetGUID());
}
