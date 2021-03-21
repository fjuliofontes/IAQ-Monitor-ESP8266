
/***********************************************************************************************************************
 * 
 * @file    main.cpp
 * @brief   Main.
 * @date    23/01/2021
 * @author  Fernando Fontes
 * @note    Platform Target: ESP8266 12E
 *
 * TAB SIZE: 4 SPACES
 *
***********************************************************************************************************************/

/****************************************************** Includes ******************************************************/
// WiFi includes
#include <ESP8266WiFi.h>
// MQTT
#include <MQTT.h>
// I2C
#include <Wire.h>
// EEPROM
#include <EEPROM.h>
// BME680
#include "bsec.h"
// Util
#include "util.h"
// OLED 0.96inch display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

/****************************************************** Defines *******************************************************/
#define STATE_SAVE_PERIOD	UINT32_C(360 * 60 * 1000) // 360 minutes - 4 times a day
#define DISPLAY_REFRESH_TIME  (30 * 1 * 1000) // 30 seconds
#define LED_BUILTIN 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
/****************************************************** Typedefs ******************************************************/

/***************************************************** Constants ******************************************************/
/* Configure the BSEC library with information about the sensor
    18v/33v = Voltage at Vdd. 1.8V or 3.3V
    3s/300s = BSEC operating mode, BSEC_SAMPLE_RATE_LP or BSEC_SAMPLE_RATE_ULP
    4d/28d = Operating age of the sensor in days
    generic_18v_3s_4d
    generic_18v_3s_28d
    generic_18v_300s_4d
    generic_18v_300s_28d
    generic_33v_3s_4d
    generic_33v_3s_28d
    generic_33v_300s_4d
    generic_33v_300s_28d
*/
const uint8_t bsec_config_iaq[] = {
//#include "config/generic_33v_300s_4d/bsec_iaq.txt"
#include "config/generic_33v_3s_4d/bsec_iaq.txt"
};

const uint8_t calibration[] = {
#include "myCalibration.txt"
};

// WiFi credentials
const char ssid[] = "YOUR_SSID";
const char pass[] = "YOUR_PWD";
/***************************************************** Variables ******************************************************/

// Sockets
WiFiClient net;
MQTTClient client;

// General Variables
float secondary_code_exec_time = 10; // defined in ms
unsigned long elapsedTime = 0;
unsigned long display_last_update = 0;
bool flag = false;
bool sendIP = true;
char payload[500];

// Create an object of the class Bsec
Bsec iaqSensor;
uint8_t bsecState[BSEC_MAX_STATE_BLOB_SIZE] = {0};
uint16_t stateUpdateCounter = 0;

// Objects for OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/*********************************************** Internal Declarations ************************************************/
// Helper functions declarations
void checkIaqSensorStatus(void);
void errLeds(void);
void loadState(void);
void updateState(void);

// MQTT
void connect(void);
void messageReceived(String &topic, String &payload);

/***************************************************** Functions ******************************************************/

