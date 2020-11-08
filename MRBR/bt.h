#include "BluetoothSerial.h"

#define STANDBY 1
#define CONNECTED 2

//Create a new instance of the BluetoothSerial class
BluetoothSerial BT;

//Int variable to store the bluetooth state
int btState;

void bt_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  switch(event)
  {
    case ESP_SPP_SRV_OPEN_EVT:
      btState = CONNECTED;
      break;
    case ESP_SPP_CLOSE_EVT:
      btState = STANDBY;
      break;
  }
}
