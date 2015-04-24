
#include "MapLoader.h"
#include "lib/tinyxml/tinyxml.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


MapLoader::MapLoader() {
}

MapLoader::~MapLoader() {

}
bool MapLoader::LoadFromFile(std::string filename)
{
    TiXmlDocument mapFile(filename.c_str());
    
    if (!mapFile.LoadFile())
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }
    
    /*Entramos en la etiqueta <map>, la raiz del archivo*/
    TiXmlElement* map;
    map = mapFile.FirstChildElement("map");
    
    /*Leemos las propiedades de map y las almacenamos*/
    ancho = atoi(map->Attribute("width"));
    alto = atoi(map->Attribute("height"));
    anchoTile = atoi(map->Attribute("tilewidth"));
    altoTile = atoi(map->Attribute("tileheight"));
    
    /*Entramos en la etiqueta <tileset> y almacenamos el primer gid*/        
    TiXmlElement* tileset;
    tileset = map->FirstChildElement("tileset");
    firstTileID = atoi(tileset->Attribute("firstgid"));
    
    /*Cargar imagen del tileset*/
    TiXmlElement* img;
    std::string src;
    img = tileset->FirstChildElement("image");
    src = img->Attribute("source");
  
    if(!imgTileset.loadFromFile(src)){
        std::cerr << "Failed to load tile sheet." << std::endl;
    
    }

    //Calculo de las filas y columnas de la imagen
    int columnas = imgTileset.getSize().x / anchoTile;
    int filas = imgTileset.getSize().y / altoTile;
    
    //Creamos un vector de rectangulos para estructurar los tiles en rectangulos
    std::vector <sf::Rect<int> > rectEstruct;
    
    //Calculo de los rectangulos de los tiles y almacenado en el vector de rectangulos
    for (int y = 0; y < filas; y++)
    {
        for (int x = 0; x < columnas; x++)
        {
            sf::Rect <int> rect;
            rect.top = y * altoTile;
            rect.height = altoTile;
            rect.left = x * anchoTile;
            rect.width = anchoTile;
            rectEstruct.push_back(rect);
        }
    }
    //Layers
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    int controlador = 0;
    
    while (layerElement)
    {
        
        Layer layer;
        if (layerElement->Attribute("opacity") != NULL)//check if opacity attribute exists
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);//convert the (string) opacity element to float
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;//if the attribute doesnt exist, default to full opacity
        }
        
        //Tiles
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;//Work out the subrect ID to 'chop up' the tilesheet image.
            if (subRectToUse >= 0)//we only need to (and only can) create a sprite/tile if there is one to display
            {
                sf::Sprite sprite;//sprite for the tile
                sprite.setTexture(imgTileset);
                sprite.setTextureRect(rectEstruct[subRectToUse]);
                sprite.setPosition(x * anchoTile, y * altoTile);

                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));//Set opacity of the tile.

                //add tile to layer 
                layer.tiles.push_back(sprite);
                
            }
            if(controlador == 1){
                    gids.push_back(tileGID);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            //increment x, y
            x++;
            if (x >= ancho)//if x has "hit" the end (right) of the map, reset it to the start (left)
            {
                x = 0;
                y++;
                if (y >= alto)
                {
                    y = 0;
                }
            }
        }
        controlador++;

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    return true;
}
void MapLoader::Draw(sf::RenderWindow &window)
{

    for (int layer = 0; layer < layers.size(); layer++)
    {
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
        {
                window.draw(layers[layer].tiles[tile]); 
        }
    }
}

bool MapLoader::Colision(int x,int y){//devuelve true si hay colision para esa posicion
    int tile_x = x/25;
    int tile_y = y/25;
    int pos = tile_x + 52*tile_y;
    std::cout << pos << std::endl;
    if(gids[pos] != 0){
        return false;
    }
    return true;
}