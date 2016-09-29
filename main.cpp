#include <iostream>
#include <math.h>
#include <limits>

static const float G = 9.8;
static const int MAX_HEIGHT = std::numeric_limits<int>::max();

/*
 * Программа получает на вход высоту прыжка.
 * Вычисляет и выводит время, когда будет достигнута максимальная высота
 * Затем с шагом 0.1 проходит по всем моментам времени между началом и концом прыжка и выводит высоту в этот момент времени
 * Кроме того, обязательно выводится момент середины прыжка и момент конца прыжка
 */

/*
 * Псевдокод:
 * 1. Запрос максимальной высоты прыжка от пользователя. Число должно быть целочисленным.
 * 2. Проверка корректности ввода:
 *      a) число должно быть положительным
 *      b) число не должно выходить за пределы максимального значения int
 * 3. Вывод высоты прыжка каждые 0.1 сек, пока тело не достигло начальной высоты
 *      a) вывод времени достижения максильной высоты прыжка (середина прыжка)
 *      b) вывод времени достижения начальной высоты прыжка (конец прыжка)
 */

bool isValidHeight(float height)
{
    return (height >= 0 && height <= MAX_HEIGHT);
}

int main(int, char *[])
{
    setlocale(LC_ALL, "rus");
    int maxHeight;

    printf("Максимальная высота прыжка: ");
    if (0 == scanf("%d", &maxHeight))
    {
        printf("\nТребуется ввести целое число\n");
        return 1;
    }

    if (!isValidHeight(maxHeight))
    {
        printf("\nМаксимальная высота прыжка должна быть положительным числом и менее %d\n", MAX_HEIGHT);
        return 1;
    }

    float timeAtMaxHeight = sqrt(maxHeight * 2 / G);
    printf("Время, при которой достигается максимальная высота = %f\n", timeAtMaxHeight);

    float initialSpeed, currHeight;
    bool flag = false;

    for (float currTime = 0; currTime < timeAtMaxHeight * 2; currTime += 0.1f)
    {
        if (currTime > timeAtMaxHeight && !flag)
        {
            flag = true;
            initialSpeed = G * timeAtMaxHeight;
            currHeight = initialSpeed * timeAtMaxHeight - 0.5f * G * pow(timeAtMaxHeight, 2);
            printf("Время, при которой достигается максимальная высота = %f, текущая высота = %f\n", timeAtMaxHeight,
                   currHeight);
        }
        initialSpeed = G * timeAtMaxHeight;
        currHeight = initialSpeed * currTime - 0.5f * G * pow(currTime, 2);
        printf("Текущее время = %f, текущая высота = %f\n", currTime, currHeight);
    }

    initialSpeed = G * timeAtMaxHeight;
    currHeight = initialSpeed * (timeAtMaxHeight * 2) - 0.5f * G * pow(timeAtMaxHeight * 2, 2);
    printf("Время, при которой достигается максимальная высота = %f, текущая высота = %f\n", timeAtMaxHeight * 2,
           currHeight);

    return 0;
}
