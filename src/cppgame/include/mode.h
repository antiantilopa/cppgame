#ifndef MODE_H
#define MODE_H

class Mode{
private:
    static char mode;
public: 
    static char ox;
    static char oy;
    static char x_sign;
    static char y_sign;

    static void setOrigin(char origin);
    static void setDirection(char direction);
    static char getOrigin();
    static char getDirection();

    static inline const char ORIGIN_TOP_LEFT = 0x00;      // 00 00
    static inline const char ORIGIN_TOP_CENTER = 0x01;    // 00 01
    static inline const char ORIGIN_TOP_RIGHT = 0x02;     // 00 10
    static inline const char ORIGIN_CENTER_LEFT = 0x04;   // 01 00
    static inline const char ORIGIN_CENTER = 0x05;        // 01 01
    static inline const char ORIGIN_CENTER_RIGHT = 0x06;  // 01 10
    static inline const char ORIGIN_BOTTOM_LEFT = 0x08;   // 10 00
    static inline const char ORIGIN_BOTTOM_CENTER = 0x09; // 10 01
    static inline const char ORIGIN_BOTTOM_RIGHT = 0x0A;  // 10 10

    static inline const char DIRECTION_UP_RIGHT = 0x00;   // 00
    static inline const char DIRECTION_UP_LEFT = 0x10;    // 10
    static inline const char DIRECTION_DOWN_RIGHT = 0x20; // 01  
    static inline const char DIRECTION_DOWN_LEFT = 0x30;  // 11
};


#endif