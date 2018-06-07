/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    map<Point<3>, TileImage> tmap;
    vector<Point<3>> color;

    for(int i = 0; i < (int)theTiles.size(); i++){
        RGBAPixel pix = theTiles.at(i).getAverageColor();
        Point<3> p(pix.red, pix.green, pix.blue);
        tmap[p] = theTiles.at(i);
        color.push_back(p);
    }

    KDTree<3>::KDTree t(color);

    MosaicCanvas::MosaicCanvas *can = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for(int i = 0; i < theSource.getRows(); i++){
        for(int j = 0; j < theSource.getColumns(); j++){
            RGBAPixel pix = theSource.getRegionColor(i, j);
            Point<3> target(pix.red, pix.green, pix.blue);
            Point<3> nNeighbor = t.findNearestNeighbor(target);
            TileImage add = tmap[nNeighbor];
            can->setTile(i, j, add);
        }
    }
    return can;
}
