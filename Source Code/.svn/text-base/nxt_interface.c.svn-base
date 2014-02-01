#include "ecrobot_interface.h"
#include "nxt_interface.h"


/* Motor */
S32 motorGetCount(U8 port){
    return nxt_motor_get_count(port);
}

void motorSetCount(U8 port, S32 count){
    nxt_motor_set_count(port, count);
}

void motorSetSpeed(U8 port, S32 speed, S32 mode){
    nxt_motor_set_speed(port, speed, mode);
}

/* Bluetooth */
U32 sendBtPacket(U8 *buf, U32 bufLen){
    return ecrobot_send_bt_packet(buf, bufLen);
}

U32 readBtPacket(U8 *buf, U32 bufLen) {
    return ecrobot_read_bt_packet(buf, bufLen);
}

U32 getSysTime(){
	return systick_get_ms();
}

void initBtConnection(){
    ecrobot_init_bt_slave("1234");
}

void termBtConnection(){
    ecrobot_term_bt_connection();
}

/* LCD Display */
void displayUpdate() {
    display_update();
}

void displayClear(U32 updateToo) {
    display_clear(updateToo);
}

void displayGotoXY(S32 x, S32 y){
    display_goto_xy(x, y);
}

void displayString(const char *str){
    display_string(str);
}

void displayInt(S32 val, U32 places){
    display_int(val, places);
}

void displayFloat(float val) {
    int decimals;
    if (val < 0){
        val = -val;
        display_string("-");
    }
    display_int(val, 0);
    display_string(",");
    decimals = (S32)(val * 100)%100;
    if (decimals < 10)
        display_string("0");
    display_int(decimals, 0);
}

void displayAssists(){
    // Clear display buffer
    //displayClear(0);

    displayGotoXY(2,0);
    displayString("EDC:  ");
    if (EDC_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }
    displayGotoXY(2,1);
    displayString("TCS:  ");
    if (TCS_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }
    displayGotoXY(2,2);
    displayString("ABS:  ");
    if (ABS_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }
    displayGotoXY(2,3);
    displayString("AEB:  ");
    if (AEB_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }
    displayGotoXY(2,4);
    displayString("EAEB: ");
    if (EAEB_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }
    displayGotoXY(2,5);
    displayString("ACC:  ");
    if (ACC_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }
    displayGotoXY(2,6);
    displayString("LKA:  ");
    if (LKA_flag == ON)
    {
        displayString("ON");
    }
    else
    {
        displayString("OFF");
    }

    // Push display buffer to display
    //displayUpdate();
}

/* Ultrasonic */
void initSonarSensor(){
    ecrobot_init_sonar_sensor(SONAR_SENSOR);
}

S32 getSonarSensor()
{
    return ecrobot_get_sonar_sensor(SONAR_SENSOR);
}

void termSonarSensor(){
    ecrobot_term_sonar_sensor(SONAR_SENSOR);
}

/* Rotation sensor */
S16 getRotationSensor(){
    return ecrobot_get_RCX_sensor(ROTATION_SENSOR);
}

void termRotationSensor(){
    ecrobot_term_RCX_power_source(ROTATION_SENSOR);
}

void initRotationSensor(){
    rotationSensor.ticks = 0;
    rotationSensor.secondToLastTick = 0;
    rotationSensor.lastTick = 0;
    ecrobot_set_RCX_power_source(ROTATION_SENSOR);
}

/* Light sensor */
void initLightSensor ()
{
    ecrobot_set_light_sensor_active(LIGHT_SENSOR_RIGHT);
    ecrobot_set_light_sensor_active(LIGHT_SENSOR_LEFT);
}

void termLightSensor ()
{
    ecrobot_set_light_sensor_inactive(LIGHT_SENSOR_RIGHT);
    ecrobot_set_light_sensor_inactive(LIGHT_SENSOR_LEFT);
}

U16 getLightSensorRight ()
{
    return ecrobot_get_light_sensor(LIGHT_SENSOR_RIGHT);
}

U16 getLightSensorLeft ()
{
    return ecrobot_get_light_sensor(LIGHT_SENSOR_LEFT);
}

void waitMs(U32 ms)
{
    systick_wait_ms(ms);
}

/* Touch sensor */
U8 getTouchSensor(U8 port){
    return ecrobot_get_touch_sensor(port);
}

/* NXT internal API */
U8 nxtEnterButton(){
    return ecrobot_is_ENTER_button_pressed();
}

/* MISC */
void updateAssistStates(){
    TCS_flag = getTCS();
    EDC_flag = getEDC();
    ABS_flag = getABS();
    ACC_flag = getACC();
    AEB_flag = getAEB();
    EAEB_flag = getEAEB();
    LKA_flag = getLKA();
}
