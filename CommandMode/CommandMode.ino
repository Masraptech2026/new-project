/*
 * CommandMode LED Controller
 *
 * Controls the built-in LED via serial commands.
 * Enter "command mode" and then send commands to blink the LED.
 *
 * Supported commands (after entering command mode):
 *   blink        - Blink at normal speed (indefinitely)
 *   blink fast   - Blink fast (indefinitely)
 *   blink slow   - Blink slow (indefinitely)
 *   blink N      - Blink exactly N times
 *   on           - Turn LED on
 *   off          - Turn LED off
 *   stop         - Stop blinking, turn LED off
 *   status       - Show current status
 *   help         - Show help
 *   exit         - Exit command mode
 */

const int LED_PIN = 13;  // Built-in LED on most Arduino boards

// Blink intervals in milliseconds
const unsigned long BLINK_SLOW_MS   = 1000;
const unsigned long BLINK_NORMAL_MS = 500;
const unsigned long BLINK_FAST_MS   = 100;

// State
bool commandMode       = false;
bool ledBlinking       = false;
bool ledState          = false;
unsigned long blinkInterval  = BLINK_NORMAL_MS;
unsigned long lastBlinkTime  = 0;
int blinkCount               = 0;
int blinkTarget              = -1;  // -1 = blink indefinitely

String inputBuffer = "";

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for serial port (needed on Leonardo/Micro)

  Serial.println("=== Arduino Command Mode LED Controller ===");
  Serial.println("Type 'mode command' to enter command mode.");
}

void loop() {
  // Read incoming serial characters
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      if (inputBuffer.length() > 0) {
        processCommand(inputBuffer);
        inputBuffer = "";
      }
    } else {
      inputBuffer += c;
    }
  }

  // Handle non-blocking LED blinking
  if (ledBlinking) {
    unsigned long now = millis();
    if (now - lastBlinkTime >= blinkInterval) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      lastBlinkTime = now;

      // Count completed blinks (one full blink = HIGH then LOW)
      if (!ledState) {
        blinkCount++;
        if (blinkTarget > 0 && blinkCount >= blinkTarget) {
          ledBlinking = false;
          ledState    = false;
          digitalWrite(LED_PIN, LOW);
          blinkCount = 0;
          Serial.print("Done: completed ");
          Serial.print(blinkTarget);
          Serial.println(" blink(s).");
        }
      }
    }
  }
}

void processCommand(String cmd) {
  cmd.trim();
  cmd.toLowerCase();

  // Always allow entering command mode
  if (cmd == "mode command") {
    commandMode = true;
    Serial.println("[OK] Entered command mode. Type 'help' for available commands.");
    return;
  }

  if (!commandMode) {
    Serial.println("[INFO] Not in command mode. Type 'mode command' to enter.");
    return;
  }

  // --- Commands available in command mode ---
  if (cmd == "help") {
    printHelp();

  } else if (cmd == "exit") {
    commandMode = false;
    ledBlinking = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("[OK] Exited command mode. LED stopped.");

  } else if (cmd == "blink") {
    startBlinking(-1, BLINK_NORMAL_MS, "Blinking at normal speed...");

  } else if (cmd == "blink fast") {
    startBlinking(-1, BLINK_FAST_MS, "Blinking fast...");

  } else if (cmd == "blink slow") {
    startBlinking(-1, BLINK_SLOW_MS, "Blinking slow...");

  } else if (cmd.startsWith("blink ")) {
    String arg   = cmd.substring(6);
    arg.trim();
    int count = arg.toInt();
    if (count > 0) {
      String msg = "Blinking " + String(count) + " time(s)...";
      startBlinking(count, BLINK_NORMAL_MS, msg);
    } else {
      Serial.println("[ERROR] Invalid count. Usage: blink <number>  (e.g. blink 5)");
    }

  } else if (cmd == "on") {
    ledBlinking = false;
    ledState    = true;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("[OK] LED ON");

  } else if (cmd == "off") {
    ledBlinking = false;
    ledState    = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("[OK] LED OFF");

  } else if (cmd == "stop") {
    ledBlinking = false;
    ledState    = false;
    blinkCount  = 0;
    digitalWrite(LED_PIN, LOW);
    Serial.println("[OK] Blinking stopped. LED OFF.");

  } else if (cmd == "status") {
    printStatus();

  } else {
    Serial.print("[ERROR] Unknown command: '");
    Serial.print(cmd);
    Serial.println("'. Type 'help' for available commands.");
  }
}

void startBlinking(int target, unsigned long interval, String message) {
  blinkTarget   = target;
  blinkInterval = interval;
  blinkCount    = 0;
  ledBlinking   = true;
  lastBlinkTime = millis();
  Serial.println("[OK] " + message);
}

void printStatus() {
  Serial.println("--- Status ---");
  Serial.print("  Command mode : "); Serial.println(commandMode ? "ON"  : "OFF");
  Serial.print("  Blinking     : "); Serial.println(ledBlinking ? "YES" : "NO");
  Serial.print("  LED state    : "); Serial.println(ledState    ? "ON"  : "OFF");
  if (ledBlinking) {
    Serial.print("  Interval     : "); Serial.print(blinkInterval); Serial.println(" ms");
    if (blinkTarget > 0) {
      Serial.print("  Progress     : "); Serial.print(blinkCount);
      Serial.print(" / ");             Serial.println(blinkTarget);
    }
  }
  Serial.println("--------------");
}

void printHelp() {
  Serial.println("--- Command Mode Help ---");
  Serial.println("  blink          Blink LED at normal speed (indefinitely)");
  Serial.println("  blink fast     Blink LED fast (indefinitely)");
  Serial.println("  blink slow     Blink LED slow (indefinitely)");
  Serial.println("  blink <N>      Blink LED exactly N times");
  Serial.println("  on             Turn LED on");
  Serial.println("  off            Turn LED off");
  Serial.println("  stop           Stop blinking and turn LED off");
  Serial.println("  status         Show current status");
  Serial.println("  help           Show this help message");
  Serial.println("  exit           Exit command mode");
  Serial.println("-------------------------");
}
