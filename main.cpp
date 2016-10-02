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

#include <iostream>
#include <math.h>
#include <climits>

static const float G = 9.8;
static const int MAX_HEIGHT = INT_MAX;

bool isValidHeight(const int &height)
{
    return (height >= 0 && height <= MAX_HEIGHT);
}

bool askMaxHeightInConsole(int &maxHeight)
{
    printf("Максимальная высота прыжка: ");
    return (scanf("%d", &maxHeight) != 0);
}

void processJump(const float &timeAtMaxHeight)
{
    float currentHeight;
    float initialSpeed = G * timeAtMaxHeight;
    bool isMaxHeight = false;

    for (float currentTime = 0; currentTime < timeAtMaxHeight * 2; currentTime += 0.1f)
    {
        if (!isMaxHeight && currentTime > timeAtMaxHeight)
        {
            isMaxHeight = true;
            currentHeight = initialSpeed * timeAtMaxHeight - 0.5f * G * pow(timeAtMaxHeight, 2);
            printf("Время, при которой достигается максимальная высота = %f, текущая высота = %f\n", timeAtMaxHeight, currentHeight);
        }
        currentHeight = initialSpeed * currentTime - 0.5f * G * pow(currentTime, 2);
        printf("Текущее время = %f, текущая высота = %f\n", currentTime, currentHeight);
    }

    currentHeight = initialSpeed * (timeAtMaxHeight * 2) - 0.5f * G * pow(timeAtMaxHeight * 2, 2);
    printf("Время, при которой достигается максимальная высота = %f, текущая высота = %f\n", timeAtMaxHeight * 2, currentHeight);
}

int main(int, char *[])
{
    setlocale(LC_ALL, "rus");
    int maxHeight;

    if (!askMaxHeightInConsole(maxHeight))
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

    processJump(timeAtMaxHeight);
    return 0;
}
