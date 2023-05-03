#include "U8glib.h" // Library for OLED display, there is also U8G2 that exists, but I created this project before I discovered that libarary
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);
// 'Select', 128x20px
// State machine
enum State {
           Start,
           Results,
           R1,
           R2,
           R3,
           FAQ,
           Q1,
           Q2,
           Q3,
           End
           };

enum {BuffSize=9};
char buf[BuffSize];

int data[3];
// Interactive Logistics ////////////////////////////////////
// Button Pins
#define left 12
#define middle 8 
#define right 4 

// One input per button press, holding doesn't do anything
int leftclick = 0;
int midclick = 0;
int rightclick = 0;

// pin and state pairing from variables set above
int buttpinclick[3][2] = {
                         {left, leftclick},
                         {middle, midclick},
                         {right, rightclick}
                         };

State state = Start; // Set state machine to start

void setup() {

    pinMode(left, INPUT_PULLUP);
    pinMode(middle, INPUT_PULLUP);
    pinMode(right, INPUT_PULLUP);

    Serial.begin(9600);

// Setting display font and color on oled screen
    u8g.setFont(u8g_font_7x14Br);
    u8g.setColorIndex(1);
}

void loop() {
// UI display Logic via state machine, each case also calls external method for controls and item displays
    u8g.firstPage();
            do{
        switch (state) {
            case Start: // Starting Screen
                startConfig();
                u8g.drawStr(50,14,"Start");
                u8g.drawStr(42,34,"Results");
                u8g.drawStr(54,58,"FAQ");
                break;
            case Results:
                resultsConfig();
                break;
            // case R1: Unused
            // case R2:
            // case R3:
            //     pollConfig();
                break;
            case FAQ:
                faqConfig();
                break;
            case Q1:
            case Q2:
            case Q3:
                qConfig();
                break;
            case End:
                endConfig();
                // snprintf (buf, BuffSize, "%d", data[0]);
                // u8g.drawStr(10, 33, buf);
                // snprintf (buf, BuffSize, "%d", data[1]);
                // u8g.drawStr(20, 33, buf);
                // snprintf (buf, BuffSize, "%d", data[2]);
                // u8g.drawStr(30, 33, buf);
                break;
        }
    } while (u8g.nextPage());
}

void startConfig() {
    int clicked = -1;
    for (int i = 0; i < (sizeof(buttpinclick)/sizeof(buttpinclick[0])); i++) {
        if ((digitalRead(buttpinclick[i][0]) == LOW) && (buttpinclick[i][1] == 0))  {
            clicked = i;
            buttpinclick[i][1] = 1;
        }
        if ((digitalRead(buttpinclick[i][0]) == HIGH) && (buttpinclick[i][1] == 1)) {
            buttpinclick[i][1] = 0;
        }
    }
    switch (clicked) {
        case 0:
            state = Q1;
            break;
        case 1:
            state = Results;
            break;
        case 2:
            state = FAQ;
            break;
    }
}

bool didRequest = false; // Unused
void resultsConfig() {
    // punch Python, grab SQL data
    u8g.drawStr(0,20,"Results");
    u8g.drawStr(0,32,"Unbuilt");
    u8g.drawStr(0,44,"Check PyTerminal");
    switch(didRequest) {
        case false:
            Serial.println("pull");
            didRequest = true;
            break;
        case true:
            break;
    }
    
    for (int i = 0; i < (sizeof(buttpinclick)/sizeof(buttpinclick[0])); i++) {
        if ((digitalRead(buttpinclick[i][0]) == LOW) && (buttpinclick[i][1] == 0))  {
            state = Start;
            didRequest = false;
            buttpinclick[i][1] = 1;
        }
        if ((digitalRead(buttpinclick[i][0]) == HIGH) && (buttpinclick[i][1] == 1)) {
            buttpinclick[i][1] = 0;
        }
    }

    
  
}

// Unbuilt
// void pollConfig() {

