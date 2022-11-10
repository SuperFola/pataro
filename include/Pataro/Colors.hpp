#ifndef INCLUDE_PATARO_COLORS_HPP
#define INCLUDE_PATARO_COLORS_HPP

#include <libtcod.hpp>

namespace pat::colors
{
    // grey levels
    constexpr tcod::ColorRGB black {0, 0, 0};
    constexpr tcod::ColorRGB darkestGrey {31, 31, 31};
    constexpr tcod::ColorRGB darkerGrey {63, 63, 63};
    constexpr tcod::ColorRGB darkGrey {95, 95, 95};
    constexpr tcod::ColorRGB grey {127, 127, 127};
    constexpr tcod::ColorRGB lightGrey {159, 159, 159};
    constexpr tcod::ColorRGB lighterGrey {191, 191, 191};
    constexpr tcod::ColorRGB lightestGrey {223, 223, 223};
    constexpr tcod::ColorRGB white {255, 255, 255};

    // sepia
    constexpr tcod::ColorRGB darkestSepia {31, 24, 15};
    constexpr tcod::ColorRGB darkerSepia {63, 50, 31};
    constexpr tcod::ColorRGB darkSepia {94, 75, 47};
    constexpr tcod::ColorRGB sepia {127, 101, 63};
    constexpr tcod::ColorRGB lightSepia {158, 134, 100};
    constexpr tcod::ColorRGB lighterSepia {191, 171, 143};
    constexpr tcod::ColorRGB lightestSepia {222, 211, 195};

    // standard colors
    constexpr tcod::ColorRGB red {255, 0, 0};
    constexpr tcod::ColorRGB flame {255, 63, 0};
    constexpr tcod::ColorRGB orange {255, 127, 0};
    constexpr tcod::ColorRGB amber {255, 191, 0};
    constexpr tcod::ColorRGB yellow {255, 255, 0};
    constexpr tcod::ColorRGB lime {191, 255, 0};
    constexpr tcod::ColorRGB chartreuse {127, 255, 0};
    constexpr tcod::ColorRGB green {0, 255, 0};
    constexpr tcod::ColorRGB sea {0, 255, 127};
    constexpr tcod::ColorRGB turquoise {0, 255, 191};
    constexpr tcod::ColorRGB cyan {0, 255, 255};
    constexpr tcod::ColorRGB sky {0, 191, 255};
    constexpr tcod::ColorRGB azure {0, 127, 255};
    constexpr tcod::ColorRGB blue {0, 0, 255};
    constexpr tcod::ColorRGB han {63, 0, 255};
    constexpr tcod::ColorRGB violet {127, 0, 255};
    constexpr tcod::ColorRGB purple {191, 0, 255};
    constexpr tcod::ColorRGB fuchsia {255, 0, 255};
    constexpr tcod::ColorRGB magenta {255, 0, 191};
    constexpr tcod::ColorRGB pink {255, 0, 127};
    constexpr tcod::ColorRGB crimson {255, 0, 63};

    // dark colors
    constexpr tcod::ColorRGB darkRed {191, 0, 0};
    constexpr tcod::ColorRGB darkFlame {191, 47, 0};
    constexpr tcod::ColorRGB darkOrange {191, 95, 0};
    constexpr tcod::ColorRGB darkAmber {191, 143, 0};
    constexpr tcod::ColorRGB darkYellow {191, 191, 0};
    constexpr tcod::ColorRGB darkLime {143, 191, 0};
    constexpr tcod::ColorRGB darkChartreuse {95, 191, 0};
    constexpr tcod::ColorRGB darkGreen {0, 191, 0};
    constexpr tcod::ColorRGB darkSea {0, 191, 95};
    constexpr tcod::ColorRGB darkTurquoise {0, 191, 143};
    constexpr tcod::ColorRGB darkCyan {0, 191, 191};
    constexpr tcod::ColorRGB darkSky {0, 143, 191};
    constexpr tcod::ColorRGB darkAzure {0, 95, 191};
    constexpr tcod::ColorRGB darkBlue {0, 0, 191};
    constexpr tcod::ColorRGB darkHan {47, 0, 191};
    constexpr tcod::ColorRGB darkViolet {95, 0, 191};
    constexpr tcod::ColorRGB darkPurple {143, 0, 191};
    constexpr tcod::ColorRGB darkFuchsia {191, 0, 191};
    constexpr tcod::ColorRGB darkMagenta {191, 0, 143};
    constexpr tcod::ColorRGB darkPink {191, 0, 95};
    constexpr tcod::ColorRGB darkCrimson {191, 0, 47};

