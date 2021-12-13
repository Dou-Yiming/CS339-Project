int a[5][5][8] = {{{1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}},
                  {{1, 1, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}},
                  {{1, 1, 0, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}},
                  {{1, 1, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1}},
                  {{1, 1, 0, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 1, 0, 1}}};
void setup() //程序初始化
{
  pinMode(9, OUTPUT); //设置LED为输出模式

  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A2, INPUT_PULLUP);
}

void loop() //程序主体循环
{
  digitalWrite(9, LOW);
  int Intensity = digitalRead(A2);
  if (Intensity == 0)
  {
    for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 5; ++j)
      {
        digitalWrite(9, HIGH);
        delay(20);
        for (int k = 0; k < 8; ++k)
        {
          int out = a[i][j][k];
          if (out == 0)
          {
            digitalWrite(9, LOW);
            delay(5);
          }
          else if (out == 1)
          {
            digitalWrite(9, HIGH);
            delay(5);
          }
        }
      }
    if (a[2][2][7] == 0)
    {
      digitalWrite(9, HIGH);
      delay(10);
    }
    else
    {
      digitalWrite(9, LOW);
      delay(10);
    }
  }
}
