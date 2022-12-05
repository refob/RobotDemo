#include <Servo.h>

int servo_pin_u = 3;
int servo_pin_o = 4;
int servo_pin_m = 5;
int servo_pin_gripper = 6;
int servo_pin_turn = 7;
int su, sm, so, st, sg;

Servo sg90_u, sg90_m, sg90_o, sg90_g, sg90_t;

void go_home(int sleep = 2000) {
  su = sm = sg = 180;
  st = 90;
  so = 0;
  sg90_u.write(su);
  sg90_m.write(sm);
  sg90_o.write(so);
  sg90_g.write(sg);
  sg90_t.write(st);
  delay(sleep);
}

void move(int gu, int gm, int go, int gt, int gg, int mdelay = 8) {
  int done;
  done = 0;
  while (!done)
  {
    if (su < gu) {
      su++;
      sg90_u.write(su);
    }
    else if (su > gu) {
      su--;
      sg90_u.write(su);
    }
    if (sm < gm) {
      sm++;
      sg90_m.write(sm);
    }
    else if (sm > gm) {
      sm--;
      sg90_m.write(sm);
    }
    if (so < go) {
      so++;
      sg90_o.write(so);
    }
    else if (so > go) {
      so--;
      sg90_o.write(so);
    }
    if (st < gt) {
      st++;
      sg90_t.write(st);
    }
    else if (st > gt) {
      st--;
      sg90_t.write(st);
    }
    if (sg < gg) {
      sg++;
      sg90_g.write(sg);
    }
    else if (sg > gg) {
      sg--;
      sg90_g.write(sg);
    }
    if (mdelay > 0) delay(mdelay);
    done = ((su == gu) && (sm == gm) && (so == go) && (st == gt) && (sg == gg));
  }
}

void open_gripper(int sleep = 600) {
  move(su, sm, so, st, 180, 0);
  delay(sleep);
}

void close_gripper(int sleep = 400) {
  move(su, sm, so, st, 0, 0);
  delay(sleep);
}

void close_gripper_a_bit(int sleep = 400) {
  move(su, sm, so, st, 110);
  delay(sleep);
}

void down(int sleep = 1000) {
  move(60, 60, 30, st, sg);
  delay(sleep);
}

void up(int sleep = 2000) {
  move(180, 180, 0, st, sg);
  delay(sleep);
}

void up_a_bit(int sleep = 2000) {
  move(130, 45, 0, st, sg);
  delay(sleep);
}

void turn_left(int sleep = 2000) {
  move(su, sm, so, 180, sg);
  delay(sleep);
}

void turn_center(int sleep = 2000) {
  move(su, sm, so, 90, sg);
  delay(sleep);
}

void turn_right(int sleep = 2000) {
  move(su, sm, so, 0, sg);
  delay(sleep);
}

void slow_to_home(int sleep = 3000) {
  move(180, 180, 0, 90, 180);
  delay(sleep);
}

void setup() {
  sg90_u.attach(servo_pin_u);
  sg90_m.attach(servo_pin_m);
  sg90_o.attach(servo_pin_o);
  sg90_g.attach(servo_pin_gripper);
  sg90_t.attach(servo_pin_turn);
  go_home();
  // gu:180 gm:180  go:0  gt:90  gg:180
  move(180, 180, 65, st, sg);
  delay(3000);
  close_gripper_a_bit(3000);
  down();
  open_gripper();
  up_a_bit();
  slow_to_home(3000);
  down();
  close_gripper_a_bit();
  up_a_bit();
  turn_left();
  down();
  open_gripper();
  up_a_bit();
  slow_to_home(3000);
  turn_left();
  down();
  close_gripper_a_bit();
  up_a_bit();
  turn_right();
  down();
  open_gripper();
  up_a_bit();
  slow_to_home(3000);
  turn_right();
  down();
  close_gripper_a_bit();
  up_a_bit();
  turn_center(3000);
  move(180, 180, 180, st, sg, 0);
  delay(60);
  move(180, 180, 180, st, 180, 0);
  delay(3000);
  slow_to_home();
}

void loop() {}
