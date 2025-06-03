#include "Component.h"

Component::Component(std::weak_ptr<GameObject> associated) : associated(associated) {}

Component::~Component() {}

void Component::Start() {
    // Por padrão, não faz nada. Pode ser sobrescrito.
}
