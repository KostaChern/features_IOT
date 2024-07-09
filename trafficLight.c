int BUTTON = 2;                  // Кнопка
int LED_RED = 10;                // Красный светодиод светофора
int LED_YELLOW = 9;              // Желтый светодиод светофора
int LED_GREEN = 8;               // Зеленый светодиод светофора
int LED_MAN_RED = 11;            // Красный светодиод светофора пешехода
int LED_MAN_GREEN = 12;          // Зеленый светодиод светофора пешехода
volatile bool isPressed = false; // Переменная для обработки прерывания нажатия кнопки
int statusMode;                  // Переменная для здачения из Serial

void semaforStatus1(); // Горит зеленый для авто
void semaforStatus2(); // Моргает зеленый для авто
void semaforStatus3(); // Горит желтый для авто
void semaforStatus4(); // Горит красный для авто и Зеленый пешеходу
void semaforStatus5(); // Горит красный и желтый
void semaforStatusB(); // Горит красный для авто и Зеленый пешеходу долго
void semaforRepair();  // Горят все светодиоды
void press();

void setup()
{
    // Инициализация порта
    Serial.begin(9600);
    Serial.println("For the traffic light repair mode, enter <1>");
    Serial.println("To exit repair mode, enter <0>");
    // Инициализация GPIO
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_MAN_RED, OUTPUT);
    pinMode(LED_MAN_GREEN, OUTPUT);
    pinMode(BUTTON, INPUT);
    // Выставление значений GPIO по умолчанию
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_MAN_RED, LOW);
    digitalWrite(LED_MAN_GREEN, LOW);
    // Подключение аппаратного прерывания по нажатию кнопки
    attachInterrupt(0, press, FALLING);
}

void loop()
{
    // Читаем значение из порта
    if (Serial.available() > 0)
    {
        statusMode = Serial.parseInt();
    }
    // Если 1, то зажигаем весь светофор
    if (statusMode == 1)
    {
        semaforRepair();
    }
    // Если 0, то светофор работает в нормальном режиме
    else if (statusMode == 0)
    {
        semaforStatus1();
        semaforStatus2();
        semaforStatus3();
        if (isPressed)
        {
            semaforStatusB();
            isPressed = false;
        }
        else
        {
            semaforStatus4();
        }
        semaforStatus5();
    }
    // Если ввели неверное значение напоминаем, что нужно вводить
    else
    {
        Serial.println("The values can only be : <1> or <0>");
    }
}

void semaforStatus1()
{

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_MAN_RED, HIGH);
    digitalWrite(LED_MAN_GREEN, LOW);
    delay(5000);
}

void semaforStatus2()
{
    for (int i = 0; i < 3; ++i)
    {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_MAN_RED, HIGH);
        digitalWrite(LED_MAN_GREEN, LOW);
        delay(500);
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_MAN_RED, HIGH);
        digitalWrite(LED_MAN_GREEN, LOW);
        delay(500);
    }
}

void semaforStatus3()
{
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_MAN_RED, HIGH);
    digitalWrite(LED_MAN_GREEN, LOW);
    delay(1500);
}

void semaforStatus4()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_MAN_RED, LOW);
    digitalWrite(LED_MAN_GREEN, HIGH);
    delay(3000);
}

void semaforStatus5()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_MAN_RED, HIGH);
    digitalWrite(LED_MAN_GREEN, LOW);
    delay(3000);
}

void semaforStatusB()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_MAN_RED, LOW);
    digitalWrite(LED_MAN_GREEN, HIGH);
    delay(8000);
}

void semaforRepair()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_MAN_RED, HIGH);
    digitalWrite(LED_MAN_GREEN, HIGH);
    delay(1000);
}

void press()
{
    isPressed = true;
}