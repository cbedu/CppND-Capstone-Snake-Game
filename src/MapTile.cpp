#include "MapTile.hpp"
#include <iostream>
  
MapTile::MapTile() : type_{0}, x_(0), y_(0), ttl_(0) {};
MapTile::MapTile(int _type, int _x, int _y)
    : type_(_type), x_(_x), y_(_y), ttl_(0), perm_(canBePerm[_type]) {};
  
MapTile::MapTile(int _type, int _x, int _y, int _ttl)
    : type_(_type), x_(_x), y_(_y), ttl_(_ttl), perm_(canBePerm[_type]) {};

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

void MapTile::Type(int newType){ type_ = newType; };
int MapTile::Type(void){ return type_; };

void MapTile::X(int newX){ x_ = newX; };
int MapTile::X(void){ return x_; };
  
void MapTile::Y(int newY){ y_ = newY; };
int MapTile::Y(void){ return y_; };

void MapTile::TTL(int newTTL){ ttl_ = newTTL; };
int MapTile::TTL(void){ return ttl_; };
  
void MapTile::IsPerm(bool newPerm){ perm_ = newPerm; };
bool MapTile::IsPerm(void){ return perm_; };