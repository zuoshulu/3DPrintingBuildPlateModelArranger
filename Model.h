#pragma once
class Model
{
public:
  Model() : x(0), y(0), length(0), width(0){};
  Model(int length_, int width_) : x(0), y(0), length(length_), width(width_){};
  int getX() { return x; }
  void setX(int x_) { x = x_; }
  int getY() { return y; }
  void setY(int y_) { y = y_; }
  int getLength() { return length; }
  void setLength(int length_) { length = length_; }
  int getWidth() { return width; }
  void setWitdh(int width_) { width = width_; }
  bool getFlipFlag() { return flipped; }
  bool setFlipFlag(bool flipped_) { flipped = flipped_; }

private:
  int x;
  int y;
  int length;
  int width;
  bool flipped;
};
