#include "MapTile.hpp"
#include <iostream>

/**
 * @brief Construct a new Map Tile object
 * 
 * Create an "empty" object. type_ of 0 is floor and is not used in these tile objects.
 * 
 */
MapTile::MapTile() : type_(0), x_(0), y_(0) {};

/**
 * @brief Construct a new Map Tile object
 * 
 * Type and location, ttl assumed off, and perm set by type default lookup.
 * 
 * @param _type   Tile type
 * @param _x      X position
 * @param _y      Y position
 */
MapTile::MapTile(int _type, int _x, int _y)
    : type_(_type), x_(_x), y_(_y), ttl_(-1), perm_(canBePerm[_type]) {};
    
/**
 * @brief Construct a new Map Tile object
 * 
 * Type and location, ttl set, which force sets perm to false to allow later deletion.
 * 
 * @param _type   Tile type
 * @param _x      X position
 * @param _y      Y position
 * @param _ttl    Time To Live in seconds
 */
MapTile::MapTile(int _type, int _x, int _y, int _ttl)
    : type_(_type), x_(_x), y_(_y), ttl_(_ttl), perm_(canBePerm[_type]) {};

/**
 * @brief Construct a new Map Tile object
 * 
 * Full object initialization
 * 
 * @param _type   Tile type
 * @param _x      X position
 * @param _y      Y position
 * @param _ttl    Time To Live in seconds
 * @param _perm   Permanent flag, if true the tile is not deleted
 *                (set back to floor type) on TTL or contact by snake
 */
MapTile::MapTile(int _type, int _x, int _y, int _ttl, bool _perm)
    : type_(_type), x_(_x), y_(_y), ttl_(_ttl)
    {
      if(canBePerm[_type]){
        perm_ = _perm;
      }else{
        std::cout << "\n\nUnhappy perm state\n\n";
        perm_ = canBePerm[_type];
      }
    };

/**
 * @brief Setter for tile type
 * 
 * @param newType 0=floor (not used), 1=food, 2=poison, 3=barrier
 */
void MapTile::Type(int newType){ type_ = newType; };

/**
 * @brief Getter for tile type
 * 
 * @return int newType 0=floor (not used), 1=food, 2=poison, 3=barrier
 */
int MapTile::Type(void) const { return type_; };

/**
 * @brief Setter for X position
 * 
 * @param newX X coords
 */
void MapTile::X(int newX){ x_ = newX; };

/**
 * @brief Getter for X position
 * 
 * @return int X coord
 */
int MapTile::X(void) const { return x_; } ;

/**
 * @brief Setter for Y position
 * 
 * @param newY Y coords
 */
void MapTile::Y(int newY){ y_ = newY; };

/**
 * @brief Getter for Y position
 * 
 * @return int Y coords
 */
int MapTile::Y(void) const{ return y_; };

/**
 * @brief Setter for TTL, overwrites current TTL immediately
 * 
 * @param newTTL Time To Live for this tile
 */
void MapTile::TTL(int newTTL){ ttl_ = newTTL; };

/**
 * @brief Getter for TTL for this tile
 * 
 * @return int Time To Live in seconds.
 */
int MapTile::TTL(void) const { return ttl_; };

/**
 * @brief Setter for permanent flag for this tile
 * 
 * @param newPerm true or false to indicate whether tile is permanent
 */
void MapTile::IsPerm(bool newPerm){ perm_ = newPerm; };

/**
 * @brief Getter for permanent flag of this tile
 * 
 * @return true     Indicates this tile is permanent and will not be deleted on TTL or contact
 * @return false    Indicates this tile will be deleted on TTL or contact
 */
bool MapTile::IsPerm(void) const { return perm_; };