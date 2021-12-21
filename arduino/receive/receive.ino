#define AD5 A5 //定义模拟口A5

int Intensity = 0; //光照度数值
int state = -1, cur_state = -1;
int pre_time = 0, cur_time = 0, hold_time = 0;
int ans[8];
int pos = 0;
bool start = false;
int id = 0;

int get_state(int intensity)
{
  if (intensity > 550) // 0
    return 0;
  else
    return 1;
}
void setup() //程序初始化
{
  Serial.begin(9600); //设置波特率9600
}
void loop() //程序主体循环
{
  Intensity = analogRead(AD5); //读取模拟口AD5的值，存入Intensity变量
//  Serial.println(Intensity);                               
  cur_time = millis();
  cur_state = get_state(Intensity);
  if (cur_state != state) // state change
  {
    hold_time = cur_time - pre_time;
    int cnt = (int)((double)hold_time / (double)5 + 0.5);
  next:
    if (cnt >= 4 && state == 1 && start == false && pos == 0) // 开始记录
    {
      start = true;
      cnt -= 4;
    }
    else if (cnt >= 4 && state == 1 && start == true) //上一轮还没记录完
    {
      int tmp = 8 - pos;
      cnt -= tmp;
      for (int i = 0; i < tmp; ++i)
        ans[pos++] = state;
      if (pos == 8) //一个包记录完成
      {
        for (int i = 0; i < 8; ++i)
        {
          Serial.println(ans[i]);
          id++;
        }
      }
      pos = 0;
      start = false;
      state = 1;
      goto next;
    }
    if (start != false)
    {
      for (int i = 0; i < cnt; ++i)
        ans[pos++] = state;
      if (pos == 8) //一个包记录完成
      {
        pos = 0;
        for (int i = 0; i < 8; ++i)
        {
          Serial.println(ans[i]);
          id++;
        }
        start = false;
      }
    }
    pre_time = millis();
    state = cur_state;
  }
}
