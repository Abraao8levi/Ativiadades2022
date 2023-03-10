#include <aux.hpp>
#include <iostream>
#include <sstream>

class Time {
private:
  int hour{0};
  int minute{0};
  int second{0};

public:
  Time(int hour, int minute, int second) {}

  void setHour(int hour) {
    if (hour < 24)
      this->hour = hour;
    else
      std::cout << "fail: hora invalida\n";
  }

  void setMinute(int minute) {
    if (minute < 60)
      this->minute = minute;
    else
      std::cout << "fail: minuto invalido\n";
  }

  void setSecond(int second) {
    if (second < 60)
      this->second = second;
    else
      std::cout << "fail: segundo invalido\n";
  }

  int getHour() { return hour; }

  int getMinute() { return minute; }

  int getSecond() { return second; }

  void nextSecond() {
    this->second++;
    if (getSecond() > 59) {
      this->minute++;
      setSecond(00);
    }
    if (getMinute() > 59) {
      this->hour++;
      setMinute(00);
    }
    if (getHour() > 23)
      setHour(00);
  }

  std::string str() {
    std::stringstream ss;
    auto sw = std::setw(2);
    ss << std::setfill('0') << sw << this->hour << ":" << sw << this->minute
       << ":" << sw << this->second;
    return ss.str();
  }
};

int main() {
  aux::Chain chain;
  aux::Param ui;
  Time time(0, 0, 0);

  chain["set"] = [&]() {
    time.setHour(aux::to<int>(ui[1]));
    time.setMinute(aux::to<int>(ui[2]));
    time.setSecond(aux::to<int>(ui[3]));
  };
  chain["show"] = [&]() { std::cout << time.str() << std::endl; };
  chain["next"] = [&]() { time.nextSecond(); };

  aux::execute(chain, ui);
};