#include <memory>

struct StateComponent {
    enum ClickState { DEFAULT = 0, IS_CLICKED = 1 };
    ClickState clicked;

    StateComponent();
};

using StateComponentPtr = std::shared_ptr<StateComponent>;