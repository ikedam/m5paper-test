#include <Arduino.h>
#include <M5EPD.h>

namespace {
  void dump_partition(esp_partition_type_t type) {
  Serial.printf("label type subtype encrypted address-start address-end size:\n");
    esp_partition_iterator_t iter = esp_partition_find(type, ESP_PARTITION_SUBTYPE_ANY, NULL);
    while(iter != NULL) {
      const esp_partition_t* part = esp_partition_get(iter);
      Serial.printf(
        "%s %02x %02x %d 0x%06x 0x%06x %d\n",
        part->label,
        part->type,
        part->subtype,
        part->encrypted,
        part->address,
        part->address + part->size,
        part->size
      );
      iter = esp_partition_next(iter);
    }
  }
}

void setup() {
  M5.begin(false, false, true, false, true);

  Serial.printf("APP partitions:\n");
  dump_partition(ESP_PARTITION_TYPE_APP);

  Serial.printf("DATA partitions:\n");
  dump_partition(ESP_PARTITION_TYPE_DATA);
}

void loop() {
  // put your main code here, to run repeatedly:
}