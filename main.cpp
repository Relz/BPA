#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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

// TODO: Rename variables and split to several functions,
// TODO: fix negative height values, fix heigh values higher than max height.


int main(int, char *[])
{
	const float g = 9.8f;
	float T;
	float Vn;
	int S;
	int M;
	printf("S: ");
	if (0 == scanf("%d", &S))
	{
		printf("\n" "expected floating-point number" "\n");
		exit(1);
	}
	// T - time point when height is at maximum.
	// t - current time point
	// v(t) == v0 - g * t
	// v0 = g * T
	// s(t) == v0 * t - 0.5 * g * t * t
	T = sqrt(S * 2 / g);
	printf("T=%f\n", T);
	bool flag = false;
	for (float t = 0; t < T * 2; t += 0.1f)
	{
		if (t > T && !flag)
		{
			flag = true;
			float V0 = g * T;
			float s = V0 * T - 0.5 * g * T * T;
			printf("t=%f, s=%f\n", T, s);
		}
		float V0 = g * T;
		float s = V0 * t - 0.5 * g * t * t;
		printf("t=%f, s=%f\n", t, s);
	}

	float V0 = g * T;
	float s = V0 * (T*2) - 0.5 * g * (T * 2) * (T * 2);
	printf("t=%f, s=%f\n", T * 2, s);

	return 0;
}
