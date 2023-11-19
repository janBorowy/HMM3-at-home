#pragma once
#include <cstdint>
#include <string>
class Command {
    Command(uint64_t index, std::string const &description);

   public:
    static const Command NONE;
    static const Command SAY_HELLO;

    Command() = default;
    explicit Command(int keyCode);
    uint64_t index_;
    bool operator==(Command const &other) const;
    bool operator<(Command const &other) const;
    bool has(Command const &command) const;
};