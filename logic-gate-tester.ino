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

void loop() {
  // Mode a b y
  int res = check_gate(A, B, Y);
  
  // Mode y b a
  if(res < 0) res = check_gate(Y, B, A);

  // Mode a y b
  if(res < 0) res = check_gate(A, Y, B);
  
  // Mode b y a
  if(res < 0) res = check_gate(B, Y, A);
  
  // Print the result of the tests into the serial monitor
  if(res < 0) {
    Serial.println("No gate detected!");
  } else {
    Serial.print("Detected ");
    Serial.print(LOGIC_GATE_NAMES[res]);
    Serial.printn(" gate");
  }
  
  // Wait one second to prevent the serial monitor from being spamed
  delay(1000);
}

int check_gate(int a, int b, int y) {
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