//     for (int i = 0; i < (sizeof(buttpinclick)/sizeof(buttpinclick[0])); i++) {
//         if ((digitalRead(buttpinclick[i][0]) == LOW) && (buttpinclick[i][1] == 0))  {
//             switch(state) {
//                 case R1:
//                     state = R2;
//                     break;
//                 case R2:
//                     state = R3;
//                 case R3:
//                     didRequest = false;
//                     state = Start;
//             }
//             buttpinclick[i][1] = 1;
//         }
//         if ((digitalRead(buttpinclick[i][0]) == HIGH) && (buttpinclick[i][1] == 1)) {
//             buttpinclick[i][1] = 0;
//         }
//     }

//     switch(state) {
//                 case R1:
//                     Serial.read();
//                     break;
//                 case R2:
//                     break;
//                 case R3:
//                     break;
//             }
// }

void faqConfig() {
    // Project dialoque
    u8g.drawStr(0,10,"This project shows the");
    u8g.drawStr(0,22,"usage of data sync");
    u8g.drawStr(0,34,"across data ");
    u8g.drawStr(0,46,"platforms with");
    u8g.drawStr(0,58,"Arduino as a tool.");

    for (int i = 0; i < (sizeof(buttpinclick)/sizeof(buttpinclick[0])); i++) {
        if ((digitalRead(buttpinclick[i][0]) == LOW) && (buttpinclick[i][1] == 0))  {
            state = Start;
            buttpinclick[i][1] = 1;
        }
        if ((digitalRead(buttpinclick[i][0]) == HIGH) && (buttpinclick[i][1] == 1)) {
            buttpinclick[i][1] = 0;
        }
    }
}

void qConfig() {

    int clicked = -1;
    for (int i = 0; i < (sizeof(buttpinclick)/sizeof(buttpinclick[0])); i++) {
        if ((digitalRead(buttpinclick[i][0]) == LOW) && (buttpinclick[i][1] == 0))  {
            clicked = i;
            buttpinclick[i][1] = 1;
        }
        if ((digitalRead(buttpinclick[i][0]) == HIGH) && (buttpinclick[i][1] == 1)) {
            clicked = -1;
            buttpinclick[i][1] = 0;
        }
    }

    switch (state) {  // Depending on Question state, grab specific SQLDB question entry
        case Q1:
            // qget(1); // Display question from sql
            u8g.drawStr(24,20,"Did you like");
            u8g.drawStr(24,32,"this course?");
            u8g.drawStr(0,54,"Yes");
            u8g.drawStr(54,54,"Meh");
            u8g.drawStr(112,54,"No");
            if (clicked != -1) {
                data[0] = clicked;
                state = Q2;
            }
            break;
        case Q2:
            // qget(2);
            u8g.drawStr(4,20,"Do you understand");
            u8g.drawStr(16,32,"this project?");
            u8g.drawStr(0,54,"Yes");
            u8g.drawStr(54,54,"Meh");
            u8g.drawStr(112,54,"No");
            if (clicked != -1) {
                data[1] = clicked;
                state = Q3;
            }
            break;
        case Q3:
            // qget(3);
            u8g.drawStr(8,16,"Do you like the");
            u8g.drawStr(18,28,"INFO Capstone");
            u8g.drawStr(40,40,"course?");
            u8g.drawStr(0,54,"Yes");
            u8g.drawStr(54,54,"Meh");
            u8g.drawStr(112,54,"No");
            if (clicked != -1) {
                data[2] = clicked;
                state = End;
            }
            break;
    }

}

void endConfig() {

    u8g.drawStr(30,20,"Thank you!");
    u8g.drawStr(20,40,"Press a button");
    u8g.drawStr(36,52,"to reset");

    for (int i = 0; i < (sizeof(buttpinclick)/sizeof(buttpinclick[0])); i++) {
        if ((digitalRead(buttpinclick[i][0]) == LOW) && (buttpinclick[i][1] == 0))  {
            snprintf (buf, BuffSize, "%d:%d:%d", data[0], data[1], data[2]);
            Serial.println(buf);
            state = Start;
            buttpinclick[i][1] = 1;
        }
        if ((digitalRead(buttpinclick[i][0]) == HIGH) && (buttpinclick[i][1] == 1)) {
            buttpinclick[i][1] = 0;
        }
    }
}