int EstadoA = 0;
int EstadoB = 0;

int EstadoW = 0;
int EstadoX = 0;
int EstadoY = 0;
int EstadoZ = 0;

void setup() {
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);  

  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  // Asegurarse de que todos los pines de salida están apagados al inicio
  }

  Serial.begin(9600);
}

void loop() {
  EstadoA = digitalRead(A0);  // Lectura de A0
  EstadoB = digitalRead(A1);  // Lectura de A1
  
  EstadoW = digitalRead(10);
  EstadoX = digitalRead(11);
  EstadoY = digitalRead(12);
  EstadoZ = digitalRead(13);

  int resultado = 0;
  bool negativo = false;
  bool indeterminado = false;

  if (EstadoW == 0 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 0) {
    Serial.println("NOP - No operation");
  } else if (EstadoW == 0 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 1) {
    resultado = EstadoA + EstadoB;
    Serial.println("Suma");
  } else if (EstadoW == 0 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 0) {
    resultado = EstadoA - EstadoB;
    if (resultado < 0) {
      negativo = true;
      resultado = -resultado;  // Invertir el resultado negativo
    }
    Serial.println("Resta");
  } else if (EstadoW == 0 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 1) {
    resultado = EstadoA * EstadoB;
    Serial.println("Multiplicacion");
  } else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 0 && EstadoZ == 0) {
    if (EstadoB != 0) {
      resultado = EstadoA / EstadoB;
    } else {
      indeterminado = true;
      Serial.println("Error: División por 0");
    }
  } else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 0 && EstadoZ == 1) {
    resultado = EstadoA & EstadoB;
    Serial.println("AND");
  } else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 1 && EstadoZ == 0) {
    resultado = EstadoA | EstadoB;
    Serial.println("OR");
  } else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 1 && EstadoZ == 1) {
    resultado = !EstadoA;
    Serial.println("NOT");
  } else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 0) {
    resultado = EstadoA ^ EstadoB;
    Serial.println("XOR");
  } else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 1) {
    resultado = !(EstadoA ^ EstadoB);
    Serial.println("XNOR");
  } else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 0) {
    resultado = !(EstadoA & EstadoB);
    Serial.println("NAND");
  } else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 1) {
    resultado = !(EstadoA | EstadoB);
    Serial.println("NOR");
  }

  clearDisplay1();  // Asegurarse de que el display esté limpio antes de mostrar el nuevo resultado

  if (!indeterminado) {
    display7Segment1(resultado);
  } else {
    displayIndeterminate();
  }

  displayNegative(negativo);
}

void display7Segment1(int number) {
  int segments[] = {
    0b0111111, // 0
    0b0000110, // 1 - Enciende solo los segmentos B y C
    0b1011011  // 2
  };
  
  if (number >= 0 && number <= 2) {  // Solo se maneja hasta el número 2
    int segment = segments[number];
    for (int i = 2; i <= 8; i++) {
      digitalWrite(i, segment & 1);
      segment >>= 1;
    }
  }
}

void displayNegative(bool isNegative) {
  // Encender el segmento G (pin 9) si el resultado es negativo
  digitalWrite(9, isNegative ? HIGH : LOW);  // HIGH enciende el segmento G
}

void displayIndeterminate() {
  // Enciende los segmentos G, A y D para indicar indeterminación
  digitalWrite(9, HIGH);  // Segmento G
  digitalWrite(2, HIGH);  // Segmento A
  digitalWrite(5, HIGH);  // Segmento D
}

void clearDisplay1() {
  for (int i = 2; i <= 8; i++) {
    digitalWrite(i, LOW);
  }     
}

void clearDisplay2() {  
  digitalWrite(9, LOW);
}



