#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

using namespace esphome;

class JuncTekKGF
  : public esphome::Component
  , public uart::UARTDevice
{
public:
  JuncTekKGF(unsigned address = 1, bool invert_current=false);

  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage_sensor_ = voltage_sensor; }
  void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
  void set_direction_sensor(sensor::Sensor *direction_sensor) { direction_sensor_ = direction_sensor; }
  void set_batteryPower_sensor(sensor::Sensor *batteryPower_sensor) { batteryPower_sensor_ = batteryPower_sensor; }
  void set_batteryLifeTime_sensor(sensor::Sensor *batteryLifeTime_sensor) { batteryLifeTime_sensor_ = batteryLifeTime_sensor; }
  void set_batteryChargedEnergy_sensor(sensor::Sensor *batteryChargedEnergy_sensor) { batteryChargedEnergy_sensor_ = batteryChargedEnergy_sensor; }
  void set_batteryDischargedEnergy_sensor(sensor::Sensor *batteryDischargedEnergy_sensor) { batteryDischargedEnergy_sensor_ = batteryDischargedEnergy_sensor; }

  void set_battery_level_sensor(sensor::Sensor *battery_level_sensor) { battery_level_sensor_ = battery_level_sensor; }
  void dump_config() override;
  void loop() override;

  float get_setup_priority() const;// override;

protected:
  bool readline();
  void handle_line();
  void handle_status(const char* buffer);
  void handle_settings(const char* buffer);
  void request_data(uint8_t data_id);
  void decode_data(std::vector<uint8_t> data);
  bool verify_checksum(int checksum, const char* buffer);

  const unsigned address_;

  sensor::Sensor* voltage_sensor_{nullptr};
  sensor::Sensor* current_sensor_{nullptr};
  sensor::Sensor* battery_level_sensor_{nullptr};
  sensor::Sensor* direction_sensor_{nullptr};
  sensor::Sensor* batteryPower_sensor_{nullptr};
  sensor::Sensor* batteryLifeTime_sensor_{nullptr};
  sensor::Sensor* batteryChargedEnergy_sensor_{nullptr};
  sensor::Sensor* batteryDischargedEnergy_sensor_{nullptr};

  static constexpr int MAX_LINE_LEN = 120;
  std::array<char, MAX_LINE_LEN> line_buffer_;
  size_t line_pos_ = 0;

  optional<float> battery_capacity_;
  optional<unsigned long> last_settings_;
  optional<unsigned long> last_stats_;
  bool invert_current_;
};
