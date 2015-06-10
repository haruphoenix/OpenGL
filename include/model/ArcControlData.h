#ifndef ARC_CONTROL_DATA
#define ARC_CONTROL_DATA

#include <set>

/*****************************************************
 * Contains all of the control data in the model
 *****************************************************/
class ArcControlData{
 public:
  ArcControlData();
  // Set the Controller State
  void setMouse(int x, int y);
  void setMouseLeft(bool down);
  void setMouseMiddle(bool down);
  void setMouseRight(bool down);
  void setKey(char key, bool down);
  void setQuit(bool quit);
  void setSize(int x, int y);
  void setTrap(bool on) { mTrap = on; };
  // Read the Controller State
  bool trap() { return mTrap; };
  bool getMouse(int* x, int* y);
  bool getSize(int* x, int* y);
  bool getMouseLeft();
  bool getMouseMiddle();
  bool getMouseRight();
  char getNextKey();
  bool quit();
 private:
  int  mMouseX;
  int  mMouseY;
  int  mSizeX;
  int  mSizeY;
  bool mMouseLeft;
  bool mMouseMiddle;
  bool mMouseRight;
  std::set<char> mKeys;
  std::set<char>::iterator mKeyIndex;
  bool mQuit;
  bool mResize;
  bool mTrap;
  bool mMouseChange;
};

#endif