/**
 *
 * @brief   Arduino like setup - runs once at the boot
 * @param   void
 * @return  void.
 * 
**/
void setup() {
    // Setup UART for debug
    Serial.begin(115200);

    // Setup GPIO
    pinMode(LED_BUILTIN,OUTPUT);

    // Setup I2C
    Wire.begin(PIN_WIRE_SDA,PIN_WIRE_SCL);

    // Setup EEPROM
    EEPROM.begin(BSEC_MAX_STATE_BLOB_SIZE + 1); // 1st address for the length

    // Setup BME680
    /// Begin I2C
    iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
    Serial.printf("\nBSEC library version %u.%u.%u.%u\n",iaqSensor.version.major,iaqSensor.version.minor,iaqSensor.version.major_bugfix,iaqSensor.version.minor_bugfix);
    checkIaqSensorStatus();
    /// Apply default configs
    iaqSensor.setConfig(bsec_config_iaq);
    checkIaqSensorStatus();
    /// Attempt to load previous state from EEPROM
    loadState();
    /// Set desired variables
    bsec_virtual_sensor_t sensorList[10] = {
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_STATIC_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };
    iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
    checkIaqSensorStatus();

    // Setup OLED
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    delay(2000);
    // Clear Display
    display.clearDisplay();
    // display intro
    display.drawBitmap(0, 0, intro, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    // Apply changes
    display.display(); 

    // Setup WIFI
    WiFi.begin(ssid, pass);

    // Setup MQTT
    client.begin("broker.hivemq.com",1883, net);
    client.onMessage(messageReceived);

    // Attempt to connect 
    connect();
    // Turns the BUILT_IN_LED OFF
    digitalWrite(LED_BUILTIN,HIGH);
}

/**
 *
 * @brief   main() Arduino like function - infinite loop
 * @param   void
 * @return  void.
 * 
**/
void loop() {
    //>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<//
    //>>>>>>>>>>>>>>>>>> PRIORITY CODE <<<<<<<<<<<<<<<<<//
    //>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<//

    if (iaqSensor.run()) { // If new data is available
        double accuracy = (iaqSensor.staticIaqAccuracy + 
                            iaqSensor.breathVocAccuracy +
                            iaqSensor.co2Accuracy +
                            iaqSensor.iaqAccuracy
                            ) / 4.f;

        if(accuracy >= 2.5f){
            digitalWrite(LED_BUILTIN,LOW);
        }

        if (client.connected()) {

            //rawT,T,rawH,H,P,IAQ,sIAQ,eCO2,eVOC

            snprintf(
                payload,
                500,
                "%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f",
                iaqSensor.rawTemperature,
                iaqSensor.temperature,
                iaqSensor.rawHumidity,
                iaqSensor.humidity,
                iaqSensor.pressure/100.0f,
                iaqSensor.iaq,
                iaqSensor.staticIaq,
                iaqSensor.co2Equivalent,
                iaqSensor.breathVocEquivalent
            );

            client.publish("ESP8266/BME680/data", payload);
        }

        updateState();
    } else {
        checkIaqSensorStatus();
    }

    // if BME680 next call is in less then 120% of secondary_code_exec_time ms, there is no time to play around, just 
    // return and wait until having more spare time.
    if((iaqSensor.nextCall - millis()) <= (secondary_code_exec_time*1.2f)){
        return;
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<//
    //>>>>>>>>>>>>>>>> AUXILIARY CODE <<<<<<<<<<<<<<<<<//
    //>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<//

    // constantly keep correcting the secondary_code_exec_time
    elapsedTime = millis();

    // check connection
    if (!client.connected()) {
        connect();
    }

    if ( millis() - display_last_update > DISPLAY_REFRESH_TIME) {
        display_last_update = millis();
        display.setFont(&FreeSans9pt7b);
        display.clearDisplay();
        display.setTextSize(1);             
        display.setTextColor(WHITE);        
        display.setCursor(0,20);             
        display.printf("T: %.2f C\n",iaqSensor.temperature);
        display.setCursor(0,40);             
        display.printf("H: %.2f %%\n",iaqSensor.humidity);
        display.setCursor(0,60);             
        display.printf("IAQ: %.2f\n", iaqSensor.iaq);
        // Draw bitmap on the screen
        if(iaqSensor.iaq <= 100) {
            display.drawBitmap(96, 16, smile, 32, 32, 1);
        } else if( iaqSensor.iaq <= 200 ) {
            display.drawBitmap(96, 16, neutral, 32, 32, 1);
        } else {
            display.drawBitmap(96, 16, sad, 32, 32, 1);
        }
        display.display();
    }

    // update secondary_code_exec_time using 30% of the last value and 70% of the current elapsed time
    secondary_code_exec_time = secondary_code_exec_time * 0.3f + (millis()-elapsedTime)*0.7f;

}

/**
 *
 * @brief   This function will attempt to connect to MQTT as soon 
 *          a the WiFi connection is available.
 * @param   void
 * @return  void.
 * 
**/
void connect(void) {
    Serial.print("checking wifi...");
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }

    Serial.print("\nconnecting...");
    if(!client.connect("ESP-01", nullptr, nullptr)) {
        return;
    }

    Serial.println("\nconnected!");

    // client.subscribe("ESP-01/updates");
    // client.unsubscribe("/hello");
}

/**
 *
 * @brief   MQTT subscribe callback function
 * @param   String &topic    - MQTT Topic
 * @param   String &payload  - MQTT Payload
 * @return  void.
 * 
**/
void messageReceived(String &topic, String &payload) {
    // // Note: Do not use the client in the callback to publish, subscribe or
    // // unsubscribe as it may cause deadlocks when other things arrive while
    // // sending and receiving acknowledgments. Instead, change a global variable,
    // // or push to a queue and handle it in the loop after calling `client.loop()`.

    // static char recv_topic[50];
    // static char recv_msg[160];
    // static char params[20];

    // // check if we have space
    // if((sizeof(recv_msg) < payload.length()) || (sizeof(recv_topic) < topic.length())){
    //     return;
    // }

    // // clear buffers
    // memset(recv_topic,'\0',sizeof(recv_topic));
    // memset(recv_msg,'\0',sizeof(recv_msg));
    // memset(params,'\0',sizeof(params));

    // // get topic name
    // topic.toCharArray(recv_topic,sizeof(recv_topic));

    // // get the received message
    // payload.toCharArray(recv_msg,sizeof(recv_msg));

    // if (strcmp(recv_msg,(char*)"sendIp") == 0){
    //     sendIP = true;
    // }
    
    // else{
    //     printf("Received a message with topic (%s) with content (%s) \r\n",recv_topic,recv_msg);
    // }
}


/**
 *
 * @brief  Check IAQ Return Value
 * @param   void
 * @return  void.
 * 
**/
void checkIaqSensorStatus(void) {
    if (iaqSensor.status != BSEC_OK) {
        if (iaqSensor.status < BSEC_OK) {
            Serial.printf("BSEC error code : %u\n",iaqSensor.status);
            for (;;)
                errLeds(); /* Halt in case of failure */
        } else {
            Serial.printf("BSEC warning code : %u\n",iaqSensor.status);
        }
    }

    if (iaqSensor.bme680Status != BME680_OK) {
        if (iaqSensor.bme680Status < BME680_OK) {
            Serial.printf("BME680 error code : %u\n",iaqSensor.bme680Status);
        for (;;)
            errLeds(); /* Halt in case of failure */
        } else {
            Serial.printf("BME680 warning code : %u\n",iaqSensor.bme680Status);
        }
    }
    iaqSensor.status = BSEC_OK;
}

/**
 *
 * @brief   Blink leds 
 * @param   void
 * @return  void.
 * 
**/
void errLeds(void) {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}

/**
 *
 * @brief   Load previous state from EEPROM
 * @param   void
 * @return  void.
 * 
**/
void loadState(void) {
    if (EEPROM.read(0) == BSEC_MAX_STATE_BLOB_SIZE) {
        // Existing state in EEPROM
        Serial.printf("Reading state from EEPROM ...\n");

        for (uint8_t i = 0; i < BSEC_MAX_STATE_BLOB_SIZE; i++) {
            bsecState[i] = EEPROM.read(i + 1);
            Serial.printf("%x,",bsecState[i]);
        }
        Serial.printf("\n");

        iaqSensor.setState(bsecState);
        checkIaqSensorStatus();
    } else {
        // Erase the EEPROM with zeroes
        Serial.println("Erasing EEPROM");

        for (uint8_t i = 0; i < BSEC_MAX_STATE_BLOB_SIZE + 1; i++) {
            EEPROM.write(i, 0);
        }

        EEPROM.commit();
    }
}

/**
 *
 * @brief   Save current state in EEPROM
 * @param   void
 * @return  void.
 * 
**/
void updateState(void) {
    bool update = false;
    /* Set a trigger to save the state. Here, the state is saved every STATE_SAVE_PERIOD with the first state being saved once the algorithm achieves full calibration, i.e. iaqAccuracy = 3 */
    if (stateUpdateCounter == 0) {
        if (iaqSensor.iaqAccuracy >= 3) {
            update = true;
            stateUpdateCounter++;
        }
    } else {
        /* Update every STATE_SAVE_PERIOD milliseconds */
        if ((stateUpdateCounter * STATE_SAVE_PERIOD) < millis()) {
            update = true;
            stateUpdateCounter++;
        }
    }

    if (update) {
        iaqSensor.getState(bsecState);
        checkIaqSensorStatus();

        Serial.println("Writing state to EEPROM");

        for (uint8_t i = 0; i < BSEC_MAX_STATE_BLOB_SIZE ; i++) {
            EEPROM.write(i + 1, bsecState[i]);
            Serial.println(bsecState[i], HEX);
        }

        EEPROM.write(0, BSEC_MAX_STATE_BLOB_SIZE);
        EEPROM.commit();
    }
}
