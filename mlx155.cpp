#include "mlx15.h"

MLX90615::MLX90615(uint8_t i2c_addr) {
  i2c_addr_ = i2c_addr;
}

void MLX90615::begin() {
  Wire.begin();
}

uint32_t MLX90615::get_id() {
  uint32_t id;
  
  id = read_word16(MLX90615_REG_ID_LOW);
  id |= (uint32_t)read_word16(MLX90615_REG_ID_HIGH) << 16;

  return id;
}

float MLX90615::get_ambient_temp() {
  float temp;

  temp = read_word16(MLX90615_REG_TEMP_AMBIENT) * 0.02 - 273.15;
  
  return temp;
}

float MLX90615::get_object_temp() {
  float temp;

  temp = read_word16(MLX90615_REG_TEMP_OBJECT) * 0.02 - 273.15;
  
  return temp;
}

uint16_t MLX90615::read_word16(uint8_t reg) {
  uint16_t data;

  Wire.beginTransmission(i2c_addr_);
  Wire.write(reg);
  Wire.endTransmission(false);
  
  Wire.requestFrom(i2c_addr_, (uint8_t)3);
  data = Wire.read();       // read low byte
  data |= Wire.read() << 8; // read high byte

  Wire.read(); // read and discard PEC (packet error code)

  return data;
}