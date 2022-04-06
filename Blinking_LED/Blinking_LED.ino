#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int LedPin = 12;

void LedToggle1(void * par)
{
  while(1)
  {
  digitalWrite(LedPin, HIGH);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  digitalWrite(LedPin, LOW);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void LedToggle2(void * par)
{
  while(1)
  {
  digitalWrite(LedPin, HIGH);
  vTaskDelay(210 / portTICK_PERIOD_MS);
  digitalWrite(LedPin, LOW);
  vTaskDelay(210 / portTICK_PERIOD_MS);
  }
}

void LedToggle3(void * par)
{
  while(1)
  {
  digitalWrite(LedPin, HIGH);
  vTaskDelay(180 / portTICK_PERIOD_MS);
  digitalWrite(LedPin, LOW);
  vTaskDelay(180 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin, OUTPUT);

  xTaskCreatePinnedToCore(LedToggle1, "Toggle Led 1", 1024, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(LedToggle2, "Toggle Led 2", 1024, NULL, 2, NULL, app_cpu);
  xTaskCreatePinnedToCore(LedToggle3, "Toggle Led 3", 1024, NULL, 3, NULL, app_cpu);
}

void loop() {
  // put your main code here, to run repeatedly:

}
