#ifndef PLATFORMER_GAME_COINCOUNTER_HPP
#define PLATFORMER_GAME_COINCOUNTER_HPP

#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "Color.hpp"
#include "Transform.hpp"

namespace PlatformerGame {
    class CoinCounter {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & _coins;
            ar & _textId;
            ar & _text;
            ar & _fontPath;
            ar & _fontSize;
            ar & _fontColor;
        }

        CoinCounter(spic::Transform transform, std::string textId, std::string text, std::string fontPath, int fontSize,
                    spic::Color fontColor, int width, int height);

        CoinCounter();

        void AddCoin();

    private:
        int _coins;

        std::string _textId;
        std::string _text;
        std::string _fontPath;
        int _fontSize;
        spic::Color _fontColor;
    };
}

#endif //PLATFORMER_GAME_COINCOUNTER_HPP