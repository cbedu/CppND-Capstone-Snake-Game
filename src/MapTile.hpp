#ifndef MAPTILE_H
#define MAPTILE_H

class MapTile {
  public:
  MapTile();
  
  MapTile(int _type, int _x, int _y);
  
  MapTile(int _type, int _x, int _y, int _ttl);

  MapTile(int _type, int _x, int _y, int _ttl, bool _perm);

  void Type(int newType);
  int Type(void);

  void X(int newX);
  int X(void);
  
  void Y(int newY);
  int Y(void);

  void TTL(int newTTL);
  int TTL(void);
  
  void IsPerm(bool newPerm);
  bool IsPerm(void);

  private:
  int type_; // tile type (1=food, 2=poison, 3=barrier, 0=floor....causes entry to be removed)
  int x_;    // horizontal location
  int y_;    // vertical location
  int ttl_;  // time to live  // cannot be -1 if type cannot be perm // object removed if 0 and not perm
  bool perm_;

  // tile types:
  //  0 = floor   default, not part of list, can't be perm, no ttl
  //  1 = food    can't be perm, can have ttl
  //  2 = poison  can't be perm, can have ttl
  //  3 = barrier can be perm, can have ttl
  constexpr static bool canBePerm[] = {"false", "false", "true"};
};

#endif