const int A = 12;
const int B = 11;
const int Y = 10;

void setup() {
  Serial.begin(9600);
}

const int LOGIC_GATES[6][4] = {
  {0, 0, 0, 1}, // And
  {0, 1, 1, 1}, // Or
  {1, 1, 1, 0}, // Nand
  {1, 0, 0, 0}, // Nor
  {0, 1, 1, 0}, // Xor
  {1, 0, 0, 1}  // Xnor
};

const String LOGIC_GATE_NAMES[6] = {
  "AND",        // 0001
  "OR",         // 0111
  "NAND",       // 1110
  "NOR",        // 1000
  "XOR",        // 0110
  "XNOR"        // 1001
};

const int MODES[6][3] = {
  {A, B, Y},
  {A, Y, B},
  {B, A, Y},
  {B, Y, A},
  {Y, A, B},
  {Y, B, A},
};

void loop() {
  // Test all possible combinations of the positions of the A, B and Y pins
  int res = -1;

  for(int i = 0; i < (sizeof MODES / sizeof MODES[0]); i++) {
    res = test_gate(MODES[i][0], MODES[i][1], MODES[i][2]);
    if(res != -1) break;
  }
  
  // Print the result of the tests into the serial monitor
  if(res == -1) {
    Serial.println("No gate detected!");
  } else {
    Serial.print("Detected ");
    Serial.print(LOGIC_GATE_NAMES[res]);
    Serial.printn(" gate");
  }
  
  // Wait one second to prevent the serial monitor from being spamed
  delay(1000);
}

int test_gate(int a, int b, int y) {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(y, INPUT);

  int values[4] = {0, 0, 0, 0};

  // Test a=0 b=0
  digitalWrite(a, 0);
  digitalWrite(b, 0);
  values[0] = digitalRead(y);

  // Test a=1 b=0
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  values[1] = digitalRead(y);

  // Test a=0 b=1
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  values[2] = digitalRead(y);

  // Test a=1 b=1
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  values[3] = digitalRead(y);
  
  // Test if the results match a logic gate and return the logic gate number if so
  for(int i = 0; i < 6; i++) {
    bool mismatch = false;
    for(int j = 0; j < 4; j++) {
      if(LOGIC_GATES[i][j] != values[j]) {
        mismatch = true;
        break;
      }
    }
    
    if(!mismatch) {
      return i;
    }
  }

  return -1;
}
