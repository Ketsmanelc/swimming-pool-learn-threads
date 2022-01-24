#include <iostream>
#include <thread>
#include <mutex>
int actTime[6] = {0,0,0,0,0,0};
std::mutex terminal_access;

void Swim(double speed, int num, int &time)
{
    const double distance = 10.0;
    double actDistance = 0;
    while (speed * time < distance)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        time++;
        actDistance = speed * time;
        if (actDistance > 100.0) actDistance = 100.0;
        terminal_access.lock();
        std::cout << "Swimmers: " << num << ": " << actDistance << " m" << "\n";
        terminal_access.unlock();
    }
}


int main() {
    double speed[6];
    for(int i = 0; i < 2; i++)
    {
        std::cin >> speed[i];
    }
    std::cout << "Start!!!" <<  std::endl;
    std::thread path_1(Swim, speed[0], 1, std::ref(actTime[0]));
    std::thread path_2(Swim, speed[1], 2, std::ref(actTime[1]));
    std::thread path_3(Swim, speed[2], 3, std::ref(actTime[2]));
    std::thread path_4(Swim, speed[3], 4, std::ref(actTime[3]));
    std::thread path_5(Swim, speed[4], 5, std::ref(actTime[4]));
    std::thread path_6(Swim, speed[5], 6, std::ref(actTime[5]));

    path_1.join();
    path_2.join();
    path_3.join();
    path_4.join();
    path_5.join();
    path_6.join();

    for (int i = 0; i < 6; i++)
        std::cout << "Swimmer # " << i + 1 << ": " << actTime[i] << " sec" << std::endl;
    return 0;
}
