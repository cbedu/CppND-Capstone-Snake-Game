#ifndef MAPTILE_H
#define MAPTILE_H

/**
 * @brief Tile object, contains information used for each non-floor tile on the map.
 */
class MapTile {
  public:
  /**
   * @brief Construct a new Map Tile object
   * 
   * Create an "empty" object. type_ of 0 is floor and is not used in these tile objects.
   * 
   */
  MapTile();
  
  /**
   * @brief Construct a new Map Tile object
   * 
   * Type and location, ttl assumed off, and perm set by type default lookup.
   * 
   * @param _type   Tile type
   * @param _x      X position
   * @param _y      Y position
   */
  MapTile(int _type, int _x, int _y);
  
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
  MapTile(int _type, int _x, int _y, int _ttl);

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
  MapTile(int _type, int _x, int _y, int _ttl, bool _perm);

  /**
  * @brief Setter for tile type
  * 
  * @param newType 0=floor (not used), 1=food, 2=poison, 3=barrier
  */
  void Type(int newType);

  /**
  * @brief Getter for tile type
  * 
  * @return int newType 0=floor (not used), 1=food, 2=poison, 3=barrier
  */
  int Type(void) const;

  /**
  * @brief Setter for X position
  * 
  * @param newX X coords
  */
  void X(int newX);
  
  /**
  * @brief Getter for X position
  * 
  * @return int X coord
  */
  int X(void) const;

  /**
  * @brief Setter for Y position
  * 
  * @param newY Y coords
  */
  void Y(int newY);

  /**
  * @brief Getter for Y position
  * 
  * @return int Y coords
  */
  int Y(void) const;

  /**
  * @brief Setter for TTL, overwrites current TTL immediately
  * 
  * @param newTTL Time To Live for this tile
  */
  void TTL(int newTTL);

  /**
  * @brief Getter for TTL for this tile
  * 
  * @return int Time To Live in seconds.
  */
  int TTL(void) const;
  
  /**
  * @brief Setter for permanent flag for this tile
  * 
  * @param newPerm true or false to indicate whether tile is permanent
  */
  void IsPerm(bool newPerm);

  /**
  * @brief Getter for permanent flag of this tile
  * 
  * @return true     Indicates this tile is permanent and will not be deleted on TTL or contact
  * @return false    Indicates this tile will be deleted on TTL or contact
  */
  bool IsPerm(void) const;

  private:
  int type_;    // tile type (1=food, 2=poison, 3=barrier, 0=floor....causes entry to be removed)
  int x_;       // horizontal location
  int y_;       // vertical location
  int ttl_;     // time to live  // cannot be -1 if type cannot be perm // object removed if 0 and not perm
  bool perm_;   // permanent flag // if true this tile does not get deleted, even if TTL reaches 0

  // tile types:
  //  0 = floor   default, not part of list, can't be perm, no ttl
  //  1 = food    can't be perm, can have ttl
  //  2 = poison  can't be perm, can have ttl
  //  3 = barrier can be perm, can have ttl
  constexpr static bool canBePerm[] = {false, false, false, true};
};

#endif