    // darker colors
    constexpr tcod::ColorRGB darkerRed {127, 0, 0};
    constexpr tcod::ColorRGB darkerFlame {127, 31, 0};
    constexpr tcod::ColorRGB darkerOrange {127, 63, 0};
    constexpr tcod::ColorRGB darkerAmber {127, 95, 0};
    constexpr tcod::ColorRGB darkerYellow {127, 127, 0};
    constexpr tcod::ColorRGB darkerLime {95, 127, 0};
    constexpr tcod::ColorRGB darkerChartreuse {63, 127, 0};
    constexpr tcod::ColorRGB darkerGreen {0, 127, 0};
    constexpr tcod::ColorRGB darkerSea {0, 127, 63};
    constexpr tcod::ColorRGB darkerTurquoise {0, 127, 95};
    constexpr tcod::ColorRGB darkerCyan {0, 127, 127};
    constexpr tcod::ColorRGB darkerSky {0, 95, 127};
    constexpr tcod::ColorRGB darkerAzure {0, 63, 127};
    constexpr tcod::ColorRGB darkerBlue {0, 0, 127};
    constexpr tcod::ColorRGB darkerHan {31, 0, 127};
    constexpr tcod::ColorRGB darkerViolet {63, 0, 127};
    constexpr tcod::ColorRGB darkerPurple {95, 0, 127};
    constexpr tcod::ColorRGB darkerFuchsia {127, 0, 127};
    constexpr tcod::ColorRGB darkerMagenta {127, 0, 95};
    constexpr tcod::ColorRGB darkerPink {127, 0, 63};
    constexpr tcod::ColorRGB darkerCrimson {127, 0, 31};

    // darkest colors
    constexpr tcod::ColorRGB darkestRed {63, 0, 0};
    constexpr tcod::ColorRGB darkestFlame {63, 15, 0};
    constexpr tcod::ColorRGB darkestOrange {63, 31, 0};
    constexpr tcod::ColorRGB darkestAmber {63, 47, 0};
    constexpr tcod::ColorRGB darkestYellow {63, 63, 0};
    constexpr tcod::ColorRGB darkestLime {47, 63, 0};
    constexpr tcod::ColorRGB darkestChartreuse {31, 63, 0};
    constexpr tcod::ColorRGB darkestGreen {0, 63, 0};
    constexpr tcod::ColorRGB darkestSea {0, 63, 31};
    constexpr tcod::ColorRGB darkestTurquoise {0, 63, 47};
    constexpr tcod::ColorRGB darkestCyan {0, 63, 63};
    constexpr tcod::ColorRGB darkestSky {0, 47, 63};
    constexpr tcod::ColorRGB darkestAzure {0, 31, 63};
    constexpr tcod::ColorRGB darkestBlue {0, 0, 63};
    constexpr tcod::ColorRGB darkestHan {15, 0, 63};
    constexpr tcod::ColorRGB darkestViolet {31, 0, 63};
    constexpr tcod::ColorRGB darkestPurple {47, 0, 63};
    constexpr tcod::ColorRGB darkestFuchsia {63, 0, 63};
    constexpr tcod::ColorRGB darkestMagenta {63, 0, 47};
    constexpr tcod::ColorRGB darkestPink {63, 0, 31};
    constexpr tcod::ColorRGB darkestCrimson {63, 0, 15};

    // light colors
    constexpr tcod::ColorRGB lightRed {255, 63, 63};
    constexpr tcod::ColorRGB lightFlame {255, 111, 63};
    constexpr tcod::ColorRGB lightOrange {255, 159, 63};
    constexpr tcod::ColorRGB lightAmber {255, 207, 63};
    constexpr tcod::ColorRGB lightYellow {255, 255, 63};
    constexpr tcod::ColorRGB lightLime {207, 255, 63};
    constexpr tcod::ColorRGB lightChartreuse {159, 255, 63};
    constexpr tcod::ColorRGB lightGreen {63, 255, 63};
    constexpr tcod::ColorRGB lightSea {63, 255, 159};
    constexpr tcod::ColorRGB lightTurquoise {63, 255, 207};
    constexpr tcod::ColorRGB lightCyan {63, 255, 255};
    constexpr tcod::ColorRGB lightSky {63, 207, 255};
    constexpr tcod::ColorRGB lightAzure {63, 159, 255};
    constexpr tcod::ColorRGB lightBlue {63, 63, 255};
    constexpr tcod::ColorRGB lightHan {111, 63, 255};
    constexpr tcod::ColorRGB lightViolet {159, 63, 255};
    constexpr tcod::ColorRGB lightPurple {207, 63, 255};
    constexpr tcod::ColorRGB lightFuchsia {255, 63, 255};
    constexpr tcod::ColorRGB lightMagenta {255, 63, 207};
    constexpr tcod::ColorRGB lightPink {255, 63, 159};
    constexpr tcod::ColorRGB lightCrimson {255, 63, 111};

