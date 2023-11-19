#include <SDL2/SDL.h>
#include <map>
#include "Command.h"

namespace {
std::map<Command, std::string> description;
std::map<Command, std::string> keyName;
std::map<int, Command> commandForKeycode = {{SDLK_e, Command::SAY_HELLO}};
const uint64_t ONE = 1;
}  // namespace

const Command Command::NONE(0, "Do nothing");
const Command Command::SAY_HELLO(ONE << 0, "Output text to stdo");
#include <iostream>
Command::Command(int keycode) {
    auto it = commandForKeycode.find(keycode);
    if (it != commandForKeycode.end()) {
        *this = it->second;
        std::cout << it->second.index_ << std::endl;
    }
}
Command::Command(uint64_t index, std::string const &text) : index_(index) {
    if (!text.empty()) description[*this] = text;
}

bool Command::operator==(Command const &other) const {
    return index_ == other.index_;
}

bool Command::operator<(Command const &other) const {
    return index_ < other.index_;
}

bool Command::has(Command const &command) const {
    return (index_ & command.index_);
}