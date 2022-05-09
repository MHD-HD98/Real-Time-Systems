#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t buf_len = 20;

char buf[buf_len];
bool Done = false;
uint8_t idx = 0;

void ReadSerial(void *parameters) {

  char c;

  // Clear whole buffer
  memset(buf, 0, buf_len);

  // Loop forever
  while (1) {

    // Read characters from serial
    if (Serial.available() > 0 && !Done) {
      c = Serial.read();
      // Update delay variable and reset buffer if we get a newline character
      if (c == '\n') {
        Done = true;
      } else {
        // Only append if index is not over message limit
        if (idx < buf_len - 1) {
          buf[idx] = c;
          idx++;
        }
      }
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void PrintSerial(void *par)
{
  while(1)
  {
    if(Done)
    {
      for(int i = 0; i <idx;i++)
        Serial.print(buf[i]);
      Serial.println("");
      memset(buf, 0, buf_len);
      idx = 0;
      Done = false;
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreatePinnedToCore(ReadSerial,"Reading From Serial",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(PrintSerial,"Printing Into Serial",1024,NULL,1,NULL,app_cpu);
}

void loop() {
  // put your main code here, to run repeatedly:

}
