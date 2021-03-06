#include "mbed.h"

#define CW 1  // clock wise
#define CCW 2 // counter clock wise
#define ERR_WISE 0 // Error wise
#define SAFERY_CURRENT 100 // max analog value of current of each motor

class Motor{
public:
  PwmOut *pwm; 
  DigitalOut *cw;  // clock wise
  DigitalOut *ccw; // counter clock wise 
  
  int direction; // rotate dir :: cw or cww. 
  float pwm_val; // 0 to 1

  
  Motor(PinName pwm_pin, PinName cw_pin,
        PinName ccw_pin){
    pwm = new PwmOut(pwm_pin);
    cw = new DigitalOut(cw_pin);
    ccw = new DigitalOut(ccw_pin);
  }
  
  void _run(int _direction, float _pwm_val){
    set_rotate_dir(_direction);
    set_pwm(_pwm_val);
  }
  
  void stop(){
    set_pwm(0);
    set_rotate_dir(ERR_WISE);
  }
  
  void set_rotate_dir(int _direction){
    direction = _direction;
    if(direction == CW){
      *cw = 1;  *ccw = 0;
    } else if (direction == CCW){
      *cw = 0; *ccw = 1;
    } else {
      *cw = 0; *ccw = 0;
    }
  }
  
  void set_pwm(float _pwm_val){
    pwm_val = _pwm_val;
    pwm->write(pwm_val);
  }

  void run(float _pwm_val){
    if(0 > _pwm_val && -1 < _pwm_val){
      _run(CW, -_pwm_val);
    } else if(0 <= _pwm_val && 1 > _pwm_val) {
      _run(CCW, _pwm_val);
    } else {
      stop();
    }
  }
};


/* sample of pin structure
   motor_a -> vnh2sp30(0)
   dp2   -> digital5 (pwm)
   dp14  -> digital8 (rotate_direction)
   dp13  -> digital7 (rotate_direction)

   motor_b -> vnh2sp30(0)
   dp1   -> digital6 (pwm)
   dp11  -> digital4 (rotate_direction)
   dp10  -> digital9 (rotate_direction)

*/

/*
  int main() {
  
  Motor motor_a(dp2, dp14, dp13);
  Motor motor_b(dp1, dp11, dp10);
  //Motor motor_c()
  
  while(1) {
  motor_a.run(0.8);
  motor_b.run(0.8);
  wait_ms(500);

    
  motor_a.run(-0.8);
  motor_b.run(-0.8);
  wait_ms(500);


  }
  }

*/
