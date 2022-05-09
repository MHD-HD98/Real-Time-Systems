#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Pins
static const int led_pin = LED_BUILTIN;

// Globals
static SemaphoreHandle_t mutex;

// Tasks
void blinkLED(void *parameters) {
  
  // Copy the parameter into a local variable
  int num = *(int *)parameters;
  
  xSemaphoreGive(mutex);
  
  Serial.print("Received: ");
  Serial.println(num);

  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(num / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(num / portTICK_PERIOD_MS);
  }
}

void setup() {

  long int delay_arg;

  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  vTaskDelay(5000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("--- Challenge 6: MUTEX ---");

  Serial.println("Enter number for delay");

  // Wait for input from Serial
  while (Serial.available() <= 0);

  delay_arg = Serial.parseInt();
  Serial.print("Sending: ");
  Serial.println(delay_arg);

  mutex = xSemaphoreCreateMutex();

  xSemaphoreTake(mutex, portMAX_DELAY);

  xTaskCreatePinnedToCore(
    blinkLED,               // Task function
    "Blink LED",            // Name of the task
    1024,                   // Stack size (bytes)
    (void *)&delay_arg,     // Parameter to pass
    1,                      // Task priority
    NULL,                   // Task handle
    app_cpu                // Core to run the task on (0 or 1)
  );

  xSemaphoreTake(mutex, portMAX_DELAY);

  Serial.println("Done!");
  
}

void loop() {

}
