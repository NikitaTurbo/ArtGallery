# AGP (Art Gallery Problem)

<p style="font-size: 18px;">
	Библиотека, которая визуализирует задачу о картинной галерее, которая целиком должна оказаться в зоне видимости как можно меньшего числа охранников; подбирает оптимальное количество и расстановку охранников для галереи произвольной N-угольной формы с помощью генетического алгоритма.
</p>

## Примеры работы
### Визуализация галереи и области видимостей охранников
<table>
  <tr>
    <td><img src="https://github.com/NikitaTurbo/ArtGallery/blob/main/examples/example1.jpg?raw=true" width="100%"></td>
    <td><img src="https://github.com/NikitaTurbo/ArtGallery/blob/main/examples/example2.jpg?raw=true" width="100%"></td>
  </tr>
  <tr>
    <td><img src="https://github.com/NikitaTurbo/ArtGallery/blob/main/examples/example3.jpg?raw=true" width="100%"></td>
    <td><img src="https://github.com/NikitaTurbo/ArtGallery/blob/main/examples/example4.jpg?raw=true" width="100%"></td>
  </tr>
</table>

### Оптимальное решение для галереи
![example5](https://github.com/NikitaTurbo/ArtGallery/blob/main/examples/example5.jpg)

## Requirements
![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.10+-064F8C?logo=cmake&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.6.1+-8CC445?logo=sfml&logoColor=white)
![Boost](https://img.shields.io/badge/Boost-1.86.0+-F7901E?logo=boost&logoColor=white)

## Установка, сборка и запуск

### 1. Установить библиотеки
[![SFML](https://img.shields.io/badge/SFML-689f38?logo=sfml&logoColor=white)](https://www.sfml-dev.org/download)
[![Boost](https://img.shields.io/badge/Boost-c26700?logo=boost&logoColor=white)](https://www.boost.org/releases/latest)

### 2. Клонировать репозиторий
```sh
git clone https://github.com/NikitaTurbo/ArtGallery.git
```

### 3. Переместить библиотеки в директорию `/ArtGallery/lib`

### 4. Собрать проект
```sh
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cmake --build .
```

### 5. Запустить
```sh
./AGP
```

## Примеры использования (`/ArtGallery/src/main.cpp`)
### Нарисовать охранников, галерею + Показ зоны видимости
```c++
#include <cmath>
#include <cstdio>
#include <unistd.h>

#include <AGP/components/ui/view.h>
#include <AGP/components/interface/team.h>
#include <AGP/components/interface/genetic_algorithm.h>

int main() {
	view w;
	w.read_gallery(); // чтение галереи
	team t = w.read_team(); // чтение охранников
	w.draw_area(t); // показ зоны видимости

	return 0;
}
```

### Чтение галереи из файла + Показ оптимального решения
```c++
#include <cmath>
#include <cstdio>
#include <unistd.h>

#include <AGP/components/ui/view.h>
#include <AGP/components/interface/team.h>
#include <AGP/components/interface/genetic_algorithm.h>

int main() {
	freopen("input.txt", "r", stdin);

	view w;

	std::cin >> gallery; // чтение галереи
	w.draw_gallery();

	population p(12);
	for (int _i = 0; _i < 10; ++_i) { // 10 поколений генетического алгоритма
		p.update();
	}

	team t = p.get(); // оптимальное решение (расположение охранников)
	w.draw_team(t);
	w.draw_area(t);

	return 0;
}
```


## Литература

<p style="font-size: 16px;">
	<i><b>[1]</b> Antonio L. Bajuelos, Santiago Canales, Gregorio Hernandez, Ana Mafalda Martins. Optimizing the Minimum Vertex Guard Set on Simple Polygons via a Genetic Algorithm. WSEAS TRANSACTIONS on INFORMATION SCIENCE and APPLICATIONS, 2008<br><b>[2]</b> М.Айгнер, Г. Циглер. Доказательства из Книги. М.: 2008.</i>
</p>
