#ifndef PLATFORMER_GAME_SPRITES_HPP
#define PLATFORMER_GAME_SPRITES_HPP

#include <string>

namespace constants
{
    [[maybe_unused]] const std::string IDLE_SPRITE_ID = "mario_idle";
    [[maybe_unused]] const std::string WALK_SPRITE_ID = "mario_walk";
    [[maybe_unused]] const std::string JUMP_SPRITE_ID = "mario_jump";
    [[maybe_unused]] const std::string IDLE_STAR_SPRITE_ID = "mario_idle_star";
    [[maybe_unused]] const std::string WALK_STAR_SPRITE_ID = "mario_walk_star";
    [[maybe_unused]] const std::string JUMP_STAR_SPRITE_ID = "mario_jump_star";

    [[maybe_unused]] const std::string HORIZONTAL_FLIP_SUFFIX = "_x_flip";
} // namespace constants

#endif //PLATFORMER_GAME_SPRITES_HPP
