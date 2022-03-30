enum colour {black,blue,cyan,darkgray,gray,green,lightgray,magenta,orange,pink,red,white,yellow};
typedef enum colour colour;

void drawLine(int, int, int, int);
void drawRect(int, int, int, int);
void fillRect(int, int, int, int);
void drawOval(int, int, int, int);
void fillOval(int, int, int, int);
void drawArc(int, int, int, int, int, int);
void fillArc(int, int, int, int, int, int);
void drawPolygon(int, int[], int[]);
void fillPolygon(int, int[], int[]);
void drawString(char*, int, int);
void displayImage(char*, int, int);

void setColour(colour);
void setRGBColour(int, int, int);

void foreground(void);
void background(void);
void clear(void);

void setWindowSize(int, int);

void sleep(int);

