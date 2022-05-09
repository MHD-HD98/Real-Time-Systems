#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int buf_len = 20;
static int LED_rate = 500; //ms

// Pins
static const int led_pin = LED_BUILTIN;


// TASK(1): Blink LED at given input from serial
void toggleLED(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(LED_rate / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(LED_rate / portTICK_PERIOD_MS);
  }
}

// TASK(2): Ask input from serial for LED blink rate
void inputRate(void *parameter) {
  char input;
  char buf[buf_len];
  int i = 0;

  while (1) {
    if (Serial.available() > 0) {
      input = Serial.read();

      /////////////////////////////////////
      /////////////////////////////////////
      if (input == '\n') {
        LED_rate = atoi(buf);
        Serial.print("LED blink at rate: ");
        Serial.println(LED_rate);
        i = 0;
      }
      else {
        if (i < buf_len - 1) {
          buf[i] = input;
          i++;
        }
      }
      /////////////////////////////////////
      /////////////////////////////////////
    }
  }
}

void setup() {

  pinMode(led_pin, OUTPUT);
  Serial.begin(1200);

  // Task to run forever
  xTaskCreatePinnedToCore(toggleLED,
                          "Blink LED",
                          1024,
                          NULL,
                          1,            // task priority
                          NULL,         // task handle
                          app_cpu);

  // Task to run once with higher priority
  xTaskCreatePinnedToCore(inputRate,
                          "Read input from Serial",
                          1024,
                          NULL,
                          1,            // task priority (must be same to prevent lockup)
                          NULL,         // task handle
                          app_cpu);


  Serial.println("Input blink rate (in ms): ");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
//  vTaskDelete(NULL);
}

void loop() {

}