    // lighter colors
    constexpr tcod::ColorRGB lighterRed {255, 127, 127};
    constexpr tcod::ColorRGB lighterFlame {255, 159, 127};
    constexpr tcod::ColorRGB lighterOrange {255, 191, 127};
    constexpr tcod::ColorRGB lighterAmber {255, 223, 127};
    constexpr tcod::ColorRGB lighterYellow {255, 255, 127};
    constexpr tcod::ColorRGB lighterLime {223, 255, 127};
    constexpr tcod::ColorRGB lighterChartreuse {191, 255, 127};
    constexpr tcod::ColorRGB lighterGreen {127, 255, 127};
    constexpr tcod::ColorRGB lighterSea {127, 255, 191};
    constexpr tcod::ColorRGB lighterTurquoise {127, 255, 223};
    constexpr tcod::ColorRGB lighterCyan {127, 255, 255};
    constexpr tcod::ColorRGB lighterSky {127, 223, 255};
    constexpr tcod::ColorRGB lighterAzure {127, 191, 255};
    constexpr tcod::ColorRGB lighterBlue {127, 127, 255};
    constexpr tcod::ColorRGB lighterHan {159, 127, 255};
    constexpr tcod::ColorRGB lighterViolet {191, 127, 255};
    constexpr tcod::ColorRGB lighterPurple {223, 127, 255};
    constexpr tcod::ColorRGB lighterFuchsia {255, 127, 255};
    constexpr tcod::ColorRGB lighterMagenta {255, 127, 223};
    constexpr tcod::ColorRGB lighterPink {255, 127, 191};
    constexpr tcod::ColorRGB lighterCrimson {255, 127, 159};

    // lightest colors
    constexpr tcod::ColorRGB lightestRed {255, 191, 191};
    constexpr tcod::ColorRGB lightestFlame {255, 207, 191};
    constexpr tcod::ColorRGB lightestOrange {255, 223, 191};
    constexpr tcod::ColorRGB lightestAmber {255, 239, 191};
    constexpr tcod::ColorRGB lightestYellow {255, 255, 191};
    constexpr tcod::ColorRGB lightestLime {239, 255, 191};
    constexpr tcod::ColorRGB lightestChartreuse {223, 255, 191};
    constexpr tcod::ColorRGB lightestGreen {191, 255, 191};
    constexpr tcod::ColorRGB lightestSea {191, 255, 223};
    constexpr tcod::ColorRGB lightestTurquoise {191, 255, 239};
    constexpr tcod::ColorRGB lightestCyan {191, 255, 255};
    constexpr tcod::ColorRGB lightestSky {191, 239, 255};
    constexpr tcod::ColorRGB lightestAzure {191, 223, 255};
    constexpr tcod::ColorRGB lightestBlue {191, 191, 255};
    constexpr tcod::ColorRGB lightestHan {207, 191, 255};
    constexpr tcod::ColorRGB lightestViolet {223, 191, 255};
    constexpr tcod::ColorRGB lightestPurple {239, 191, 255};
    constexpr tcod::ColorRGB lightestFuchsia {255, 191, 255};
    constexpr tcod::ColorRGB lightestMagenta {255, 191, 239};
    constexpr tcod::ColorRGB lightestPink {255, 191, 223};
    constexpr tcod::ColorRGB lightestCrimson {255, 191, 207};

    // desaturated colors
    constexpr tcod::ColorRGB desaturatedRed {127, 63, 63};
    constexpr tcod::ColorRGB desaturatedFlame {127, 79, 63};
    constexpr tcod::ColorRGB desaturatedOrange {127, 95, 63};
    constexpr tcod::ColorRGB desaturatedAmber {127, 111, 63};
    constexpr tcod::ColorRGB desaturatedYellow {127, 127, 63};
    constexpr tcod::ColorRGB desaturatedLime {111, 127, 63};
    constexpr tcod::ColorRGB desaturatedChartreuse {95, 127, 63};
    constexpr tcod::ColorRGB desaturatedGreen {63, 127, 63};
    constexpr tcod::ColorRGB desaturatedSea {63, 127, 95};
    constexpr tcod::ColorRGB desaturatedTurquoise {63, 127, 111};
    constexpr tcod::ColorRGB desaturatedCyan {63, 127, 127};
    constexpr tcod::ColorRGB desaturatedSky {63, 111, 127};
    constexpr tcod::ColorRGB desaturatedAzure {63, 95, 127};
    constexpr tcod::ColorRGB desaturatedBlue {63, 63, 127};
    constexpr tcod::ColorRGB desaturatedHan {79, 63, 127};
    constexpr tcod::ColorRGB desaturatedViolet {95, 63, 127};
    constexpr tcod::ColorRGB desaturatedPurple {111, 63, 127};
    constexpr tcod::ColorRGB desaturatedFuchsia {127, 63, 127};
    constexpr tcod::ColorRGB desaturatedMagenta {127, 63, 111};
    constexpr tcod::ColorRGB desaturatedPink {127, 63, 95};
    constexpr tcod::ColorRGB desaturatedCrimson {127, 63, 79};

    // metallic
    constexpr tcod::ColorRGB brass {191, 151, 96};
    constexpr tcod::ColorRGB copper {197, 136, 124};
    constexpr tcod::ColorRGB gold {229, 191, 0};
    constexpr tcod::ColorRGB silver {203, 203, 203};

    // miscellaneous
    constexpr tcod::ColorRGB celadon {172, 255, 175};
    constexpr tcod::ColorRGB peach {255, 159, 127};
}

#endif
