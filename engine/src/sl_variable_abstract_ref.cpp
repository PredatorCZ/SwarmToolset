#include "sl_variable_abstract_ref.hpp"
#include "abstract.hpp"
#include "abstract_manager.hpp"

bool SLVariableAbstractRef::FromString(const std::string &text,
                                       int ignoreLock) {
  if (isLocked == 2 && !ignoreLock) {
    throw "Variable locked - cannot assign by validation\n";
  }

  if (referenceState) {
    AbstractManager::Get()->RemoveReference(this);
    reference = 0;
    referenceState = 0;
  }

  if (text == "_NULL_") {
    return false;
  }

  referenceState = 1;
  guid = text;
  reference = AbstractManager::Get()->GetAbstractFromGUID(guid);

  if (reference) {
    referenceNodeToThis = reference->AddReferee(*this);
    referenceState = 2;
  } else {
    globalReferenceNodeToThis = AbstractManager::Get()->AddAbstractRef(*this);
  }

  return true;
}

SLVariable *SLVariableAbstractRef::Clone() {
  SLVariableAbstractRef *clone = new SLVariableAbstractRef(*this);
  clone->isLocked = isLocked;
  clone->field_26 = field_26;

  return clone;
}

SLVariableAbstractRef::SLVariableAbstractRef(
    const SLVariableAbstractRef &other) {
  if (&other == this) {
    return;
  }

  if (referenceState) {
    AbstractManager::Get()->RemoveReference(this);
  }

  reference = other.reference;
  name = other.name;
  guid = other.guid;
  referenceState = other.referenceState;
  field_26 = other.field_26;

  if (reference) {
    referenceNodeToThis = reference->AddReferee(*this);
    return;
  }

  if (referenceState) {
    this->globalReferenceNodeToThis = AbstractManager::Get()->CopyAbstractRef(
        other, *this, other.globalReferenceNodeToThis);
  }
}

void SLVariableAbstractRef::SetGUIDFromReference() {
  guid = *reference->GetGUID();
}

void SLVariableAbstractRef::SetReference(Abstract *abstract) {
  reference = abstract;
  referenceState = 2;
  referenceNodeToThis = abstract->referencedBy.emplace(this).first;

  field_34();
}
