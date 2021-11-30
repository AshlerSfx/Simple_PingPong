#include <iostream>
#include <pthread.h>
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int counter;
static int bounce_num = 5;


void ball_fun(void *n) {
    char *name = (char *) n;

    //Захватываем мьютекс
    pthread_mutex_lock(&mutex);

    while (counter++ < bounce_num) {
        std::cout << "\nNow player " <<  name << " is bouncing the ball!" << std::endl;

        //Шутки ради,выведем победителя, последнего отбившего мяч
        if(counter == bounce_num)
            std::cout << "\nWow, looks like player " << name << " is the winner!" << std::endl;

        //Будит второй поток, сам впадает в режим ожидания
        if(!pthread_cond_signal(&cond)) std::cout << name << " signals!\n";
        if(!pthread_cond_wait(&cond, &mutex)) std::cout << name << " is waiting\n";

    }
    //Открываем мьютекс
    pthread_mutex_unlock(&mutex);

    //Второй поток ждет, надо сообщить
    pthread_cond_signal(&cond);


}
int main() {

    pthread_t thread_1, thread_2;
    counter = 0;
    char *name1 =  "Player 1";
    char *name2 = "Player 2";

    std::cout << "Let the game start!" << std::endl;

    pthread_create(&thread_1, nullptr, reinterpret_cast<void *(*)(void *)>(&ball_fun),  (void *)name1);
    pthread_create(&thread_2, nullptr, reinterpret_cast<void *(*)(void *)>(&ball_fun),  (void *)name2);

    pthread_join(thread_1, nullptr);
    pthread_join(thread_2, nullptr);

    return 0;
}
