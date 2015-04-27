/* 
 * File:   MapLoader.h
 * Author: monchu11_18
 *
 * Created on 20 de marzo de 2015, 20:41
 */

#ifndef MAPLOADER_H
#define	MAPLOADER_H

#include <string>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct Layer{
    int opacity;
    std::vector <sf::Sprite> tiles;
};

class MapLoader {
public:
    MapLoader();
    virtual ~MapLoader();
    bool LoadFromFile(std::string filename);
    //Draws the map to the provided window.
    void Draw(sf::RenderWindow &window, int capa); 
    //Dada una posición comprueba si se spuede avanzar o no
    bool Colision(int x,int y, int tipo);
    //Vector con todos los gids de los tiles
    std::vector <int> gids;
private:
    int ancho, alto, anchoTile,altoTile;//Propiedades de map
    int firstTileID;//Primer gid del tileset
    sf::Texture imgTileset;//Imagen del tileset
    //This stores each layer of sprites/tiles so they can be drawn in order.
    std::vector <Layer> layers;
};

#endif	/* MAPLOADER_H */

